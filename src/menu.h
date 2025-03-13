#ifndef MENU_H
#define MENU_H

#include <U8g2lib.h>
#include <LCDMenuLib2.h>

// 外部声明 OLED 屏幕对象
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
extern LCDMenuLib2 menu;

// 菜单初始化
void menuInit();

// 菜单绘制
void drawMenu();

// 按键操作方法
void menuSelect();
void cancelAction();
void menuNext();
void menuPrev();

#endif // MENU_H
