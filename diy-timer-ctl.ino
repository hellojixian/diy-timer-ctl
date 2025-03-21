#include "src/libs/display.h"
#include "src/libs/hal.h"
#include "src/libs/input.h"
#include "src/libs/sleep.h"
#include "src/libs/memory.h"
#include "src/libs/setting.h"
#include "src/modules/menu/menu.h"
#include "src/modules/timer/timer_counting.h"

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
  Serial.println(F("System started"));
  // digitalWrite(CTL_OUTPUT_PIN, HIGH);
}

void loop()
{
  handleInput();
  updateSleep();
  updateTimer();
}
