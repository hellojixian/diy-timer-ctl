#include "timer_counting.h"
#include "timer.h"
#include "../menu/menu_items.h"
#include "../../libs/display.h"
#include "../../libs/sleep.h"
#include "../../libs/input.h"
#include "../../libs/buzzer.h"
#include "../../libs/setting.h"
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

volatile bool isCompleted = false;
volatile bool isCounting = false;
volatile unsigned int timerCountSeconds = 0;
volatile unsigned int timerTriggerInterval = 0;

void startTimerCounting()
{
  previousHandlers[0] = onOkPress;
  previousHandlers[1] = onCancelPress;
  previousHandlers[2] = onLeftPress;
  previousHandlers[3] = onRightPress;

  bindButtonHandlers(nullptr, cancelTimerCounting, nullptr, nullptr);
  setSystemState(SystemState::BUSY);

  timerCountSeconds = getTimerSetting() * 60;
  timerTriggerInterval = getTriggerInterval();
  isCounting = true;

  triggerSignal();
  drawTimerCountingUIFrame();
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
  char buffer[30];
  char tempString[20];
  strcpy_P(tempString, timer_counting_name); // 读取 "Counting: %d mins"
  sprintf(buffer, tempString, getTimerSetting());
  drawText(0, 16, buffer);
  display.display();
}

void drawTimerCountingUI()
{
  unsigned int totalSeconds = getTimerSetting() * 60;             // 获取总计时秒数
  unsigned int elapsedSeconds = totalSeconds - timerCountSeconds; // 计算已过去时间

  // 进度条更新（基于已用时间，而不是剩余时间）
  unsigned int progress = map(elapsedSeconds, 0, totalSeconds, 0, SCREEN_WIDTH);
  unsigned int progrssHeight = 5;
  display.drawLine(0, SCREEN_HEIGHT - 1, SCREEN_WIDTH, SCREEN_HEIGHT - 1, SSD1306_WHITE);
  display.drawLine(0, SCREEN_HEIGHT - progrssHeight, SCREEN_WIDTH, SCREEN_HEIGHT - progrssHeight, SSD1306_WHITE);
  display.fillRect(0, SCREEN_HEIGHT - progrssHeight, progress, progrssHeight, SSD1306_WHITE);
  display.display();

  char buffer[20];                                                        // 存储格式化的时间
  sprintf(buffer, "%02u:%02u", elapsedSeconds / 60, elapsedSeconds % 60); // 02u 保持两位数格式
  display.fillRect(34, 32, 60, 24, SSD1306_BLACK);
  display.display();
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
  char buffer[30];
  char tempString[20];

  strcpy_P(buffer, timer_counting_completed);
  drawText(60, 18, buffer);
  strcpy_P(tempString, timer_minute_format); // 读取 "Counting: %d mins"
  sprintf(buffer, tempString, getTimerSetting());
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