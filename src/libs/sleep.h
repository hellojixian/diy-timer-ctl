#ifndef SLEEP_H
#define SLEEP_H

#include "hal.h"

// **系统状态枚举**
enum class SystemState
{
  IDLE, // **空闲**
  BUSY  // **繁忙**
};

bool isSleeping();
void wakeUp();
void goSleep();
void updateSleep();

void setSystemState(SystemState state);
SystemState getSystemState();

#endif // SLEEP_H
