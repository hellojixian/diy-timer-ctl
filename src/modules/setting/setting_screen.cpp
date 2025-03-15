#include "setting_screen.h"
#include "setting.h"
#include "../../libs/display.h"
#include "../../libs/input.h"
#include "../../libs/sleep.h"
#include "../../libs/setting.h"

extern ButtonCallback previousHandlers[4];
extern ButtonCallback onOkPress;
extern ButtonCallback onCancelPress;
extern ButtonCallback onLeftPress;
extern ButtonCallback onRightPress;

void settingScreenValueCommit();
void settingScreenValueReset();
void settingScreenValuePrev();
void settingScreenValueNext();
void displayScreenValueOptions();

uint8_t currentSettingScreenOptionIndex = 1; // 默认 MEDIUM

void displayScreenValue()
{
  char buffer[20];
  strcpy_P(buffer, setting_screen);
  drawText(0, 20, buffer);

  // **匹配当前亮度**
  uint8_t currentBrightness = getScreenBrightness();
  for (uint8_t i = 0; i < setting_screen_options_count; i++)
  {
    uint8_t value = pgm_read_byte(&setting_screen_options[i].value);
    if (value == currentBrightness)
    {
      currentSettingScreenOptionIndex = i;
      break;
    }
  }

  // **正确读取选项名称**
  const char *optionName = (const char *)pgm_read_ptr(&setting_screen_options[currentSettingScreenOptionIndex].name);

  // **拷贝 PROGMEM 字符串到 RAM**
  char nameBuffer[20];
  strcpy_P(nameBuffer, optionName);

  display.setTextSize(2);
  display.setCursor(alignCenter(nameBuffer, 2), 36);
  display.print(nameBuffer);
  display.display();
}

void settingScreenValue()
{
  // **备份当前按钮事件**
  previousHandlers[0] = onOkPress;
  previousHandlers[1] = onCancelPress;
  previousHandlers[2] = onLeftPress;
  previousHandlers[3] = onRightPress;

  bindButtonHandlers(settingScreenValueCommit, settingScreenValueReset, settingScreenValuePrev, settingScreenValueNext);
  setSystemState(SystemState::IDLE);

  displayScreenValueOptions();
}

void displayScreenValueOptions()
{
  char buffer[10];
  display.fillRect(24, 32, SCREEN_WIDTH - 24 * 2, 24, SSD1306_WHITE);

  // **正确读取选项名称**
  const char *optionName = (const char *)pgm_read_ptr(&setting_screen_options[currentSettingScreenOptionIndex].name);

  // **拷贝 PROGMEM 数据到 RAM**
  strcpy_P(buffer, optionName);

  drawAdjustArrows();
  display.setTextSize(2);
  display.setTextColor(SSD1306_BLACK);
  display.setCursor(alignCenter(buffer, 2), 36);
  display.print(buffer);
  display.display();
}

void settingScreenValueNext()
{
  currentSettingScreenOptionIndex = (currentSettingScreenOptionIndex + 1) % setting_screen_options_count;
  uint8_t brightnessValue = pgm_read_byte(&setting_screen_options[currentSettingScreenOptionIndex].value);
  setDisplayScreenBrightness(brightnessValue);
  setSystemState(SystemState::IDLE);
  displayScreenValueOptions();
}

void settingScreenValuePrev()
{
  currentSettingScreenOptionIndex = (currentSettingScreenOptionIndex + setting_screen_options_count - 1) % setting_screen_options_count;
  uint8_t brightnessValue = pgm_read_byte(&setting_screen_options[currentSettingScreenOptionIndex].value);
  setDisplayScreenBrightness(brightnessValue);
  setSystemState(SystemState::IDLE);
  displayScreenValueOptions();
}

void settingScreenValueReset()
{
  bindButtonHandlers(previousHandlers[0], previousHandlers[1], previousHandlers[2], previousHandlers[3]);
  setSystemState(SystemState::IDLE);
  clearScreen();
  drawSettingUI();
}

void settingScreenValueCommit()
{
  setSystemState(SystemState::IDLE);

  // **正确读取选项值**
  uint8_t brightnessValue = pgm_read_byte(&setting_screen_options[currentSettingScreenOptionIndex].value);

  // **应用新亮度**
  setScreenBrightness(brightnessValue);
  setDisplayScreenBrightness(brightnessValue);
  settingScreenValueReset();
}
