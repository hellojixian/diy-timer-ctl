#include "setting_sleep_timeout.h"
#include "setting.h"
#include "../../libs/display.h"
#include "../../libs/input.h"
#include "../../libs/sleep.h"
#include "../../libs/setting.h"

#define CHAR_WIDTH 12

extern unsigned int sleepTimeout;

extern ButtonCallback previousHandlers[4];
extern ButtonCallback onOkPress;
extern ButtonCallback onCancelPress;
extern ButtonCallback onLeftPress;
extern ButtonCallback onRightPress;

void settingSleepTimeoutValueCommit();
void settingSleepTimeoutValueReset();
void settingSleepTimeoutValuePrev();
void settingSleepTimeoutValueNext();
void displaySleepTimeoutValueOptions();

const uint8_t settingSleepTimeoutOptionsCount = sizeof(setting_sleep_timeout_options) / sizeof(setting_sleep_timeout_options[0]);
uint8_t currentSettingSleepTimeoutOptionIndex = 0;

void displaySleepTimeoutValue()
{
  char buffer[20];
  strcpy_P(buffer, setting_sleep_timeout);
  drawText(0, 20, buffer);

  unsigned int sleepTimeout = getSleepTimeout();
  if (sleepTimeout == 0)
  {
    strcpy_P(buffer, setting_sleep_timeout_off);
  }
  else
  {
    sprintf(buffer, "%03u", sleepTimeout); // 格式化成3位数字，前面补零
  }
  int16_t textWidth = strlen(buffer) * CHAR_WIDTH;
  int16_t x = (SCREEN_WIDTH - textWidth) / 2; // **居中对齐 X 坐标**
  display.setTextSize(2);
  display.setCursor(x, 36); // **设置居中 X 坐标**
  display.print(buffer);
  display.display();
}

void settingSleepTimeoutValue()
{
  previousHandlers[0] = onOkPress;
  previousHandlers[1] = onCancelPress;
  previousHandlers[2] = onLeftPress;
  previousHandlers[3] = onRightPress;

  bindButtonHandlers(settingSleepTimeoutValueCommit, settingSleepTimeoutValueReset, settingSleepTimeoutValuePrev, settingSleepTimeoutValueNext);
  setSystemState(SystemState::IDLE);
  unsigned int sleepTimeout = getSleepTimeout();
  for (uint8_t i = 0; i < settingSleepTimeoutOptionsCount; i++)
  {
    char buffer[10];
    strcpy_P(buffer, (char *)pgm_read_ptr(&setting_sleep_timeout_options[i])); // 读取 PROGMEM 字符串
    // 判断是否匹配 `"OFF"` 或数值
    if ((strcmp(buffer, "OFF") == 0 && sleepTimeout == 0) || atoi(buffer) == sleepTimeout)
    {
      currentSettingSleepTimeoutOptionIndex = i;
      break; // 找到匹配项，跳出循环
    }
  }
  displaySleepTimeoutValueOptions();
}

void displaySleepTimeoutValueOptions()
{
  display.fillRect(24, 32, SCREEN_WIDTH - 24 * 2, 23, SSD1306_WHITE);
  char buffer[20];
  if (currentSettingSleepTimeoutOptionIndex == 0)
  {
    strcpy_P(buffer, setting_sleep_timeout_off);
  }
  else
  {
    strcpy_P(buffer, (char *)pgm_read_ptr(&setting_sleep_timeout_options[currentSettingSleepTimeoutOptionIndex]));
  }
  int16_t textWidth = strlen(buffer) * CHAR_WIDTH;
  int16_t x = (SCREEN_WIDTH - textWidth) / 2; // **居中对齐 X 坐标**
  drawAdjustArrows();
  display.setTextSize(2);
  display.setTextColor(SSD1306_BLACK);
  display.setCursor(x, 36); // **设置居中 X 坐标**
  display.print(buffer);
  display.display();
}

void settingSleepTimeoutValueNext()
{
  currentSettingSleepTimeoutOptionIndex = (currentSettingSleepTimeoutOptionIndex + 1) % settingSleepTimeoutOptionsCount;
  setSystemState(SystemState::IDLE);
  displaySleepTimeoutValueOptions();
}

void settingSleepTimeoutValuePrev()
{
  currentSettingSleepTimeoutOptionIndex = (currentSettingSleepTimeoutOptionIndex + settingSleepTimeoutOptionsCount - 1) % settingSleepTimeoutOptionsCount;
  setSystemState(SystemState::IDLE);
  displaySleepTimeoutValueOptions();
}

void settingSleepTimeoutValueReset()
{
  bindButtonHandlers(previousHandlers[0], previousHandlers[1], previousHandlers[2], previousHandlers[3]);
  setSystemState(SystemState::IDLE);
  clearScreen();
  drawSettingUI();
}

void settingSleepTimeoutValueCommit()
{
  setSystemState(SystemState::IDLE);
  char buffer[10]; // 存储转换的字符串
  if (currentSettingSleepTimeoutOptionIndex == 0)
  {
    setSleepTimeout(0);
  }
  else
  {
    strcpy_P(buffer, (char *)pgm_read_ptr(&setting_sleep_timeout_options[currentSettingSleepTimeoutOptionIndex]));
    setSleepTimeout(atoi(buffer)); // 将字符串转换为整数
  }
  sleepTimeout = getSleepTimeout();
  settingSleepTimeoutValueReset();
}