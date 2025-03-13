#ifndef DISPLAY_H
#define DISPLAY_H
#include <U8g2lib.h>
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;


void drawText(int x, int y, const char *text);
void clearScreen();

#endif // DISPLAY_H
