#include "sleep.h"
#include "display.h"
#include "menu.h"
#include <avr/sleep.h>

bool isSleeping = false;

void checkSleep()
{
  if (!isSleeping && millis() > 30000)
  { // 30秒无操作
    isSleeping = true;
    clearScreen();
    drawText(40, 30, "Sleeping...");
    delay(500);
    sleep_mode();
  }
}

void wakeUp()
{
  if (isSleeping)
  {
    isSleeping = false;
    drawMenu();
  }
}
