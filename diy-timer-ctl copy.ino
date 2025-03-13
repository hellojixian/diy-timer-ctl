#include <Wire.h>             // I2C 通信库
#include <Adafruit_GFX.h>     // Adafruit 图形库
#include <Adafruit_SSD1306.h> // SSD1306 OLED 屏幕驱动库
#include <avr/interrupt.h>

#define SCREEN_WIDTH 128 // OLED 屏幕宽度
#define SCREEN_HEIGHT 64 // OLED 屏幕高度

#define BUZZER_PIN D5 // 蜂鸣器连接到 PD5

#define BTN_CANCEL PD3 // 取消按钮
#define BTN_OK PD2     // 确认按钮
#define BTN_UP PD6     // 向上按钮
#define BTN_DOWN PD7   // 向下按钮

// 创建 OLED 屏幕对象 (I2C 地址通常是 0x3C)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

volatile uint8_t button_pressed = 0;            // 记录哪个按钮被按下
volatile unsigned long last_interrupt_time = 0; // 记录上次按键触发的时间（消抖）

void setup()
{
  Serial.begin(115200); // 初始化串口
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Hello, World!");
  display.display();

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(BTN_CANCEL, INPUT_PULLUP);
  pinMode(BTN_OK, INPUT_PULLUP);
  pinMode(BTN_UP, INPUT_PULLUP);
  pinMode(BTN_DOWN, INPUT_PULLUP);

  cli(); // 关闭全局中断

  PCICR |= (1 << PCIE2);                                                       // 使能 PCINT2 组中断 (PD0-PD7)
  PCMSK2 |= (1 << PCINT19) | (1 << PCINT18) | (1 << PCINT22) | (1 << PCINT23); // 使能 PD2, PD3, PD6, PD7 的中断

  sei(); // 使能全局中断
}

ISR(PCINT2_vect)
{
  unsigned long interrupt_time = millis();
  if (interrupt_time - last_interrupt_time < 200)
    return; // 200ms 消抖
  last_interrupt_time = interrupt_time;

  if (digitalRead(BTN_CANCEL) == LOW)
  {
    button_pressed = BTN_CANCEL;
  }
  else if (digitalRead(BTN_OK) == LOW)
  {
    button_pressed = BTN_OK;
  }
  else if (digitalRead(BTN_UP) == LOW)
  {
    button_pressed = BTN_UP;
  }
  else if (digitalRead(BTN_DOWN) == LOW)
  {
    button_pressed = BTN_DOWN;
  }
}

void loop()
{
  if (button_pressed != 0)
  {
    switch (button_pressed)
    {
    case BTN_CANCEL:
      playTone(500, 100);
      Serial.println("BTN_CANCEL pressed");
      break;
    case BTN_OK:
      playTone(1000, 100);
      Serial.println("BTN_OK pressed");
      break;
    case BTN_UP:
      playTone(1500, 100);
      Serial.println("BTN_UP pressed");
      break;
    case BTN_DOWN:
      playTone(2000, 100);
      Serial.println("BTN_DOWN pressed");
      break;
    }
    button_pressed = 0; // 清空标志位
  }
}

// 播放指定频率和时长的提示音
void playTone(int frequency, int duration)
{
  int period = 1000000 / frequency;
  int half_period = period / 2;
  long cycles = (long)duration * 1000 / period;

  for (long i = 0; i < cycles; i++)
  {
    digitalWrite(BUZZER_PIN, HIGH);
    delayMicroseconds(half_period);
    digitalWrite(BUZZER_PIN, LOW);
    delayMicroseconds(half_period);
  }
}
