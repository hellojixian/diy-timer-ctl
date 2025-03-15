#include "src/libs/display.h"
#include "src/libs/hal.h"
#include "src/libs/input.h"
#include "src/libs/sleep.h"
#include "src/libs/memory.h"
#include "src/libs/setting.h"
#include "src/modules/menu/menu.h"

void setup()
{
  Serial.begin(115200);
  initHardware();
  initSettings();
  initInput();
  initDisplay();
  initMenu();
  initSleepManager();
  checkMemory();
}

void loop()
{
  handleInput();
  updateSleep();
}
