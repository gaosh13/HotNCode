#ifndef LIMIT_H
#define LIMIT_H

struct limit {
  int home;
  int edge;
  int forbid;
  int state;
  limit(int a) {
    home = a + 4;
    edge = a == 2 ? 1: 0;
    forbid = (a == 0 || a == 3) ? 3-a: -1;
    state = 0;
  }
  limit(int h, int e, int f) : home(h), edge(e), forbid(f), state(0) {
  }
};

#endif

