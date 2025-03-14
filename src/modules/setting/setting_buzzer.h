#ifndef SETTING_BUZZER_H
#define SETTING_BUZZER_H
#include <avr/pgmspace.h>

const char setting_buzzer[] PROGMEM = "Buzzer";
void displayBuzzerValue();
void settingBuzzerValue();

#endif // SETTING_BUZZER_H