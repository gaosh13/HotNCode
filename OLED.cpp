#include "OLED.h"

int OLEDPen::cover = 0;

OLEDPen::OLEDPen() {}

void OLEDPen::begin() {
  super.begin();
}

void OLEDPen::drawTest(char *text, uint16_t color=WHITE) {
  super.setCursor(0, 0);
  super.setTextColor(color);
  super.print(text);
}

void OLEDPen::drawCircles(uint8_t radius, uint16_t color) {
  for (uint8_t x=0; x < super.width()-1+radius; x+=radius*2) {
    for (uint8_t y=0; y < super.height()-1+radius; y+=radius*2) {
      super.drawCircle(x, y, radius, color);
    }
  }
}

void OLEDPen::drawCursor(uint8_t x, uint8_t y, uint8_t radius=5, uint16_t color=WHITE) {
  super.drawCircle(x, y, radius, color);
}

void OLEDPen::drawMenu(MenuCursor* m, int c=cover) {
  if (c == 0) {
    super.fillScreen(BLACK);
  }
  int TITLE = WHITE;
  int CHOSEN = YELLOW;
  int UNCHOSEN = BLUE;
  if (c == 2) {
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
