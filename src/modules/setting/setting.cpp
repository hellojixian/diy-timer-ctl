#include <Arduino.h>
#include "setting.h"
#include "../../libs/display.h"
#include "../../libs/input.h"
#include "../../libs/sleep.h"
#include "../../libs/setting.h"
#include "../menu/menu.h"

const uint8_t settingsCount = sizeof(settings) / sizeof(SettingItem);
uint8_t currentSettingIndex = 0;

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
  action();
}

void goSetting()
{
  DisplayValueFunc action = (DisplayValueFunc)pgm_read_ptr(&settings[currentSettingIndex].displayValue);
  action();
}

void prevSettingOption()
{
  currentSettingIndex = (currentSettingIndex + settingsCount - 1) % settingsCount;
  drawSettingUI();
}

void nextSettingOption()
{
  currentSettingIndex = (currentSettingIndex + 1) % settingsCount;
  drawSettingUI();
}