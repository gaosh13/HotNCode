#ifndef OLED_H
#define OLED_H

#define sclk 2
#define mosi 3
#define dc   4
#define cs   5
#define rst  6

// Color definitions
#define BLACK           0x0000
#define BLUE            0x001F
#define RED             0xF800
#define GREEN           0x07E0
#define CYAN            0x07FF
#define MAGENTA         0xF81F
#define YELLOW          0xFFE0  
#define WHITE           0xFFFF

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1351.h>
#include <SPI.h>
//#include <ArduinoSTL.h>
#include "MenuCursor.h"

struct OLEDPen{
  Adafruit_SSD1351 super = Adafruit_SSD1351(cs, dc, mosi, sclk, rst);
  OLEDPen() {
  }
  void begin() {
    super.begin();
  }
  void drawTest(char *text, uint16_t color=WHITE) {
    super.setCursor(0, 0);
    super.setTextColor(color);
    super.print(text);
  }
  void drawCircles(uint8_t radius, uint16_t color) {
    for (uint8_t x=0; x < super.width()-1+radius; x+=radius*2) {
      for (uint8_t y=0; y < super.height()-1+radius; y+=radius*2) {
        super.drawCircle(x, y, radius, color);
      }
    }
  }
  void drawCursor(uint8_t x, uint8_t y, uint8_t radius=5, uint16_t color=WHITE) {
    super.drawCircle(x, y, radius, color);
  }
  
  void drawMenu(MenuCursor* m, int cover=0) {
    if (cover == 0) {
      super.fillScreen(BLACK);
    }
    int TITLE = WHITE;
    int CHOSEN = YELLOW;
    int UNCHOSEN = BLUE;
    if (cover == 2) {
      TITLE = CHOSEN = UNCHOSEN = BLACK;
    }
    
    super.setCursor(0, 0);
    super.setTextColor(TITLE);
    super.setTextSize(0);
    super.print(m->name.c_str());

    super.setTextSize(1);
    for (int i = 0; i < m->child.size(); ++i) {
      int x = 10, y = i * 20 + 20;
      if (m->choice == i) {
        super.setTextColor(CHOSEN);
//        this->drawCursor(x + 5, y + 2);
//        x += 15;
      } else {
        super.setTextColor(UNCHOSEN);
      }
      super.setCursor(x, y);
      super.print(m->child[i]->name.c_str());
    }
  }
};

#endif
