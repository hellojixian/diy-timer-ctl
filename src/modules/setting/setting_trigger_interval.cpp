#include "setting_trigger_interval.h"
#include "setting.h"
#include "../../libs/display.h"
#include "../../libs/input.h"
#include "../../libs/sleep.h"
#include "../../libs/setting.h"

#define CHAR_WIDTH 12

extern ButtonCallback previousHandlers[4];
extern ButtonCallback onOkPress;
extern ButtonCallback onCancelPress;
extern ButtonCallback onLeftPress;
extern ButtonCallback onRightPress;

void displayTriggerIntervalValue();
void settingTriggerIntervalValue();
void settingTriggerIntervalValueNext();
void settingTriggerIntervalValuePrev();
void settingTriggerIntervalValueCommit();
void settingTriggerIntervalValueReset();
void displayTriggerIntervalValueOptions();

// 触发间隔值的最小和最大值
const uint8_t settingTriggerIntervalOptionsCount = TRIGGER_INTERVAL_MAX - TRIGGER_INTERVAL_MIN + 1;
uint8_t currentSettingTriggerIntervalOptionIndex = 0;

void displayTriggerIntervalValue()
{
  char buffer[20];
  strcpy_P(buffer, setting_trigger_interval);
  drawText(0, 20, buffer);

  unsigned int triggerInterval = getTriggerInterval();
  sprintf(buffer, "%03u", triggerInterval); // 格式化成3位数字，前面补零

  int16_t textWidth = strlen(buffer) * CHAR_WIDTH;
  int16_t x = (SCREEN_WIDTH - textWidth) / 2; // **居中对齐 X 坐标**
  display.setTextSize(2);
  display.setCursor(x, 36); // **设置居中 X 坐标**
  display.print(buffer);
  display.display();
}

void settingTriggerIntervalValue()
{
  // 备份按钮处理函数
  previousHandlers[0] = onOkPress;
  previousHandlers[1] = onCancelPress;
  previousHandlers[2] = onLeftPress;
  previousHandlers[3] = onRightPress;

  // 绑定新的按钮处理函数
  bindButtonHandlers(settingTriggerIntervalValueCommit, settingTriggerIntervalValueReset, settingTriggerIntervalValuePrev, settingTriggerIntervalValueNext);
  setSystemState(SystemState::IDLE);

  unsigned int triggerInterval = getTriggerInterval();

  // 计算 `currentSettingTriggerIntervalOptionIndex`
  if (triggerInterval < TRIGGER_INTERVAL_MIN)
  {
    currentSettingTriggerIntervalOptionIndex = 0;
  }
  else if (triggerInterval > TRIGGER_INTERVAL_MAX)
  {
    currentSettingTriggerIntervalOptionIndex = settingTriggerIntervalOptionsCount - 1;
  }
  else
  {
    currentSettingTriggerIntervalOptionIndex = triggerInterval - TRIGGER_INTERVAL_MIN;
  }

  displayTriggerIntervalValueOptions();
}

void displayTriggerIntervalValueOptions()
{
  display.fillRect(24, 32, SCREEN_WIDTH - 24 * 2, 23, SSD1306_WHITE);

  char buffer[4];
  sprintf(buffer, "%03u", TRIGGER_INTERVAL_MIN + currentSettingTriggerIntervalOptionIndex); // 格式化值
  int16_t textWidth = strlen(buffer) * CHAR_WIDTH;
  int16_t x = (SCREEN_WIDTH - textWidth) / 2; // **居中对齐 X 坐标**

  drawAdjustArrows();
  display.setTextSize(2);
  display.setTextColor(SSD1306_BLACK);
  display.setCursor(x, 36); // **设置居中 X 坐标**
  display.print(buffer);
  display.display();
}

void settingTriggerIntervalValueNext()
{
  if (currentSettingTriggerIntervalOptionIndex < settingTriggerIntervalOptionsCount - 1)
  {
    currentSettingTriggerIntervalOptionIndex++;
    setSystemState(SystemState::IDLE);
    displayTriggerIntervalValueOptions();
  }
}

void settingTriggerIntervalValuePrev()
{
  if (currentSettingTriggerIntervalOptionIndex > 0)
  {
    currentSettingTriggerIntervalOptionIndex--;
    setSystemState(SystemState::IDLE);
    displayTriggerIntervalValueOptions();
  }
}

void settingTriggerIntervalValueReset()
{
  // 恢复原来的按钮处理函数
  bindButtonHandlers(previousHandlers[0], previousHandlers[1], previousHandlers[2], previousHandlers[3]);
  setSystemState(SystemState::IDLE);
  clearScreen();
  drawSettingUI();
}

void settingTriggerIntervalValueCommit()
{
  setSystemState(SystemState::IDLE);
  unsigned int newTriggerInterval = TRIGGER_INTERVAL_MIN + currentSettingTriggerIntervalOptionIndex;
  setTriggerInterval(newTriggerInterval);
  settingTriggerIntervalValueReset();
}
