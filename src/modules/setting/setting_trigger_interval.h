#ifndef SETTING_TRIGGER_INTERVAL_H
#define SETTING_TRIGGER_INTERVAL_H

#include <avr/pgmspace.h>

const char setting_trigger_interval[] PROGMEM = "Triger Interval (sec)";
void displayTriggerIntervalValue();
void settingTriggerIntervalValue();

#endif // SETTING_TRIGGER_INTERVAL_H