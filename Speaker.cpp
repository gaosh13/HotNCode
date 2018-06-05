#include "Speaker.h"

Speaker::Speaker() {
  Serial1.begin(9600);
  if (!sfx.reset()) {}
}

int Speaker::play(int a) {
  if (! sfx.playTrack(a) ) {
    return -1;
  }
  return 0;
}

int Speaker::operate(std::string cmds) {
  switch (cmds[0]) {
    case 'r': {
      if (!sfx.reset()) {
        return -1;
      }
      break; 
    }
    
    case '#': {
      uint8_t n = 0;
      for (int i = 1; i < cmds.size(); ++i) {
        if (isdigit(cmds[i])) {
          n = n*10 + cmds[i] - '0';
        } else {
          break;
        }
      }
      if (! sfx.playTrack(n) ) {
        return -1;
      }
      break;
    }

   case '+': {
      uint16_t v;
      if (! (v = sfx.volUp()) ) {
        return -1;
      }
      break;
   }

   case '-': {
      uint16_t v;
      if (! (v=sfx.volDown()) ) {
        return -1;
      }
      break;
   }
   
   case '=': {
      if (! sfx.pause() ) {
        return -1;
      }
      break;
   }
   
   case '>': {
      if (! sfx.unpause() ) {
        return -1;
      }
      break;
   }
   
   case 'q': {
      if (! sfx.stop() ) {
        return -1;
      }
      break;
   }

   default: {
    return -1;
   }
  }
  return 0;
}
