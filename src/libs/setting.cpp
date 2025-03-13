#include "setting.h"
#include <Arduino.h>
#include <EEPROM.h>

void setBuzzerState(bool enabled)
{
  EEPROM.write(EEPROM_BUZZER_ADDR, enabled ? 1 : 0);
}

bool getBuzzerState()
{
  uint8_t storedValue = EEPROM.read(EEPROM_BUZZER_ADDR); // **从 EEPROM 读取值**
  return storedValue != 0;                               // **返回存储的值（1 = 开启，0 = 关闭）**
}
