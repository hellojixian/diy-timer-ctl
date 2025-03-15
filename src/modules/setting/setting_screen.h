#ifndef SETTING_SCREEN_H
#define SETTING_SCREEN_H
#include <avr/pgmspace.h>

#define SCREEN_BRIGHTNESS_MIN 1
#define SCREEN_BRIGHTNESS_MED 127
#define SCREEN_BRIGHTNESS_MAX 254

const char setting_screen[] PROGMEM = "Screen Bridghtness";
const char setting_screen_low[] PROGMEM = "LOW";
const char setting_screen_medium[] PROGMEM = "MEDIUM";
const char setting_screen_high[] PROGMEM = "HIGH";

// **定义结构体存储 Key-Value**
struct ScreenOption
{
  const char *name; // 亮度名称
  uint8_t value;    // 亮度值
};

// **存储选项数组（PROGMEM 方式）**
const ScreenOption setting_screen_options[] PROGMEM = {
    {setting_screen_low, SCREEN_BRIGHTNESS_MIN},
    {setting_screen_medium, SCREEN_BRIGHTNESS_MED},
    {setting_screen_high, SCREEN_BRIGHTNESS_MAX}};

const uint8_t setting_screen_options_count = sizeof(setting_screen_options) / sizeof(ScreenOption);

void displayScreenValue();
void settingScreenValue();

#endif // SETTING_SCREEN_H