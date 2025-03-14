#include "info.h"
#include "../../libs/display.h"
#include "../../libs/sleep.h"
#include "../../libs/input.h"
#include "../menu/menu.h"

#include <avr/pgmspace.h>

extern Adafruit_SSD1306 display;
void goBack();
void drawUI();

// 将字符串存储在 PROGMEM
const char info_diy_timer[] PROGMEM = " DIY Timer Controller";
const char info_author[] PROGMEM = " by Jixian Wang";
const char info_version[] PROGMEM = " Version: 1.0.0";
const char info_release[] PROGMEM = " Release: Mar, 2025";

void initInfoModule()
{
  bindButtonHandlers(goBack, goBack, nullptr, nullptr);
  drawUI();
  setSystemState(SystemState::IDLE);
}

void drawUI()
{
  clearScreen();
  char buffer[30]; // 定义缓冲区来读取 PROGMEM 字符串

  strcpy_P(buffer, PSTR("> "));
  strcat_P(buffer, info_name); // 在运行时拼接字符串
  drawText(0, 0, buffer);
  display.drawLine(0, 12, SCREEN_WIDTH, 12, SSD1306_WHITE);
  int margin_top = 8;
  int line_height = 11;

  strcpy_P(buffer, info_diy_timer);
  drawText(0, margin_top + line_height * 1, buffer);

  strcpy_P(buffer, info_author);
  drawText(0, margin_top + line_height * 2, buffer);

  strcpy_P(buffer, info_version);
  drawText(0, margin_top + line_height * 3, buffer);

  strcpy_P(buffer, info_release);
  drawText(0, margin_top + line_height * 4, buffer);
}

void goBack()
{
  initMenu();
}
