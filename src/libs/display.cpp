#include "display.h"
#include "setting.h"
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
  setScreenBrightness(getScreenBrightness());
  display.clearDisplay();
  display.display();
}

void setDisplayScreenBrightness(uint8_t brightness)
{
  Serial.print(F("Setting brightness to: "));
  Serial.println(brightness);
  display.ssd1306_command(SSD1306_SETCONTRAST);
  display.ssd1306_command(brightness);
}

void drawText(int x, int y, const char *text, int size = 1)
{
  display.setTextSize(size);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(x, y);
  display.print(text);
  display.display();
}

void drawNavBar(const char *name)
{
  char buffer[30]; // 定义缓冲区来读取 PROGMEM 字符串
  strcpy_P(buffer, PSTR("> "));
  strcat_P(buffer, name); // 在运行时拼接字符串
  drawText(0, 0, buffer);
  display.drawLine(0, 12, SCREEN_WIDTH, 12, SSD1306_WHITE);
  display.display();
}

void drawAdjustArrows(int y_pos = 36)
{
  char buffer[2];
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, y_pos);
  strcpy_P(buffer, PSTR("<"));
  display.print(buffer);
  display.display();
  display.setCursor(SCREEN_WIDTH - 12, y_pos);
  strcpy_P(buffer, PSTR(">"));
  display.print(buffer);
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

unsigned int alignCenter(const char *text, int size = 1)
{
  int char_width = 6 * size;
  int16_t textWidth = strlen(text) * char_width;
  return (SCREEN_WIDTH - textWidth) / 2;
}
