#include "src/libs/display.h"
#include "src/libs/hal.h"
#include "src/libs/input.h"
#include "src/libs/sleep.h"
#include "src/modules/menu/menu.h"

int freeMemory()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void checkMemory()
{
  int ram = freeMemory();
  Serial.print(F("Free RAM: ")); // 使用 F() 宏，减少 RAM 占用
  Serial.print(ram);
  Serial.println(F(" bytes"));
}

void setup()
{
  Serial.begin(115200);
  initHardware();
  initInput();
  initDisplay();
  initMenu();
  checkMemory(); // **初始化后再检查**
}

void loop()
{
  updateMenu();
  updateSleep();
}
