#include "memory.h"
#include <Arduino.h>

int freeMemory()
{
  extern int __heap_start, *__brkval;
  int v;
  return (int)&v - (__brkval == 0 ? (int)&__heap_start : (int)__brkval);
}

void checkMemory()
{
  int ram = freeMemory();
  Serial.begin(115200);
  Serial.print(F("Free RAM: ")); // 使用 F() 宏，减少 RAM 占用
  Serial.print(ram);
  Serial.println(F(" bytes"));
}