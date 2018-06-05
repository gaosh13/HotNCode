#include "OLED.h"
#include "MenuCursor.h"
#include "ButtonHandle.h"
#include "PCBscanner.h"
#include "Speaker.h"
#include "game.h"

OLEDPen* tft;
MenuCursor* menu;
ButtonHandle* button;
Scanner* scanner;
Speaker* speaker;
game* g;
int cover;

// Option 1: use any pins but a little slower
//Adafruit_SSD1351 super = Adafruit_SSD1351(cs, dc, mosi, sclk, rst);
// Option 2: must use the hardware SPI pins 
// (for UNO thats sclk = 13 and sid = 11) and pin 10 must be 
// an output. This is much faster - also required if you want
// to use the microSD card (see the image drawing example)
//Adafruit_SSD1351 tft = Adafruit_SSD1351(cs, dc, rst);

void setup(void) {
  Serial.begin(9600);
  Serial.println("begin");
  tft = new OLEDPen();
  speaker = new Speaker();
  scanner = new PCBscanner();
  tft->begin();
  button = new ClickButton();
  Serial.println("port");
  menu = generateMenu();
  g = new game();
  MMMenu::speaker = speaker;
  MMMenu::tft = tft;
  MMMenu::g = g;
  MMMenu:: scanner = scanner;
  OLEDPen::cover = 0;
  Serial.println("menu");
}

void loop() {
//  Serial.println("begin drawing");
  tft->drawMenu(menu);
//  Serial.println("end drawing");
  OLEDPen::cover = 1;
  buttonBlock();
}

void buttonBlock() {
  for (;;) {
    for (;!button->ready(););
    
    int b = button->pressed();
    bool flag = true;
    if (b == 0) {
      tft->drawMenu(menu, 2);
      menu = menu->back();
      cover = true;
    } else if (b == 1) {
      menu->last();
    } else if (b == 2) {
      menu->next();
    } else if (b == 3) {
      tft->drawMenu(menu, 2);
      menu = menu->enter();
    } else {
      flag = false;
    }
    if (flag) {
      break;
    }
  }
}

