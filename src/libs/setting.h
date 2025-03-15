#ifndef SETTING_H
#define SETTING_H

#define EEPROM_BUZZER_ADDR 0            // **EEPROM 里存储蜂鸣器状态的位置**
#define EEPROM_SLEEP_ADDR 10            // **EEPROM 里存储睡眠超时时间的位置**
#define EEPROM_TRIGGER_INTERVAL_ADDR 20 // **EEPROM 里存储触发间隔的位置**
#define EEPROM_TIMER_SETTING_ADDR 30

#define DEFAULT_SLEEP_TIMEOUT 30
#define DEFAULT_TRIGGER_INTERVAL 10
#define DEFAULT_TIMER_SETTING 10
#define DEFAULT_BUZZER_STATE true

void initSettings();

bool getBuzzerState();
void setBuzzerState(bool enabled);

unsigned int getSleepTimeout();
void setSleepTimeout(unsigned int seconds);

unsigned int getTriggerInterval();
void setTriggerInterval(unsigned int seconds);

unsigned int getTimerSetting();
void setTimerSetting(unsigned int minutes);

#endif