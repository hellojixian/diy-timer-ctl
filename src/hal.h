#ifndef HAL_H
#define HAL_H

#include <Arduino.h>

#define BUZZER_PIN PD5     // 蜂鸣器
#define BTN_CANCEL PD3     // 取消按钮
#define BTN_OK PD2         // 确认按钮
#define BTN_UP PD6         // 向上按钮
#define BTN_DOWN PD7       // 向下按钮
#define CTL_OUTPUT_PIN PB2 // 输出控制引脚

void initHardware(); // 仅声明，不实现

#endif // HAL_H
