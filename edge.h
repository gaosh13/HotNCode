#ifndef EDGE_H
#define EDGE_H

#include "const.h"

struct Edge {
  Edge() : next(nullptr), des(-1), label(-1), used(-1) {}
  Edge(Edge *a, int b, int label) {
    this->next = a;
    this->des = b;
    this->label = label;
    this->used = 0;
  }

  Edge* next;
  int des;
  int label;
  int used;
};

#endif

