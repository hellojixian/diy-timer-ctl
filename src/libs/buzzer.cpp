#include "buzzer.h"
#include "hal.h"
#include "setting.h"

void playTone(int frequency, int duration);

void playOnCompletedTone()
{
  static uint32_t lastPlayTime = 0; // 记录上次播放时间
  uint32_t currentTime = millis();

  if (getBuzzerState() && (currentTime - lastPlayTime >= 1000)) // 限制 1 秒内只能触发一次
  {
    lastPlayTime = currentTime; // 更新上次触发时间

    playTone(2000, 50);
    delay(100);
    playTone(5000, 50);
    delay(100);
    playTone(3000, 50);
    delay(100);
  }
}

void playTriggerTone()
{
  if (getBuzzerState())
    playTone(3000, 50);
}

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