#include "setting_trigger_interval.h"
#include "../../libs/display.h"
#include "../../libs/input.h"
#include "../../libs/sleep.h"
#include "../../libs/setting.h"

void displayTriggerIntervalValue()
{
  char buffer[20];
  strcpy_P(buffer, setting_trigger_interval);
  drawText(0, 20, buffer);

  unsigned int triggerInterval = getTriggerInterval();
  sprintf(buffer, "%03u", triggerInterval); // 格式化成3位数字，前面补零
  drawText(46, 36, buffer, 2);
}

void settingTriggerIntervalValue()
{
}
