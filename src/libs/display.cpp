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

void drawNavBar(const char *name)
{
  char buffer[10]; // 定义缓冲区来读取 PROGMEM 字符串
  strcpy_P(buffer, PSTR("> "));
  strcat_P(buffer, name); // 在运行时拼接字符串
  drawText(0, 0, buffer);
  display.drawLine(0, 12, SCREEN_WIDTH, 12, SSD1306_WHITE);
  display.display();
}

void drawBottomMenu(int currentIndex, int totalItems)
{
  int menu_width = SCREEN_WIDTH / totalItems;
  int menu_item_height = 3;
  for (int i = 0; i < totalItems; i++)
  {
    display.drawLine(i * menu_width + 1, SCREEN_HEIGHT - 2, i * menu_width + menu_width - 2, SCREEN_HEIGHT - 2, SSD1306_WHITE);
  }
  display.fillRect(currentIndex * menu_width + 1, SCREEN_HEIGHT - menu_item_height, menu_width - 2, SCREEN_HEIGHT - menu_item_height, SSD1306_WHITE);
  display.display();
}

void clearScreen()
{
  display.clearDisplay();
  display.display();
}
