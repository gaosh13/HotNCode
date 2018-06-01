#ifndef BUTTONHANDLE_H
#define BUTTONHANDLE_H
struct ButtonHandle {
  ButtonHandle() {};
  virtual int ready();
  virtual int pressed();
  virtual void clear();
};

struct SerialButton : ButtonHandle {
  SerialButton() : ButtonHandle(), a(0) {}
  char a;
  int ready() {
    return Serial.available();
  }
  void recordSerial() {
    if (Serial.available()) {
      a = Serial.read();
    } else {
      a = 0;
    }
  }
  int pressed() {
    recordSerial();
    if (a == 'b') {
      return 0;
    } else if (a == 'u') {
      return 1;
    } else if (a == 'd') {
      return 2;
    } else if (a == 'g') {
      return 3;
    } else{
      return -1;
    }
  }
  void clear() {
    a = 0;
  }
};

struct ClickButton : ButtonHandle {
  static const int BUTTONS = 4;
  static const int INPUTPIN[BUTTONS] = {8, 9, 10, 11};
  int a[BUTTONS];
  int ret;

  ClickButton() : ButtonHandle() {
    for (int i = 0; i < BUTTONS; ++i) {
      a[i] = HIGH:
      pinMode(INPUTPIN[i], INPUT_PULLUP);
    }
    ret = -1;
  }
  int ready() {
    for (int i = 0; i < BUTTONS; ++i) {
      int b = digitalRead(INPUTPIN[i]);
      if (b != a[i]) {
        a[i] = b;
        if (b == LOW) {
          ret = i;
          return true;
        }
      }
    }
    ret = -1;
    return false;
  }
  int pressed() {
    return ret;
  }
  void clear() {
    ret = -1;
    for (int i = 0; i < BUTTONS; ++i) {
      a[i] = HIGH;
    }
  }
};
#endif
