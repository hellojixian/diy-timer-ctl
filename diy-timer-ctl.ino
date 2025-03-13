#include "src/hal.h"
#include "src/menu.h"
#include "src/input.h"
#include "src/sleep.h"
#include "src/modules/timer/menu_timer.h"

void setup()
{
  initHardware(); // 初始化硬件
  menuInit();     // 初始化菜单
}

void loop()
{
  if (isCountingDown())
  {
    updateCountdown();
  }
  else
  {
    handleInput();
    checkSleep();
  }
}
