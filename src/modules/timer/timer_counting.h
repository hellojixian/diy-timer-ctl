#ifndef TIMER_COUNTING_H
#define TIMER_COUNTING_H

#include <avr/pgmspace.h>

const char timer_counting_name[] PROGMEM = "Counting: %02u:00";
const char timer_minute_format[] PROGMEM = "%02u:00";
const char timer_counting_completed[] PROGMEM = "DONE!";
void startTimerCounting();
void updateTimer();
#endif