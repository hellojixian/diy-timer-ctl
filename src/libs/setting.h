#ifndef SETTING_H
#define SETTING_H

#define EEPROM_LAST_SELECTED_MENU_IDX_ADDR 0x0
#define EEPROM_BUZZER_ADDR 0x1           // **EEPROM 里存储蜂鸣器状态的位置**
#define EEPROM_SLEEP_ADDR 0x2            // **EEPROM 里存储睡眠超时时间的位置**
#define EEPROM_TRIGGER_INTERVAL_ADDR 0x3 // **EEPROM 里存储触发间隔的位置**
#define EEPROM_TIMER_SETTING_ADDR 0x4
#define EEPROM_SCREEN_BRIGHTNESS_ADDR 0x5

#define DEFAULT_SLEEP_TIMEOUT 30
#define DEFAULT_TRIGGER_INTERVAL 10
#define DEFAULT_TIMER_SETTING 10
#define DEFAULT_SCREEN_BRIGHTNESS 127
#define DEFAULT_BUZZER_STATE true
#define DEFAULT_LAST_SELECTED_MENU_IDX 0

void initSettings();

bool getBuzzerState();
void setBuzzerState(bool enabled);

unsigned int getSleepTimeout();
void setSleepTimeout(unsigned int seconds);

unsigned int getTriggerInterval();
void setTriggerInterval(unsigned int seconds);

unsigned int getTimerSetting();
void setTimerSetting(unsigned int minutes);

unsigned int getScreenBrightness();
void setScreenBrightness(unsigned int brightness);

unsigned int getLastSelectedMenuIndex();
void setLastSelectedMenuIndex(unsigned int index);

#endif