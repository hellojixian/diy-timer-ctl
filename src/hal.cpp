#include "hal.h"

void initHardware()
{
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BTN_CANCEL, INPUT_PULLUP);
  pinMode(BTN_OK, INPUT_PULLUP);
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);
  pinMode(CTL_OUTPUT_PIN, OUTPUT);
}
