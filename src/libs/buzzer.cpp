#include "buzzer.h"
#include "hal.h"
#include "setting.h"

void playTone(int frequency, int duration);

void playButtonTone()
{
  if (getBuzzerState())
    playTone(1500, 100);
}

void playOKTone()
{
  if (getBuzzerState())
    playTone(2000, 100);
}

void playCancelTone()
{
  if (getBuzzerState())
    playTone(1000, 100);
}

// // 播放指定频率和时长的提示音
void playTone(int frequency, int duration)
{
  int period = 1000000 / frequency;
  int half_period = period / 2;
  long cycles = (long)duration * 1000 / period;

  for (long i = 0; i < cycles; i++)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(half_period);
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(half_period);
  }
}
