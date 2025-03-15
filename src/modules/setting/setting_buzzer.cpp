#include "setting_buzzer.h"
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

void settingBuzzerValueCommit();
void settingBuzzerValueReset();
void settingBuzzerValuePrev();
void settingBuzzerValueNext();
void displayBuzzerValueOptions();

const uint8_t settingBuzzerOptionsCount = sizeof(setting_buzzer_options);
uint8_t currentSettingOptionIndex = 0;

void displayBuzzerValue()
{
  char buffer[20];
  strcpy_P(buffer, setting_buzzer);
  drawText(0, 20, buffer);

  bool buzzerEnabled = getBuzzerState();
  sprintf(buffer, "%s", buzzerEnabled ? strcpy_P(buffer, setting_buzzer_on) : strcpy_P(buffer, setting_buzzer_off));
  int16_t textWidth = strlen(buffer) * CHAR_WIDTH;
  int16_t x = (SCREEN_WIDTH - textWidth) / 2; // **居中对齐 X 坐标**
  display.setTextSize(2);
  display.setCursor(x, 36); // **设置居中 X 坐标**
  display.print(buffer);
  display.display();
}

void settingBuzzerValue()
{
  previousHandlers[0] = onOkPress;
  previousHandlers[1] = onCancelPress;
  previousHandlers[2] = onLeftPress;
  previousHandlers[3] = onRightPress;

  bindButtonHandlers(settingBuzzerValueCommit, settingBuzzerValueReset, settingBuzzerValuePrev, settingBuzzerValueNext);
  setSystemState(SystemState::IDLE);

  currentSettingOptionIndex = getBuzzerState() ? 0 : 1;
  displayBuzzerValueOptions();
}

void displayBuzzerValueOptions()
{
  char buffer[20];
  display.fillRect(24, 32, SCREEN_WIDTH - 24 * 2, 24, SSD1306_WHITE);
  strcpy_P(buffer, currentSettingOptionIndex == 0 ? setting_buzzer_on : setting_buzzer_off);
  int16_t textWidth = strlen(buffer) * CHAR_WIDTH;
  int16_t x = (SCREEN_WIDTH - textWidth) / 2; // **居中对齐 X 坐标**
  drawAdjustArrows();
  display.setTextSize(2);
  display.setTextColor(SSD1306_BLACK);
  display.setCursor(x, 36); // **设置居中 X 坐标**
  display.print(buffer);
  display.display();
}

void settingBuzzerValueNext()
{
  currentSettingOptionIndex = (currentSettingOptionIndex + 1) % settingBuzzerOptionsCount;
  setSystemState(SystemState::IDLE);
  displayBuzzerValueOptions();
}

void settingBuzzerValuePrev()
{
  currentSettingOptionIndex = (currentSettingOptionIndex + settingBuzzerOptionsCount - 1) % settingBuzzerOptionsCount;
  setSystemState(SystemState::IDLE);
  displayBuzzerValueOptions();
}

void settingBuzzerValueReset()
{
  bindButtonHandlers(previousHandlers[0], previousHandlers[1], previousHandlers[2], previousHandlers[3]);
  setSystemState(SystemState::IDLE);
  clearScreen();
  drawSettingUI();
}

void settingBuzzerValueCommit()
{
  setSystemState(SystemState::IDLE);
  bool buzzerEnabled = currentSettingOptionIndex == 0;
  setBuzzerState(buzzerEnabled);
  settingBuzzerValueReset();
}