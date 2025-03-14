#ifndef INPUT_H
#define INPUT_H

typedef void (*ButtonCallback)(); // 定义按钮回调函数类型
void bindButtonHandlers(ButtonCallback okHandler, ButtonCallback cancelHandler, ButtonCallback leftHandler, ButtonCallback rightHandler);

void initInput();
void handleInput();
#endif
