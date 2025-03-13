#include "display.h"
#include "hal.h"

// 创建 `Adafruit_SSD1306` 对象
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void initDisplay()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C))
  {
    while (1)
      ; // 如果初始化失败，程序卡住
  }
  display.clearDisplay();
  display.display();
}

void drawText(int x, int y, const char *text)
{
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x, y);
  display.print(text);
  display.display();
}

void clearScreen()
{
  display.clearDisplay();
  display.display();
}
