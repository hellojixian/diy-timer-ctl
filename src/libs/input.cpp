#include "input.h"
#include "hal.h"
#include "buzzer.h"
#include "sleep.h"

#include <Arduino.h>

// **按钮回调函数指针**
ButtonCallback onOkPress = nullptr;
ButtonCallback onCancelPress = nullptr;
ButtonCallback onLeftPress = nullptr;
ButtonCallback onRightPress = nullptr;

// **防抖时间（单位：毫秒）**
#define DEBOUNCE_DELAY 50
#define HOLD_DELAY 50            // **长按判定时间（800ms后进入连发）**
#define HOLD_REPEAT_INTERVAL 300 // **长按连发间隔（每150ms触发一次）**

// **存储按钮的上次触发时间**
volatile uint32_t lastDebounceTime_OK = 0;
volatile uint32_t lastDebounceTime_Cancel = 0;
volatile uint32_t lastDebounceTime_Left = 0;
volatile uint32_t lastDebounceTime_Right = 0;

// **存储按钮的标记状态（是否有新的按键事件）**
volatile bool buttonPressed_OK = false;
volatile bool buttonPressed_Cancel = false;
volatile bool buttonPressed_Left = false;
volatile bool buttonPressed_Right = false;

// **标记 Left/Right 是否已经进入长按模式**
volatile bool buttonHeld_Left = false;
volatile bool buttonHeld_Right = false;

// **初始化 PCINT 使能**
void initInput()
{
  cli(); // **关闭全局中断**

  // **使能 PCINT2（PD2-PD7）**
  PCICR |= (1 << PCIE2);    // **使能 PCINT2 组**
  PCMSK2 |= (1 << PCINT18); // **使能 PD2 (OK)**
  PCMSK2 |= (1 << PCINT19); // **使能 PD3 (CANCEL)**
  PCMSK2 |= (1 << PCINT22); // **使能 PD6 (UP)**
  PCMSK2 |= (1 << PCINT23); // **使能 PD7 (DOWN)**

  sei(); // **开启全局中断**
}

// **绑定按钮事件**
void bindButtonHandlers(ButtonCallback okHandler, ButtonCallback cancelHandler, ButtonCallback leftHandler, ButtonCallback rightHandler)
{
  onOkPress = okHandler;
  onCancelPress = cancelHandler;
  onLeftPress = leftHandler;
  onRightPress = rightHandler;
}

void handleInput()
{
  uint32_t currentTime = millis();

  // **处理 Left（UP）按键，支持长按连发**
  if (buttonPressed_Left)
  {
    if (!buttonHeld_Left) // **第一次按下**
    {
      if (currentTime - lastDebounceTime_Left > DEBOUNCE_DELAY)
      {
        playButtonTone();
        if (onLeftPress)
          onLeftPress();
        buttonHeld_Left = true; // **进入长按检测状态**
        lastDebounceTime_Left = currentTime;
      }
    }
    else if (currentTime - lastDebounceTime_Left > HOLD_REPEAT_INTERVAL) // **长按时的连发逻辑**
    {
      playButtonTone();
      if (onLeftPress)
        onLeftPress();
      lastDebounceTime_Left = currentTime;
    }
  }

  // **处理 Right（DOWN）按键，支持长按连发**
  if (buttonPressed_Right)
  {
    if (!buttonHeld_Right) // **第一次按下**
    {
      if (currentTime - lastDebounceTime_Right > DEBOUNCE_DELAY)
      {
        playButtonTone();
        if (onRightPress)
          onRightPress();
        buttonHeld_Right = true; // **进入长按检测状态**
        lastDebounceTime_Right = currentTime;
      }
    }
    else if (currentTime - lastDebounceTime_Right > HOLD_REPEAT_INTERVAL) // **长按时的连发逻辑**
    {
      playButtonTone();
      if (onRightPress)
        onRightPress();
      lastDebounceTime_Right = currentTime;
    }
  }

  // **处理 OK 按键（无长按）**
  if (buttonPressed_OK && (currentTime - lastDebounceTime_OK > DEBOUNCE_DELAY))
  {
    buttonPressed_OK = false;
    playOKTone();
    if (onOkPress)
      onOkPress();
  }

  // **处理 Cancel 按键（无长按）**
  if (buttonPressed_Cancel && (currentTime - lastDebounceTime_Cancel > DEBOUNCE_DELAY))
  {
    buttonPressed_Cancel = false;
    playCancelTone();
    if (onCancelPress)
      onCancelPress();
  }
}

// **按钮中断处理（只做标记，不直接调用事件）**
ISR(PCINT2_vect)
{
  if (isSleeping())
  {
    wakeUp();
    return;
  }

  uint32_t currentTime = millis();

  // **处理 Left（UP）按键**
  if (bit_is_clear(PIND, BTN_LEFT))
  {
    if (!buttonPressed_Left)
    {
      lastDebounceTime_Left = currentTime;
      buttonPressed_Left = true;
      buttonHeld_Left = false; // **重置长按状态**
    }
  }
  else
  {
    buttonPressed_Left = false;
    buttonHeld_Left = false; // **松开后重置**
  }

  // **处理 Right（DOWN）按键**
  if (bit_is_clear(PIND, BTN_RIGHT))
  {
    if (!buttonPressed_Right)
    {
      lastDebounceTime_Right = currentTime;
      buttonPressed_Right = true;
      buttonHeld_Right = false; // **重置长按状态**
    }
  }
  else
  {
    buttonPressed_Right = false;
    buttonHeld_Right = false; // **松开后重置**
  }

  // **处理 OK 按键**
  if (bit_is_clear(PIND, BTN_OK))
  {
    if (!buttonPressed_OK)
    {
      lastDebounceTime_OK = currentTime;
      buttonPressed_OK = true;
    }
  }
  else
  {
    buttonPressed_OK = false;
  }

  // **处理 Cancel 按键**
  if (bit_is_clear(PIND, BTN_CANCEL))
  {
    if (!buttonPressed_Cancel)
    {
      lastDebounceTime_Cancel = currentTime;
      buttonPressed_Cancel = true;
    }
  }
  else
  {
    buttonPressed_Cancel = false;
  }
}
