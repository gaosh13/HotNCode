#ifndef SPEAKER_H
#define SPEAKER_H

#define SFX_RST 7

#include <ArduinoSTL.h>
#include <Adafruit_Soundboard.h>

struct Speaker {
  Adafruit_Soundboard sfx = Adafruit_Soundboard(&Serial1, NULL, SFX_RST);
  Speaker();
  int operate(std::string cmds);
};

#endif
