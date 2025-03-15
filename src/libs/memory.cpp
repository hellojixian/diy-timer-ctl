#include "memory.h"
#include <Arduino.h>
#include <avr/wdt.h>
#include <avr/io.h>

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

void resetSystem()
{
  cli();                 // 关闭全局中断
  wdt_enable(WDTO_15MS); // 启动看门狗，15ms 后复位
  while (1)
    ; // 等待复位
}