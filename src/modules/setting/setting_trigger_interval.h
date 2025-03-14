#ifndef SETTING_TRIGGER_INTERVAL_H
#define SETTING_TRIGGER_INTERVAL_H

#include <avr/pgmspace.h>

const char setting_sleep_timeout[] PROGMEM = "Sleep Timeout (sec)";
void displaySleepTimeoutlValue();
void settingSleepTimeoutlValue();

#endif // SETTING_TRIGGER_INTERVAL_H