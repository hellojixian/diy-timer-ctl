#include "src/libs/display.h"
#include "src/libs/hal.h"
#include "src/libs/input.h"
#include "src/modules/menu/menu.h"

void setup()
{
  Serial.begin(115200);
  initHardware();
  initInput();
  initDisplay();
  initMenu();
}

void loop()
{
}
