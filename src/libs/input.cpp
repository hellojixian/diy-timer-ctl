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
#define DEBOUNCE_DELAY 100

// **存储按钮的上次触发时间**
volatile uint32_t lastDebounceTime_OK = 0;
volatile uint32_t lastDebounceTime_Cancel = 0;
volatile uint32_t lastDebounceTime_Left = 0;
volatile uint32_t lastDebounceTime_Right = 0;

// **存储按钮的上次状态（0 = 未按下, 1 = 按下）**
volatile bool lastButtonState_OK = false;
volatile bool lastButtonState_Cancel = false;
volatile bool lastButtonState_Left = false;
volatile bool lastButtonState_Right = false;

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

// **按钮中断处理（带防抖 & 仅响应按下）**
ISR(PCINT2_vect)
{
  uint32_t currentTime = millis(); // **获取当前时间**
  if (isSleeping())
  {
    wakeUp();
    return;
  }
  // **处理 Left（UP）按键**
  if (bit_is_clear(PIND, BTN_LEFT))
  {
    if (!lastButtonState_Left && (currentTime - lastDebounceTime_Left > DEBOUNCE_DELAY))
    {
      lastDebounceTime_Left = currentTime;
      lastButtonState_Left = true;
      playButtonTone();
      if (onLeftPress)
        onLeftPress();
    }
  }
  else
  {
    lastButtonState_Left = false;
  }

  // **处理 Right（DOWN）按键**
  if (bit_is_clear(PIND, BTN_RIGHT))
  {
    if (!lastButtonState_Right && (currentTime - lastDebounceTime_Right > DEBOUNCE_DELAY))
    {
      lastDebounceTime_Right = currentTime;
      lastButtonState_Right = true;
      playButtonTone();
      if (onRightPress)
        onRightPress();
    }
  }
  else
  {
    lastButtonState_Right = false;
  }

  // **处理 OK 按键**
  if (bit_is_clear(PIND, BTN_OK))
  {
    if (!lastButtonState_OK && (currentTime - lastDebounceTime_OK > DEBOUNCE_DELAY))
    {
      lastDebounceTime_OK = currentTime;
      lastButtonState_OK = true;
      playOKTone();
      if (onOkPress)
        onOkPress();
    }
  }
  else
  {
    lastButtonState_OK = false;
  }

  // **处理 Cancel 按键**
  if (bit_is_clear(PIND, BTN_CANCEL))
  {
    if (!lastButtonState_Cancel && (currentTime - lastDebounceTime_Cancel > DEBOUNCE_DELAY))
    {
      lastDebounceTime_Cancel = currentTime;
      lastButtonState_Cancel = true;
      playCancelTone();
      if (onCancelPress)
        onCancelPress();
    }
  }
  else
  {
    lastButtonState_Cancel = false;
  }
}
