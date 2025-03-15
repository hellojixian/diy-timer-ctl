#ifndef MENU_TIMER_H
#define MENU_TIMER_H

#define TIMER_SETTING_MIN 1
#define TIMER_SETTING_MAX 60

#include <avr/pgmspace.h>

// **系统状态枚举**
enum class TimerState
{
  IDLE, // **空闲**
  BUSY  // **繁忙**
};
const char setting_timer[] PROGMEM = "Countdown (min)";

void initTimerModule();

#endif // MENU_TIMER_H
