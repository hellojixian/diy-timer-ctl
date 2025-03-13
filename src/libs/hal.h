#ifndef HAL_H
#define HAL_H
#include <Arduino.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// 按钮引脚
#define BTN_OK PD2
#define BTN_CANCEL PD3
#define BTN_LEFT PD7
#define BTN_RIGHT PD6

// 其他硬件
#define BUZZER_PIN PD5
#define CTL_OUTPUT_PIN PB2

void initHardware();
#endif
