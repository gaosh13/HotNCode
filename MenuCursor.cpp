#include "MenuCursor.h"
#include "const.h"
#include <Arduino.h>
#include <ArduinoSTL.h>

MenuCursor::MenuCursor(const char* res, MenuCursor* p) : choice(0), name(res) {
  if (p) {
    p->addChild(this);
    parent = p;
  } else {
    parent = this;
  }
}

void MenuCursor::addChild(MenuCursor* cursor) {
  this->child.push_back(cursor);
}

void MenuCursor::last() {
  if (child.size()) {
    --choice;
    if (choice == -1) {
      choice = child.size()-1;
    }
  }
}

void MenuCursor::next() {
  if (child.size()) {
    ++choice;
    if (choice >= child.size()) {
      choice -= child.size();
    }
  }
}

MenuCursor* MenuCursor::back() {
  return this->parent;
}

MenuCursor* MenuCursor::enter() {
  Serial.print("choice ");
  Serial.println(choice);
  if (choice >= 0 && choice < child.size()) {
    return child[choice];
  } else {
    return this;
  }
}

MenuCursor::~MenuCursor() {
  for (int i = 0; i < child.size(); ++i) {
    delete child[i];
  }
}

MenuCursor* generateMenu() {
  MenuCursor* p[16];
  p[0] = new MenuCursor("Main Menu", NULL);
  p[1] = new MenuCursor("Story Mode", p[0]);
  p[2] = new MenuCursor("Versus Mode", p[0]);
  p[3] = new MenuCursor("Settings", p[0]);
  p[4] = new MMMenu("Level 1", p[1]);
  p[5] = new MMMenu("Level 2", p[1]);
  p[6] = new MMMenu("Level 3", p[1]);
  p[7] = new MenuCursor("Volume", p[3]);
  p[8] = new MenuCursor("Language", p[3]);
  p[9] = new MenuCursor("Creators", p[3]);
  p[10] = new MMMenu("Level 4", p[1]);
  p[11] = new MMMenu("Level 5", p[1]);
  p[12] = new MMMenu("Level 6", p[1]);
//  p[13] = new MMMenu("Level 7", p[1]);
//  p[14] = new MMMenu("Level 8", p[1]);
//  p[15] = new MMMenu("Level 9", p[1]);
  return p[0];
}

MMMenu::MMMenu(const char* res, MenuCursor* p) : MenuCursor(res, p) {
  choice = -1;
}

int decodeHome(int a) {
  return a/100 == HOME;
}

int numHome(int a) {
  return a%100;
}

MenuCursor* MMMenu::enter() {
  Serial.println("game");
//  if (speaker) {
//    speaker->play(0);
//  }
  if (scanner && speaker && tft && g) {
    g->setLevel(this->parent->choice);
    Serial.print("try level ");
    Serial.println(g->getLevel());
    std::string s = scanner->scan();
    int res = g->play(s.c_str());
    if (res == SUCCESS) {
      Serial.println("YOU SUCCEED");
      speaker->play(8);
      g->levelUp();
      this->parent->next();
      return this->parent->enter();
    } else if (res == FILL) {
      Serial.println("PLEASE FILL ALL");
      speaker->play(6);
    } else if (decodeHome(res)) {
      Serial.println("SOMEONE CANNOT GO HOME");
      speaker->play(1 + numHome(res));
    } else if (res == PREDATOR) {
      Serial.println("BIG BAD WOLF");
      speaker->play(5);
    } else if (res == EXTRA) {
      Serial.println("CONTAINING EXTRA ROAD");
      speaker->play(7);
    }
  }
  return this->MenuCursor::enter();
}

Speaker* MMMenu::speaker = NULL;
OLEDPen* MMMenu::tft = NULL;
game* MMMenu::g = NULL;
Scanner* MMMenu::scanner = NULL;
