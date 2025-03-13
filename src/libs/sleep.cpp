#include "sleep.h"
#include "display.h"
#include <avr/sleep.h>
#include "../modules/menu/menu.h"

bool _isSleeping = false;
bool _isWakingUp = false;

bool isSleeping()
{
  return _isSleeping;
}

void checkSleep()
{
  if (!_isSleeping && millis() > 30000)
  { // 30秒无操作
    goSleep();
  }
}

void goSleep()
{
  clearScreen();
  drawText(36, 18, "Sleeping...");
  display.display();
  delay(500);
  display.ssd1306_command(SSD1306_DISPLAYOFF);
  _isSleeping = true;

  // **配置 PCINT 作为唤醒源**
  cli();
  PCICR |= (1 << PCIE2); // **使能 PCINT2（PD2-PD7）**
  sei();

  // **设置深度睡眠模式**
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
  sleep_enable();

  // **进入睡眠**
  sleep_cpu();

  // **当 PCINT 触发时，单片机会唤醒**
  sleep_disable();
}

void wakeUp()
{
  if (_isSleeping)
  {
    _isSleeping = false;
    _isWakingUp = true;
    // drawMenu();
  }
}

void updateSleep()
{
  if (_isWakingUp)
  {
    _isWakingUp = false;
    display.ssd1306_command(SSD1306_DISPLAYON);
    drawMenu();
  }
}