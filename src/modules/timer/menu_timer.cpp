#include "menu_timer.h"
#include "../../display.h"
#include "../../menu.h"
#include "../../hal.h"

int countdownTime = 60;
unsigned long countdownStart = 0;
bool counting = false;

void startCountdown()
{
  counting = true;
  countdownStart = millis();
}

void updateCountdown()
{
  if (!counting)
    return;

  unsigned long elapsed = (millis() - countdownStart) / 1000;
  int remaining = countdownTime - elapsed;
  if (remaining <= 0)
  {
    counting = false;
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
    drawMenu();
  }
  else
  {
    clearScreen();
    drawText(40, 30, String(remaining).c_str());
  }
}

bool isCountingDown()
{
  return counting;
}

void cancelCountdown()
{
  counting = false;
  drawMenu();
}

void timerMenuHandler()
{
  startCountdown();
}
