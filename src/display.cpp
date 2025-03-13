#include "display.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/U8X8_PIN_NONE);

void drawText(int x, int y, const char *text)
{
  u8g2.clearBuffer();
  u8g2.setCursor(x, y);
  u8g2.print(text);
  u8g2.sendBuffer();
}

void clearScreen()
{
  u8g2.clearBuffer();
  u8g2.sendBuffer();
}
