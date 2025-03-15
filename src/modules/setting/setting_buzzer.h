#ifndef SETTING_BUZZER_H
#define SETTING_BUZZER_H
#include <avr/pgmspace.h>

const char setting_buzzer[] PROGMEM = "Buzzer";
const char setting_buzzer_on[] PROGMEM = "ON";
const char setting_buzzer_off[] PROGMEM = "OFF";
const char setting_buzzer_options[] = {setting_buzzer_on, setting_buzzer_off};

void displayBuzzerValue();
void settingBuzzerValue();

#endif // SETTING_BUZZER_H