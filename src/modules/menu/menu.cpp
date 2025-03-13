#include "menu.h"
#include "../../libs/display.h"
#include "../../libs/input.h"
// **当前菜单索引**
uint8_t currentMenuIndex = 0;

// **菜单项数量**
constexpr uint8_t menuCount = sizeof(menuItems) / sizeof(menuItems[0]);

void selectMenu();
void nextMenu();
void prevMenu();

void initMenu()
{

  drawMenu();
}

void drawMenu()
{
  clearScreen();
}

void nextMenu()
{
  currentMenuIndex = (currentMenuIndex + 1) % menuCount; // **循环到下一个菜单**
  drawMenu();
}

void prevMenu()
{
  currentMenuIndex = (currentMenuIndex + menuCount - 1) % menuCount; // **循环到上一个菜单**
  drawMenu();
}

void selectMenu()
{
  MenuFunction action = (MenuFunction)pgm_read_ptr(&menuItems[currentMenuIndex].action);
  action(); // **执行菜单函数**
}
