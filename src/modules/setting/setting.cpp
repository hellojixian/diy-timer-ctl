#include <Arduino.h>
#include "setting.h"
#include "../../libs/display.h"
#include "../../libs/input.h"
#include "../../libs/sleep.h"
#include "../../libs/setting.h"
#include "../menu/menu.h"

const uint8_t settingsCount = sizeof(settings) / sizeof(SettingItem);
uint8_t currentSettingIndex = 0;

void goBack();
void goSetting();
void prevSettingOption();
void nextSettingOption();
void drawSettingUI();

void initSettingModule()
{
  bindButtonHandlers(&initMenu, goSetting, prevSettingOption, nextSettingOption);
  drawSettingUI();
  setSystemState(SystemState::IDLE);
}

void drawSettingUI()
{
  clearScreen();
  drawBottomMenu(currentSettingIndex, settingsCount);
}
