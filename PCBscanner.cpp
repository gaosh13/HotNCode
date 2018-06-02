#include "PCBscanner.h"
#include "game.h"
#include <Arduino.h>
#include <ArduinoSTL.h>

Scanner::Scanner() {
}

PCBscanner::PCBscanner() : Scanner() {
	for (int i = 0; i < PINS; ++i) {
		pinMode(inputPin(i), INPUT);
		pinMode(outputPin(i), OUTPUT);
	}
}

std::string PCBscanner::scan() {
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

int getint() {
	int num = 0;
	char c = ' ';
	for (;;) {
		if (Serial.available()) {
			c = Serial.read();
			if (isDigit(c)) break;
		}
	}
	for (;;) {
		num = num * 10 + c - '0';
		for (;;) {
			if (Serial.available()) {
				c = Serial.read();
				break;
			}
		}
		if (!isDigit(c)) break;
	}
	return num;
}

void toCharArray(char *tmp, int a) {
  for (int i = 0; i < Nhole; ++i) {
    tmp[Nhole-1-i] = '0' + a%2;
    a /= 2;
  }
}

std::string genpattern(int num[Ntile], int dir[Ntile]) {
  std::string s;
  char tmp[Ntile][Nhole+1];
  memset(tmp, 0, sizeof(tmp));
  for (int i = 0; i < Ntile; ++i) {
    if (num[i] >= 0 && num[i] < Nblock && dir[i] >= 0 && dir[i] < 4) {
      toCharArray(tmp[i], BlockPattern[num[i]]);
      for (int j = 0; j < dir[i]; ++j) {
        swapTurn(tmp[i][0], tmp[i][6], tmp[i][8], tmp[i][2]);
        swapTurn(tmp[i][1], tmp[i][3], tmp[i][7], tmp[i][5]);
      }
    }
  }
//  cout << "end block" << endl;
  for (int i = 0; i < H*SH; ++i) {
    for (int j = 0; j < W*SH; ++j) {
      if (0 < i/SH && i/SH < H-1 && 0 < j/SH && j/SH < W-1) {
        s += tmp[(i/SH-1)*(W-2)+(j/SH-1)][i%SH*SH+j%SH];
      } else
        s += '0';
    }
  }
  return s;
}

Serialscanner::Serialscanner() : Scanner() {
}

std::string Serialscanner::scan() {
	int num[Ntile], dir[Ntile];
	for (int i = 0; i < Ntile; ++i) {
		num[i] = getint();
		dir[i] = getint();
	}
	return genpattern(num, dir);
}
