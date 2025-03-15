#include "setting.h"
#include "sleep.h"
#include <Arduino.h>
#include <EEPROM.h>

extern unsigned int sleepTimeout;

void initSettings()
{
  if (EEPROM.read(EEPROM_BUZZER_ADDR) == 255)
  {
    setBuzzerState(DEFAULT_BUZZER_STATE);
  }

  if (EEPROM.read(EEPROM_SLEEP_ADDR) == 255)
  {
    setSleepTimeout(DEFAULT_SLEEP_TIMEOUT);
  }

  if (EEPROM.read(EEPROM_TRIGGER_INTERVAL_ADDR) == 255)
  {
    setTriggerInterval(DEFAULT_TRIGGER_INTERVAL);
  }
}

void setBuzzerState(bool enabled)
{
  EEPROM.write(EEPROM_BUZZER_ADDR, enabled ? 1 : 0);
}

bool getBuzzerState()
{
  uint8_t storedValue = EEPROM.read(EEPROM_BUZZER_ADDR); // **从 EEPROM 读取值**
  return storedValue != 0;                               // **返回存储的值（1 = 开启，0 = 关闭）**
}

void setSleepTimeout(unsigned int seconds)
{

  EEPROM.write(EEPROM_SLEEP_ADDR, seconds);
  sleepTimeout = seconds;
}

unsigned int getSleepTimeout()
{
  uint8_t storedValue = EEPROM.read(EEPROM_SLEEP_ADDR); // **从 EEPROM 读取值**
  return storedValue;
}

void setTriggerInterval(unsigned int seconds)
{

  EEPROM.write(EEPROM_TRIGGER_INTERVAL_ADDR, seconds);
  sleepTimeout = seconds;
}

unsigned int getTriggerInterval()
{
  uint8_t storedValue = EEPROM.read(EEPROM_TRIGGER_INTERVAL_ADDR); // **从 EEPROM 读取值**
  return storedValue;
}
