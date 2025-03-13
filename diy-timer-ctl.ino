#include "src/libs/display.h"
#include "src/libs/hal.h"
#include "src/libs/input.h"
#include "src/libs/sleep.h"
#include "src/libs/memory.h"
#include "src/modules/menu/menu.h"

void setup()
{
  Serial.begin(115200);
  initHardware();
  initInput();
  initDisplay();
  initMenu();
  initSleepManager();
  checkMemory(); // **初始化后再检查**
}

void loop()
{
  updateMenu();
  updateSleep();
}
