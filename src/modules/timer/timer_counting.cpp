#include "timer_counting.h"
#include "timer.h"
#include "../menu/menu_items.h"
#include "../../libs/display.h"
#include "../../libs/sleep.h"
#include "../../libs/input.h"
#include "../../libs/buzzer.h"
#include "../../libs/setting.h"
#include "../../libs/memory.h"
#include "../menu/menu.h"

extern ButtonCallback previousHandlers[4];
extern ButtonCallback onOkPress;
extern ButtonCallback onCancelPress;
extern ButtonCallback onLeftPress;
extern ButtonCallback onRightPress;

void drawTimerCountingUIFrame();
void drawTimerCountingUI();
void drawOnCompletedUI();
void cancelTimerCounting();
void onTimerCountingCompleted();
void triggerSignal();
void timerCountingSettingIncrement();
void timerCountingSettingDecrement();

volatile bool isCompleted = false;
volatile bool isCounting = false;
volatile unsigned int totalSeconds = 0;
volatile unsigned int elapsedSeconds = 0;
volatile unsigned int timerCountSeconds = 0;
volatile unsigned int timerTriggerInterval = 0;

void startTimerCounting()
{
  previousHandlers[0] = onOkPress;
  previousHandlers[1] = onCancelPress;
  previousHandlers[2] = onLeftPress;
  previousHandlers[3] = onRightPress;

  bindButtonHandlers(nullptr, cancelTimerCounting, timerCountingSettingDecrement, timerCountingSettingIncrement);
  setSystemState(SystemState::BUSY);

  totalSeconds = getTimerSetting() * 60; // 获取总计时秒数
  timerCountSeconds = getTimerSetting() * 60;
  timerTriggerInterval = getTriggerInterval();
  isCounting = true;

  triggerSignal();
  drawTimerCountingUIFrame();
  checkMemory();
}

void updateTimer()
{
  if (isCompleted)
  {
    onTimerCountingCompleted();
    return;
  }

  if (!isCounting)
    return;
  static uint32_t lastUpdateTime = 0; // 记录上次更新的时间
  uint32_t currentTime = millis();

  // **确保每秒只减少一次 timerCountSeconds**
  if (currentTime - lastUpdateTime >= 1000)
  {
    lastUpdateTime = currentTime; // **更新计时**
    timerCountSeconds--;          // **减少 1 秒**

    // **更新 UI**
    drawTimerCountingUI();

    // **检查是否需要触发事件**
    if (timerCountSeconds % timerTriggerInterval == 0)
    {
      triggerSignal(); // 可选，播放提示音
    }

    // **计时结束，调用 `timerCountingCompleted()`**
    if (timerCountSeconds == 0)
    {
      isCounting = false;
      isCompleted = true;
      drawOnCompletedUI();
    }
  }
}

void drawTimerCountingUIFrame()
{
  clearScreen();
  drawNavBar(timer_name);
  char buffer[40];
  char tempString[38];
  strcpy_P(tempString, timer_counting_name); // 读取 "Counting: %d mins"
  sprintf(buffer, tempString, getTimerSetting());
  drawText(0, 16, buffer);
  unsigned int progrssHeight = 5;
  display.drawLine(0, SCREEN_HEIGHT - 1, SCREEN_WIDTH, SCREEN_HEIGHT - 1, SSD1306_WHITE);
  display.drawLine(0, SCREEN_HEIGHT - progrssHeight, SCREEN_WIDTH, SCREEN_HEIGHT - progrssHeight, SSD1306_WHITE);
  display.display();
}

void drawTimerCountingUI()
{
  elapsedSeconds = totalSeconds - timerCountSeconds; // 计算已过去时间

  // 进度条更新（基于已用时间，而不是剩余时间）
  unsigned int progress = map(elapsedSeconds, 0, totalSeconds, 0, SCREEN_WIDTH);
  unsigned int progrssHeight = 5;
  display.fillRect(0, SCREEN_HEIGHT - progrssHeight, progress, progrssHeight, SSD1306_WHITE);

  display.fillRect(34, 32, 60, 24, SSD1306_BLACK);
  char buffer[40];
  char formatString[40]; // **确保足够存储 "%02u:%02u"**
  strcpy_P(formatString, timer_second_format);
  sprintf(buffer, formatString, elapsedSeconds / 60, elapsedSeconds % 60); // 02u 保持两位数格式

  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(34, 32);
  display.print(buffer);

  display.display();
}

void cancelTimerCounting()
{
  isCounting = false;
  isCompleted = false;
  bindButtonHandlers(previousHandlers[0], previousHandlers[1], previousHandlers[2], previousHandlers[3]);
  setSystemState(SystemState::IDLE);
  initTimerModule();
}

void drawOnCompletedUI()
{
  clearScreen();
  char buffer[40];

  strcpy_P(buffer, timer_counting_completed);
  drawText(60, 18, buffer);
  char formatString[10]; // **确保足够存储 "%02u:%02u"**
  strcpy_P(formatString, timer_minute_format);
  sprintf(buffer, formatString, getTimerSetting());
  drawText(60, 32, buffer, 2);

  // const uint8_t *icon = (const uint8_t *)pgm_read_ptr(&timer_icon); // 读取图标
  display.drawBitmap(10, 14, timer_icon, 40, 40, SSD1306_WHITE);
  display.display();
}

void onTimerCountingCompleted()
{
  playOnCompletedTone();
}

void triggerSignal()
{
  digitalWrite(CTL_OUTPUT_PIN, LOW);
  playTriggerTone();
  digitalWrite(CTL_OUTPUT_PIN, HIGH);
}

void timerCountingSettingIncrement()
{
  if (isCompleted)
    return;

  unsigned int currentSetting = getTimerSetting();
  if (currentSetting < TIMER_SETTING_MAX)
  {
    setTimerSetting(currentSetting + 1);
    timerCountSeconds += 60;
    totalSeconds = getTimerSetting() * 60; // 获取总计时秒数
    drawTimerCountingUIFrame();
  }
}
void timerCountingSettingDecrement()
{
  if (isCompleted)
    return;

  unsigned int currentSetting = getTimerSetting();
  unsigned int elapsedSeconds = currentSetting * 60 - timerCountSeconds;
  if (currentSetting > TIMER_SETTING_MIN && (currentSetting - 1 > elapsedSeconds / 60))
  {
    setTimerSetting(currentSetting - 1);
    timerCountSeconds -= 60;
    totalSeconds = getTimerSetting() * 60; // 获取总计时秒数
    drawTimerCountingUIFrame();
  }
}