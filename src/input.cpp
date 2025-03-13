#include "input.h"
#include "menu.h"

void handleInput()
{
  if (digitalRead(BTN_CANCEL) == LOW)
  {
    cancelAction();
    delay(200);
  }

  if (digitalRead(BTN_OK) == LOW)
  {
    menuSelect();
    delay(200);
  }

  if (digitalRead(BTN_UP) == LOW)
  {
    menuNext();
    delay(200);
  }

  if (digitalRead(BTN_DOWN) == LOW)
  {
    menuPrev();
    delay(200);
  }
}
