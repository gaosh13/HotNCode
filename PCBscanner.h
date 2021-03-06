#ifndef PCBSCANNER_H
#define PCBSCANNER_H

#include <ArduinoSTL.h>

class Scanner {
public:
  Scanner();
  virtual std::string scan() = 0;
};

class PCBscanner : public Scanner{
  static const int PINS = 12;
  int inputPin(int i) {
    return i*2 + 25;
  }
  int outputPin(int i) {
    return i*2 + 24;
  }
public:
  PCBscanner();
  std::string scan();
};

class Serialscanner : public Scanner{
public:
  Serialscanner();
  std::string scan();
};

#endif
