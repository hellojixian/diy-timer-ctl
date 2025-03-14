#ifndef SETTING_SLEEP_TIMEOUT_H
#define SETTING_SLEEP_TIMEOUT_H

#include <avr/pgmspace.h>

const char setting_trigger_interval[] PROGMEM = "Triger Interval (sec)";
void displayTriggerIntervalValue();
void settingTriggerIntervalValue();

#endif // SETTING_SLEEP_TIMEOUT_H