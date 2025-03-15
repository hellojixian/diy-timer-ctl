#include "info.h"
#include "../../libs/display.h"
#include "../../libs/sleep.h"
#include "../../libs/input.h"
#include "../../libs/memory.h"
#include "../menu/menu.h"

#include <avr/pgmspace.h>

extern Adafruit_SSD1306 display;
void drawInfoUI();

// 将字符串存储在 PROGMEM
const char info_diy_timer[] PROGMEM = " DIY Timer Controller";
const char info_author[] PROGMEM = " by Jixian Wang";
const char info_version[] PROGMEM = " Version: 1.0.0";
const char info_release[] PROGMEM = " Release: Mar, 2025";

void initInfoModule()
{
  bindButtonHandlers(&resetSystem, &resetSystem, nullptr, nullptr);
  drawInfoUI();
  setSystemState(SystemState::IDLE);
}

void drawInfoUI()
{
  clearScreen();
  char buffer[30]; // 定义缓冲区来读取 PROGMEM 字符串

  drawNavBar(info_name);

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
  display.display();
}
