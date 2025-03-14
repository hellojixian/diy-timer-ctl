#include "setting_sleep_timeout.h"
#include "../../libs/display.h"
#include "../../libs/input.h"
#include "../../libs/sleep.h"
#include "../../libs/setting.h"

void displaySleepTimeoutValue()
{
  char buffer[20];
  strcpy_P(buffer, setting_sleep_timeout);
  drawText(0, 20, buffer);

  unsigned int sleepTimeout = getSleepTimeout();
  sprintf(buffer, "%03u", sleepTimeout);
  drawText(46, 36, buffer, 2);
}

void settingSleepTimeoutValue()
{
}