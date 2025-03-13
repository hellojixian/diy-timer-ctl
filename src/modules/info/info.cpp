#include "info.h"
#include "../../libs/display.h"

void infoMenuHandler()
{
  clearScreen();
  drawText(10, 20, "Version: 1.0");
  drawText(10, 40, "Author: YourName");
}
