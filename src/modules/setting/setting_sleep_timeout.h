#ifndef SETTING_SLEEP_TIMEOUT_H
#define SETTING_SLEEP_TIMEOUT_H

#include <avr/pgmspace.h>

const char setting_sleep_timeout[] PROGMEM = "Sleep Timeout (sec)";
void displaySleepTimeoutValue();
void settingSleepTimeoutValue();

#endif // SETTING_SLEEP_TIMEOUT_H