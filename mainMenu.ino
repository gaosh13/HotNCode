#include "OLED.h"
#include "MenuCursor.h"
#include "ButtonHandle.h"
#include "PCBscanner.h"

OLEDPen tft = OLEDPen();
MenuCursor* menu;
ButtonHandle* button;
PCBscanner scanner = PCBscanner();
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
  tft.begin();
  menu = generateMenu();
  button = new SerialButton();
  cover = 0;
}

void loop() {
  tft.drawMenu(menu, cover);
  cover = 1;
  for (;;) {
    if (button->ready()) {
      int b = button->pressed();
      bool flag = true;
      if (b == 0) {
        tft.drawMenu(menu, 2);
        menu = menu->back();
        cover = true;
      } else if (b == 1) {
        menu->last();
      } else if (b == 2) {
        menu->next();
      } else if (b == 3) {
        tft.drawMenu(menu, 2);
        menu = menu->enter();
      } else {
        flag = false;
      }
      if (flag) {
        break;
      }
    }
  }
}
