#ifndef SETTING_H
#define SETTING_H

#define EEPROM_BUZZER_ADDR 0 // **EEPROM 里存储蜂鸣器状态的位置**

bool getBuzzerState();
void setBuzzerState(bool enabled);

#endif