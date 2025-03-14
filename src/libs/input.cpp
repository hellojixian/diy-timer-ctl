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
#define DEBOUNCE_DELAY 300

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

  if (buttonPressed_Left && (currentTime - lastDebounceTime_Left > DEBOUNCE_DELAY))
  {
    buttonPressed_Left = false;
    playButtonTone();
    if (onLeftPress)
      onLeftPress();
  }

  if (buttonPressed_Right && (currentTime - lastDebounceTime_Right > DEBOUNCE_DELAY))
  {
    buttonPressed_Right = false;
    playButtonTone();
    if (onRightPress)
      onRightPress();
  }

  if (buttonPressed_OK && (currentTime - lastDebounceTime_OK > DEBOUNCE_DELAY))
  {
    buttonPressed_OK = false;
    playOKTone();
    if (onOkPress)
      onOkPress();
  }

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

  if (bit_is_clear(PIND, BTN_LEFT))
  {
    if (!buttonPressed_Left)
    {
      lastDebounceTime_Left = currentTime;
      buttonPressed_Left = true;
    }
  }

  if (bit_is_clear(PIND, BTN_RIGHT))
  {
    if (!buttonPressed_Right)
    {
      lastDebounceTime_Right = currentTime;
      buttonPressed_Right = true;
    }
  }

  if (bit_is_clear(PIND, BTN_OK))
  {
    if (!buttonPressed_OK)
    {
      lastDebounceTime_OK = currentTime;
      buttonPressed_OK = true;
    }
  }

  if (bit_is_clear(PIND, BTN_CANCEL))
  {
    if (!buttonPressed_Cancel)
    {
      lastDebounceTime_Cancel = currentTime;
      buttonPressed_Cancel = true;
    }
  }
}
