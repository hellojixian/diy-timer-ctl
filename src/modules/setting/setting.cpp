#include <Arduino.h>
#include "setting.h"
#include "../../libs/display.h"
#include "../../libs/input.h"
#include "../../libs/sleep.h"
#include "../../libs/setting.h"
#include "../../libs/memory.h"
#include "../menu/menu.h"

const uint8_t settingsCount = sizeof(settingActions) / sizeof(SettingAction);
uint8_t currentSettingIndex = 0;

ButtonCallback previousHandlers[4] = {nullptr, nullptr, nullptr, nullptr};

void goSetting();
void prevSettingOption();
void nextSettingOption();
void drawSettingUI();

void initSettingModule()
{
  bindButtonHandlers(goSetting, &resetSystem, prevSettingOption, nextSettingOption);
  drawSettingUI();
  setSystemState(SystemState::IDLE);
}

void drawSettingUI()
{
  clearScreen();
  drawNavBar(setting_name);
  drawBottomMenu(currentSettingIndex, settingsCount);

  DisplayValueFunc action = settingActions[currentSettingIndex].displayValue;
  if (action != nullptr)
    action();
}

void goSetting()
{
  DisplayValueFunc action = settingActions[currentSettingIndex].settingValue;
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