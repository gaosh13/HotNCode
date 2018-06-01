#ifndef MENUCURSOR_H
#define MENUCURSOR_H

#include <ArduinoSTL.h>

struct MenuCursor {
  int choice;
  std::string name;
  std::vector<MenuCursor*> child;
  MenuCursor* parent;
  MenuCursor(const char* res, MenuCursor* p) : choice(0), name(res) {
    if (p) {
      p->addChild(this);
      parent = p;
    } else {
      parent = this;
    }
  }
  void addChild(MenuCursor* cursor) {
  	this->child.push_back(cursor);
  }
  void last() {
    if (child.size()) {
      --choice;
      if (choice == -1) {
        choice = child.size()-1;
      }
    }
  }
  void next() {
    if (child.size()) {
      ++choice;
      if (choice >= child.size()) {
        choice -= child.size();
      }
    }
  }
  MenuCursor* back() {
    return this->parent;
  }
  MenuCursor* enter() {
    if (choice >= 0 && choice < child.size()) {
      return child[choice];
    } else {
      return this;
    }
  }
  ~MenuCursor() {
    for (int i = 0; i < child.size(); ++i) {
      delete child[i];
    }
  }
};

MenuCursor* generateMenu() {
  MenuCursor* p[10];
  p[0] = new MenuCursor("Main Menu", NULL);
  p[1] = new MenuCursor("Story Mode", p[0]);
  p[2] = new MenuCursor("Versus Mode", p[0]);
  p[3] = new MenuCursor("Settings", p[0]);
  p[4] = new MenuCursor("Level 1", p[1]);
  p[5] = new MenuCursor("Level 2", p[1]);
  p[6] = new MenuCursor("Level 3", p[1]);
  p[7] = new MenuCursor("Volumn", p[3]);
  p[8] = new MenuCursor("Language", p[3]);
  p[9] = new MenuCursor("Creators", p[3]);
  return p[0];
}

#endif
