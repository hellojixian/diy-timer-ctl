#include "input.h"
#include "hal.h"
#include "buzzer.h"

#include <Arduino.h>

// **按钮回调函数指针**
ButtonCallback onOkPress = nullptr;
ButtonCallback onCancelPress = nullptr;
ButtonCallback onUpPress = nullptr;
ButtonCallback onDownPress = nullptr;

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
void bindButtonHandlers(ButtonCallback okHandler, ButtonCallback cancelHandler, ButtonCallback upHandler, ButtonCallback downHandler)
{
  onOkPress = okHandler;
  onCancelPress = cancelHandler;
  onUpPress = upHandler;
  onDownPress = downHandler;
}

// **按钮中断处理**
ISR(PCINT2_vect)
{
  if (bit_is_clear(PIND, BTN_UP) && onUpPress)
  {
    playButtonTone();
    onUpPress(); // **触发上键回调**
  }
  if (bit_is_clear(PIND, BTN_DOWN) && onDownPress)
  {
    playButtonTone();
    onDownPress(); // **触发下键回调**
  }
  if (bit_is_clear(PIND, BTN_OK) && onOkPress)
  {
    playOKTone();
    onOkPress(); // **触发 OK 键回调**
  }
  if (bit_is_clear(PIND, BTN_CANCEL) && onCancelPress)
  {
    playCancelTone();
    onCancelPress(); // **触发 Cancel 键回调**
  }
}