#ifndef SETTING_TRIGGER_INTERVAL_H
#define SETTING_TRIGGER_INTERVAL_H

#include <avr/pgmspace.h>

#define TRIGGER_INTERVAL_MIN 1
#define TRIGGER_INTERVAL_MAX 60

const char setting_trigger_interval[] PROGMEM = "Triger Interval (sec)";

void displayTriggerIntervalValue();
void settingTriggerIntervalValue();

#endif // SETTING_TRIGGER_INTERVAL_H