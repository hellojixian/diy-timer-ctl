#ifndef SETTING_SLEEP_TIMEOUT_H
#define SETTING_SLEEP_TIMEOUT_H

#include <avr/pgmspace.h>

const char setting_sleep_timeout[] PROGMEM = "Sleep Timeout (sec)";
const char setting_sleep_timeout_off[] PROGMEM = "OFF";
const char setting_sleep_timeout_10[] PROGMEM = "10";
const char setting_sleep_timeout_20[] PROGMEM = "20";
const char setting_sleep_timeout_30[] PROGMEM = "30";
const char setting_sleep_timeout_60[] PROGMEM = "60";
const char *const setting_sleep_timeout_options[] PROGMEM = {
    setting_sleep_timeout_off,
    setting_sleep_timeout_10,
    setting_sleep_timeout_20,
    setting_sleep_timeout_30,
    setting_sleep_timeout_60};

void displaySleepTimeoutValue();
void settingSleepTimeoutValue();

#endif // SETTING_SLEEP_TIMEOUT_H