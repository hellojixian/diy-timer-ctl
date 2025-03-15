#include "menu.h"
#include "../../libs/display.h"
#include "../../libs/input.h"
#include "../../libs/hal.h"
#include "../../libs/sleep.h"

// **当前菜单索引**
uint8_t currentMenuIndex = 0;

extern Adafruit_SSD1306 display;

// **菜单项数量**
constexpr uint8_t menuCount = sizeof(menuItems) / sizeof(menuItems[0]);

void menuOKHandler();
void menuRightHandler();
void menuLeftHandler();
void menuCancelHandler();

void initMenu()
{
  bindButtonHandlers(menuOKHandler, menuCancelHandler, menuLeftHandler, menuRightHandler);
  drawMenu();
  setSystemState(SystemState::IDLE);
}

void drawMenuItem()
{
  const uint8_t *icon = (const uint8_t *)pgm_read_ptr(&menuItems[currentMenuIndex].icon); // 读取图标
  display.drawBitmap(44, 2, icon, 40, 40, SSD1306_WHITE);
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  char nameBuffer[20];
  strcpy_P(nameBuffer, (const char *)pgm_read_ptr((const void *)&menuItems[currentMenuIndex].name));
  display.setCursor(alignCenter(nameBuffer, 1), 46); // **设置居中 X 坐标**
  display.print(nameBuffer);
  display.display();
}

void drawMenu()
{
  clearScreen();
  drawBottomMenu(currentMenuIndex, menuCount);
  drawMenuItem();
}

void menuLeftHandler()
{
  setSystemState(SystemState::IDLE);
  currentMenuIndex = (currentMenuIndex + menuCount - 1) % menuCount; // **循环到上一个菜单**
  drawMenu();
}

void menuRightHandler()
{
  setSystemState(SystemState::IDLE);
  currentMenuIndex = (currentMenuIndex + 1) % menuCount; // **循环到下一个菜单**
  drawMenu();
}

void menuOKHandler()
{
  MenuFunction action = (MenuFunction)pgm_read_ptr(&menuItems[currentMenuIndex].action);
  action();
}

void menuCancelHandler()
{
  setSystemState(SystemState::IDLE);
  goSleep();
}