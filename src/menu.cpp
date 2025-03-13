#include "menu.h"
#include "modules/timer/menu_timer.h"
#include "modules/setting/menu_setting.h"
#include "modules/info/menu_info.h"


#include <U8g2lib.h>
#include <LCDMenuLib2.h>

// 外部声明 OLED 屏幕对象
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2;
extern LCDMenuLib2 menu;

// **定义菜单 ID**
#define LCDML_0      255 // 根菜单 ID
#define LCDML_1      1   // Timer
#define LCDML_2      2   // Setting
#define LCDML_3      3   // Info

// **LCDMenuLib2 菜单项**
LCDMenuLib2_menu LCDML_0_menu(LCDML_0, 0, 0, NULL, NULL);
LCDMenuLib2_menu LCDML_1_menu(LCDML_1, 0, 0, timerMenuHandler, NULL);
LCDMenuLib2_menu LCDML_2_menu(LCDML_2, 0, 0, settingMenuHandler, NULL);
LCDMenuLib2_menu LCDML_3_menu(LCDML_3, 0, 0, infoMenuHandler, NULL);

// **LCDMenuLib2 结构**
LCDMenuLib2 menu(LCDML_0_menu, 3, 1, NULL, NULL, NULL);

// **初始化菜单**
void menuInit() {
    menu.init(LCDML_0);
    drawMenu();
}

// **绘制菜单**
void drawMenu() {
    u8g2.clearBuffer();
    int startX = 10;
    int itemWidth = 50;
    int selectedIndex = menu.MENU_getCursorPos();  // **修正 API**

    for (int i = 0; i < menu.MENU_getChilds(); i++) {  // **修正 API**
        int x = startX + (i - selectedIndex) * itemWidth;
        if (i == selectedIndex) {
            u8g2.drawBox(x - 2, 20, itemWidth, 15);  // 选中项背景
            u8g2.setDrawColor(0);
        }
        u8g2.setCursor(x, 30);
        u8g2.print("Item ");
        u8g2.print(i + 1);
        u8g2.setDrawColor(1);
    }

    u8g2.sendBuffer();
}

// **菜单操作**
void menuSelect() {
    menu.BT_enter();  // **修正 API**
}

void cancelAction() {
    menu.BT_quit();  // **修正 API**
    drawMenu();
}

void menuNext() {
    menu.BT_right();  // **修正 API**
    drawMenu();
}

void menuPrev() {
    menu.BT_left();  // **修正 API**
    drawMenu();
}
