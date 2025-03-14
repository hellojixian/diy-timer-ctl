#include "setting_buzzer.h"
#include "../../libs/display.h"
#include "../../libs/input.h"
#include "../../libs/sleep.h"
#include "../../libs/setting.h"

#define CHAR_WIDTH 12

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
}