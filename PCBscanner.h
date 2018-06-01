#ifndef PCBSCANNER_H
#define PCBSCANNER_H

#include <ArduinoSTL.h>

class PCBscanner {
  static const int PINS = 15;
  int inputPin(int i) {
    return i*2 + 22;
  }
  int outputPin(int i) {
    return i*2 + 23;
  }
public:
  PCBscanner() {
    for (int i = 0; i < PINS; ++i) {
      pinMode(inputPin(i), INPUT);
      pinMode(outputPin(i), OUTPUT);
    }
  }
  std::string scan() {
    std::string pattern = "";
    for (int i = 0; i < PINS; ++i) {
      for (int j = 0; j < PINS; ++j) {
        digitalWrite(j, i == j ? LOW : HIGH);
      }
      delay(10);
      for (int j = 0; j < PINS; ++j) {
        int a = digitalRead(j);
        char c = a == HIGH ? '0' : '1';
        pattern += c;
      }
    }
    return pattern;
  }
};

#endif
