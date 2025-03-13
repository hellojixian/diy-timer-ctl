#ifndef SETTING_H
#define SETTING_H

#define EEPROM_BUZZER_ADDR 0 // **EEPROM 里存储蜂鸣器状态的位置**
#define EEPROM_SLEEP_ADDR 10 // **EEPROM 里存储睡眠超时时间的位置**

bool getBuzzerState();
void setBuzzerState(bool enabled);

unsigned int getSleepTimeout();
void setSleepTimeout(unsigned int seconds);

#endif