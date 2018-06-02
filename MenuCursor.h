#ifndef MENUCURSOR_H
#define MENUCURSOR_H

#include "Speaker.h"
#include "OLED.h"
#include "game.h"
#include "PCBscanner.h"
#include <ArduinoSTL.h>

struct OLEDPen;
struct Speaker;
class game;
struct Scanner;

struct MenuCursor {
  int choice;
  std::string name;
  std::vector<MenuCursor*> child;
  MenuCursor* parent;
  MenuCursor(const char* res, MenuCursor* p);
  void addChild(MenuCursor* cursor);
  void last();
  void next();
  MenuCursor* back();
  virtual MenuCursor* enter();
  ~MenuCursor();
};

struct MMMenu : MenuCursor {
  static Speaker* speaker;
  static OLEDPen* tft;
  static game* g;
  static Scanner* scanner;
  MMMenu(const char* res, MenuCursor* p);
  MenuCursor* enter();
};

MenuCursor* generateMenu();

#endif
