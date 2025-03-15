#include "timer.h"
#include "timer_counting.h"
#include "../../libs/display.h"
#include "../../libs/sleep.h"
#include "../../libs/input.h"
#include "../../libs/setting.h"
#include "../../libs/memory.h"
#include "../menu/menu.h"

void startTimer();
void timerSettingIncrement();
void timerSettingDecrement();
void displayTimerSettingValue();
void drawTimerUI();

unsigned int currentTimerSetting = 0;

void initTimerModule()
{
  bindButtonHandlers(&startTimer, &resetSystem, &timerSettingDecrement, &timerSettingIncrement);
  currentTimerSetting = getTimerSetting();
  drawTimerUI();
  setSystemState(SystemState::IDLE);
}

void drawTimerUI()
{
  clearScreen();
  drawNavBar(timer_name);
  char buffer[20];
  strcpy_P(buffer, setting_timer);
  drawText(0, 16, buffer);
  display.display();
  displayTimerSettingValue();
}

void displayTimerSettingValue()
{
  display.fillRect(24, 28, SCREEN_WIDTH - 24 * 2, 23, SSD1306_WHITE);
  drawAdjustArrows(32);

  char buffer[20];
  sprintf(buffer, "%03u", currentTimerSetting);
  display.setTextSize(2);
  display.setTextColor(SSD1306_BLACK);
  display.setCursor(alignCenter(buffer, 2), 32); // **设置居中 X 坐标**
  display.print(buffer);
  display.display();

  int progress_width = map(currentTimerSetting, TIMER_SETTING_MIN, TIMER_SETTING_MAX - 1, 0, SCREEN_WIDTH);
  display.fillRect(0, SCREEN_HEIGHT - 4, SCREEN_WIDTH, 4, SSD1306_BLACK);
  display.drawLine(0, SCREEN_HEIGHT - 2, SCREEN_WIDTH, SCREEN_HEIGHT - 2, SSD1306_WHITE);
  display.fillRect(0, SCREEN_HEIGHT - 4, progress_width - 2, 4, SSD1306_WHITE);
  display.display();
}

void timerSettingIncrement()
{
  if (currentTimerSetting < TIMER_SETTING_MAX - 1)
  {
    currentTimerSetting++;
    setSystemState(SystemState::IDLE);
    displayTimerSettingValue();
  }
}

void timerSettingDecrement()
{
  if (currentTimerSetting > TIMER_SETTING_MIN)
  {
    currentTimerSetting--;
    setSystemState(SystemState::IDLE);
    displayTimerSettingValue();
  }
}

void startTimer()
{
  setTimerSetting(currentTimerSetting);
  setSystemState(SystemState::BUSY);
  startTimerCounting();
}