#include "menu.h"
#include "modules/timer/menu_timer.h"
#include "modules/setting/menu_setting.h"
#include "modules/info/menu_info.h"

U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// 菜单项
LCDMenuLib2_menu ROOT(NULL, 0, 0, NULL, "Main Menu", NULL);
LCDMenuLib2_menu TIMER(&ROOT, 1, 0, NULL, "Timer", timerMenuHandler);
LCDMenuLib2_menu SETTING(&ROOT, 2, 0, NULL, "Setting", settingMenuHandler);
LCDMenuLib2_menu INFO(&ROOT, 3, 0, NULL, "Info", infoMenuHandler);

LCDMenuLib2 menu(&ROOT, 128, 64, 10, 10);

// **菜单初始化**
void menuInit() {
    menu.init();
    drawMenu();
}

// **绘制菜单**
void drawMenu() {
    u8g2.clearBuffer();
    int startX = 10;
    int itemWidth = 50;
    int selectedIndex = menu.getCursorPos();

    for (int i = 0; i < menu.getChilds(); i++) {
        int x = startX + (i - selectedIndex) * itemWidth;
        if (i == selectedIndex) {
            u8g2.drawBox(x - 2, 20, itemWidth, 15);  // 选中项背景
            u8g2.setDrawColor(0);
        }
        u8g2.setCursor(x, 30);
        u8g2.print(menu.getChild(i)->getName());
        u8g2.setDrawColor(1);
    }

    u8g2.sendBuffer();
}

// **菜单操作**
void menuSelect() {
    menu.getSelected()->select();
}

void cancelAction() {
    menu.setCursorPos(0);
    drawMenu();
}

void menuNext() {
    menu.next();
    drawMenu();
}

void menuPrev() {
    menu.prev();
    drawMenu();
}
