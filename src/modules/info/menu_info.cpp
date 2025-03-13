#include "menu_info.h"
#include "../../menu.h"
#include "../../display.h"

void infoMenuHandler()
{
  clearScreen();
  drawText(10, 20, "Version: 1.0");
  drawText(10, 40, "Author: YourName");
}
