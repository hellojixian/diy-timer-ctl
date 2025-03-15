#include <Arduino.h>
#include "setting.h"
#include "../../libs/display.h"
#include "../../libs/input.h"
#include "../../libs/sleep.h"
#include "../../libs/setting.h"
#include "../menu/menu.h"

const uint8_t settingsCount = sizeof(settings) / sizeof(SettingItem);
uint8_t currentSettingIndex = 0;

ButtonCallback previousHandlers[4] = {nullptr, nullptr, nullptr, nullptr};

void goSetting();
void prevSettingOption();
void nextSettingOption();
void drawSettingUI();

void initSettingModule()
{
  bindButtonHandlers(goSetting, &initMenu, prevSettingOption, nextSettingOption);
  drawSettingUI();
  setSystemState(SystemState::IDLE);
}

void drawSettingUI()
{
  clearScreen();
  drawNavBar(setting_name);
  drawBottomMenu(currentSettingIndex, settingsCount);
  DisplayValueFunc action = (DisplayValueFunc)pgm_read_ptr(&settings[currentSettingIndex].displayValue);
  if (action != nullptr)
    action();
}

void goSetting()
{
  DisplayValueFunc action = (DisplayValueFunc)pgm_read_ptr(&settings[currentSettingIndex].settingValue);
  if (action != nullptr)
    action();
}

void prevSettingOption()
{
  setSystemState(SystemState::IDLE);
  currentSettingIndex = (currentSettingIndex + settingsCount - 1) % settingsCount;
  drawSettingUI();
}

void nextSettingOption()
{
  setSystemState(SystemState::IDLE);
  currentSettingIndex = (currentSettingIndex + 1) % settingsCount;
  drawSettingUI();
}