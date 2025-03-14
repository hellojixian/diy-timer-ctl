#include <Arduino.h>
#include "setting.h"
#include "../../libs/display.h"
#include "../../libs/input.h"
#include "../../libs/sleep.h"
#include "../menu/menu.h"

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
}
