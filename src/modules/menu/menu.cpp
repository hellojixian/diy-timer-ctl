#include "menu.h"
#include "../../libs/display.h"
#include "../../libs/input.h"
#include "../../libs/hal.h"
#include "../../libs/sleep.h"
#define CHAR_WIDTH 6

// **当前菜单索引**
uint8_t currentMenuIndex = 0;

extern Adafruit_SSD1306 display;

// **菜单项数量**
constexpr uint8_t menuCount = sizeof(menuItems) / sizeof(menuItems[0]);

volatile bool menuNeedsRedraw = false;
volatile bool needToGoSleep = false;

void btnOKHandler();
void btnRightHandler();
void btnLeftHandler();
void btnCancelHander();

void initMenu()
{
  bindButtonHandlers(btnOKHandler, btnCancelHander, btnLeftHandler, btnRightHandler);
  drawMenu();
  setSystemState(SystemState::IDLE);
}

void drawMenu()
{
  clearScreen();

  int menu_width = SCREEN_WIDTH / menuCount;
  int menu_item_height = 3;
  for (int i = 0; i < menuCount; i++)
  {
    display.drawLine(i * menu_width + 1, SCREEN_HEIGHT - 2, i * menu_width + menu_width - 2, SCREEN_HEIGHT - 2, SSD1306_WHITE);
  }
  display.fillRect(currentMenuIndex * menu_width + 1, SCREEN_HEIGHT - menu_item_height, menu_width - 2, SCREEN_HEIGHT - menu_item_height, SSD1306_WHITE);
  const uint8_t *icon = (const uint8_t *)pgm_read_ptr(&menuItems[currentMenuIndex].icon); // 读取图标
  display.drawBitmap(48, 6, icon, 32, 32, SSD1306_WHITE);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  char nameBuffer[20];
  strcpy_P(nameBuffer, (const char *)pgm_read_ptr((const void *)&menuItems[currentMenuIndex].name));
  // **计算文本宽度**
  int16_t textWidth = strlen(nameBuffer) * CHAR_WIDTH;
  int16_t x = (SCREEN_WIDTH - textWidth) / 2; // **居中对齐 X 坐标**
  display.setCursor(x, 42);                   // **设置居中 X 坐标**
  display.print(nameBuffer);
  display.display();
}

void updateMenu()
{
  if (menuNeedsRedraw)
  {
    menuNeedsRedraw = false;
    drawMenu();
  }
  else if (needToGoSleep)
  {
    needToGoSleep = false;
    goSleep();
  }
}

void btnLeftHandler()
{
  setSystemState(SystemState::IDLE);
  currentMenuIndex = (currentMenuIndex + menuCount - 1) % menuCount; // **循环到上一个菜单**
  menuNeedsRedraw = true;
}

void btnRightHandler()
{
  setSystemState(SystemState::IDLE);
  currentMenuIndex = (currentMenuIndex + 1) % menuCount; // **循环到下一个菜单**
  menuNeedsRedraw = true;
}

void btnOKHandler()
{
  MenuFunction action = (MenuFunction)pgm_read_ptr(&menuItems[currentMenuIndex].action);
  action(); // **执行菜单函数**
}

void btnCancelHander()
{
  setSystemState(SystemState::IDLE);
  menuNeedsRedraw = false;
  needToGoSleep = true;
}