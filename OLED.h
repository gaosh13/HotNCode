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

struct MenuCursor;

struct OLEDPen{
  Adafruit_SSD1351 super = Adafruit_SSD1351(cs, dc, mosi, sclk, rst);
  OLEDPen();
  static int cover;
  void begin();
  void drawTest(char *text, uint16_t color=WHITE);
  void drawCircles(uint8_t radius, uint16_t color);
  void drawCursor(uint8_t x, uint8_t y, uint8_t radius=5, uint16_t color=WHITE);
  void drawMenu(MenuCursor* m, int c=cover);
};

#endif
