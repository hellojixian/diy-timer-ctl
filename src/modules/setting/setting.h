#ifndef MENU_SETTING_H
#define MENU_SETTING_H

#include "setting_trigger_interval.h"
#include "setting_sleep_timeout.h"
#include "setting_buzzer.h"

// **定义 Getter 方法类型**
typedef void (*DisplayValueFunc)(); // **用于显示当前值**
typedef void (*SettingValueFunc)(); // **用于修改设置值**

// **定义 SettingItem 结构体**
struct SettingItem
{
  const char *name;              // **设置项名称（存储在 PROGMEM）**
  DisplayValueFunc displayValue; // **显示当前值函数**
  SettingValueFunc settingValue; // **设置值函数**
};

const SettingItem settings[] PROGMEM = {
    {setting_trigger_interval, displayTriggerIntervalValue, settingTriggerIntervalValue},
    {setting_sleep_timeout, displaySleepTimeoutlValue, settingSleepTimeoutlValue},
    {setting_buzzer, displayBuzzerValue, settingBuzzerValue}};

void initSettingModule();

#endif // MENU_SETTING_H
