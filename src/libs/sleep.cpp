#include "sleep.h"
#include "display.h"
#include "setting.h"
#include <avr/sleep.h>
#include "../modules/menu/menu.h"

static SystemState currentState = SystemState::IDLE; // **默认状态为繁忙**
volatile unsigned long lastIdleTime = 0;             // **上次进入空闲状态的时间**
unsigned int sleepTimeout = 0;

// **设置系统状态**
void setSystemState(SystemState state)
{
  currentState = state;
  if (state == SystemState::IDLE)
  {
    lastIdleTime = millis(); // **记录空闲开始时间**
  }
}

bool _isSleeping = false;
bool _isWakingUp = false;

void initSleepManager()
{
  // **配置 PCINT 作为唤醒源**
  cli();
  PCICR |= (1 << PCIE2); // **使能 PCINT2（PD2-PD7）**
  sei();

  sleepTimeout = getSleepTimeout();
}

bool isSleeping()
{
  return _isSleeping;
}

void goSleep()
{
  clearScreen();
  drawText(36, 18, "Sleeping...");
  display.display();
  delay(500);
  display.ssd1306_command(SSD1306_DISPLAYOFF);
  _isSleeping = true;

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
  }
}

void updateSleep()
{
  unsigned long ms = millis() + 100;
  if (_isWakingUp)
  {
    _isWakingUp = false;
    clearScreen();
    display.ssd1306_command(SSD1306_DISPLAYON);
    lastIdleTime = millis();
    drawMenu();
  }
  else
  {
    if (sleepTimeout != 0 && currentState == SystemState::IDLE && (ms - lastIdleTime > sleepTimeout))
    {
      goSleep();
    }
  }
}