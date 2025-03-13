#ifndef MENU_H
#define MENU_H

#include <U8g2lib.h>
#include <LCDMenuLib2.h>
#include "modules/timer/menu_timer.h"
#include "modules/setting/menu_setting.h"
#include "modules/info/menu_info.h"

extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
extern LCDMenuLib2 menu;

void menuInit();
void drawMenu();

#endif // MENU_H
