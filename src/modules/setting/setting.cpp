#include <Arduino.h>
#include "setting.h"
#include "../../libs/display.h"

bool isMuted = false;
// int sleepTimeout = 30;

void settingMenuHandler()
{
  toggleMute();
}

void toggleMute()
{
  isMuted = !isMuted;
  drawText(10, 20, isMuted ? "Mute: ON" : "Mute: OFF");
}

void changeSleepTimeout()
{
  // sleepTimeout = (sleepTimeout == 10) ? 30 : (sleepTimeout == 30) ? 60
  //                                        : (sleepTimeout == 60)   ? 0
  //                                                                 : 10;
  // drawText(10, 40, sleepTimeout == 0 ? "Sleep: Off" : String(sleepTimeout).c_str());
}
