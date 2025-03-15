#ifndef DISPLAY_H
#define DISPLAY_H

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

extern Adafruit_SSD1306 display;

void initDisplay();
void drawText(int x, int y, const char *text, int size = 1);
void drawNavBar(const char *name);
void drawBottomMenu(int currentIndex, int totalItems);
void drawAdjustArrows(int y_pos = 36);
void clearScreen();
unsigned int alignCenter(const char *text, int size = 1);
#endif
