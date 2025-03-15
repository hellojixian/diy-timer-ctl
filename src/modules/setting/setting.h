#ifndef MENU_SETTING_H
#define MENU_SETTING_H

#include "setting_trigger_interval.h"
#include "setting_sleep_timeout.h"
#include "setting_buzzer.h"
#include "setting_screen.h"
#include "../../libs/input.h"

// **定义 Getter 方法类型**
typedef void (*DisplayValueFunc)(); // **用于显示当前值**
typedef void (*SettingValueFunc)(); // **用于修改设置值**

struct SettingAction
{
  DisplayValueFunc displayValue; // **显示当前值函数**
  SettingValueFunc settingValue; // **设置值函数**
};

const SettingAction settingActions[] = {
    {displayTriggerIntervalValue, settingTriggerIntervalValue},
    {displaySleepTimeoutValue, settingSleepTimeoutValue},
    {displayScreenValue, settingScreenValue},
    {displayBuzzerValue, settingBuzzerValue}};

void initSettingModule();
void drawSettingUI();
#endif // MENU_SETTING_H
