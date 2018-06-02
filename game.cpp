#include <ArduinoSTL.h>

#include "game.h"
#include "const.h"
#include "edge.h"
#include "limit.h"

game::game()
{
  level = 0;
}

void game::dfs(int x, limit *l) {
  l->state |= checkTile(x, l);
  for (Edge *e = point[x]; e; e = e->next) {
    if (e->used == 0) {
      if (e->label == l->edge) {
        e->used = 1;
        dfs(e->des, l);
      }
    }
  }
}

int game::checkTile(int i, int j, int d, limit *l) {
  if (d != -1 && place[i][j][1] != d)
    return 0;
  if (place[i][j][0] == l->home)
    return 1;
  if (place[i][j][0] == l->forbid)
    return 2;
  return 0;
}

game::v_T game::tiles(int x) {
  int i = 0, j = 0;
  v_T v;
  if (x >= HP) {
    j = (x-HP)/H;
    i = (x-HP)%H;
    if (j > 0) {
      v.push_back(Tile(i, j-1, 1));
    }
    if (j < W) {
      v.push_back(Tile(i, j, 3));
    }
  } else {
    i = x/W;
    j = x%W;
    if (i > 0) {
      v.push_back(Tile(i-1, j, 2));
    }
    if (i < H) {
      v.push_back(Tile(i, j, 0));
    }
  }
  return v;
}

int game::checkTile(int x, limit *l) {
  int a = 0;
  for (Tile &t : tiles(x)) {
    a |= checkTile(t.i, t.j, t.d, l);
//    a |= checkTile(t.i, t.j, -1, l);
  }
  return a;
}

int game::findPoint(int i, int j, int d) {
  switch (d) {
  case 0:
    return i*W+j;
  case 1:
    return HP+(j+1)*H+i;
  case 2:
    return (i+1)*W+j;
  default:
    return HP+j*H+i;
  }
}

int game::findPoint(int i, int j) {
  return findPoint(i, j, place[i][j][1]);
}

int game::checkFill() {
  for (int i = 0; i < H; ++i)
    for (int j = 0; j < H; ++j)
      if (place[i][j][0] == -1)
        return false;
  return true;
}

int isanimal(int tile) {
  return tile < 4;
}

int isroad(int tile) {
  return tile >= 8;
}

int game::checkHome() {
  for (int i = 0; i < H; ++i)
    for (int j = 0; j < W; ++j) {
      if (isanimal(place[i][j][0])) {
        int x = findPoint(i, j);
        if (!point[x])
          return HOME;
        if (point[x]->used)
          continue;
        limit l = limit(place[i][j][0]);
        dfs(findPoint(i, j), &l);
        if ((l.state & 1) == 0)
          return HOME;
        if ((l.state & 2) != 0)
          return PREDATOR;
      }
    }
  return SUCCESS;
}

int game::sameTile(int x, int y) {
  v_T tx = tiles(x);
  v_T ty = tiles(y);
  for (Tile &ix : tx)
    for (Tile &iy : ty)
      if (ix.i == iy.i && ix.j == iy.j)
        return true;
  return false;
}

int game::animalTile(int x) {
  for (Tile &t : tiles(x)) {
    if (!isroad(place[t.i][t.j][0]) && place[t.i][t.j][1] == t.d)
      return true;
  }
  return false;
}

int game::checkExtra() {
  for (Edge *e = edgePool; e < ep; e++) {
    if (e->used == 0)
      return false;
  }
  for (int i = 0; i < TP; ++i) {
    if (!animalTile(i)) {
      if (point[i]) {
        Edge *e = point[i];
        int o = e->des;
        int same = false;
        for (e = e->next; e; e = e->next) {
          same |= !sameTile(o, e->des);
        }
        if (!same)
          return false;
      }
    }
  }
  return true;
}

int game::resultCode() {
  if (!checkFill())
    return FILL;
//  cout << "end fill" << endl;
  int x = checkHome();
  if (x != SUCCESS)
    return x;
//  cout << "end home" << endl;
  if (!checkExtra())
    return EXTRA;
//  cout << "end extra" << endl;
  return SUCCESS;
}

void game::bidirectional(int a, int b, int label) {
  *ep = Edge(point[a], b, label);
  point[a] = ep++;
  *ep = Edge(point[b], a, label);
  point[b] = ep++;
}

void game::buildEdge(int tile[2], int a, int b, int c, int d) {
  switch (tile[0] * 4 + tile[1]) {
    case 32: // 8 0
      bidirectional(a, c, 0);
      break;
    case 33: // 8 1
      bidirectional(b, d, 0);
      break;

    case 36: // 9 0
      bidirectional(a, c, 1);
      break;
    case 37: // 9 1
      bidirectional(b, d, 1);
      break;

    case 40: // 10 0
      bidirectional(a, d, 0);
      break;
    case 41: // 10 1
      bidirectional(a, b, 0);
      break;
    case 42: // 10 2
      bidirectional(b, c, 0);
      break;
    case 43: // 10 3
      bidirectional(c, d, 0);
      break;

    case 44: // 11 0
      bidirectional(a, d, 1);
      break;
    case 45: // 11 1
      bidirectional(a, b, 1);
      break;
    case 46: // 11 2
      bidirectional(b, c, 1);
      break;
    case 47: // 11 3
      bidirectional(c, d, 1);
      break;

    case 48: // 12 0
      bidirectional(a, b, 0);
      bidirectional(b, c, 0);
      bidirectional(c, d, 0);
      break;

    case 52: // 13 0
      bidirectional(b, d, 0);
      bidirectional(a, c, 1);
      break;
    case 53: // 13 1
      bidirectional(a, c, 0);
      bidirectional(b, d, 1);
      break;

    case 56: // 14 0
      bidirectional(a, d, 0);
      bidirectional(b, c, 0);
      break;
    case 57: // 14 1
      bidirectional(a, b, 0);
      bidirectional(c, d, 0);
      break;

    case 60: // 15 0
      bidirectional(a, d, 0);
      bidirectional(b, c, 1);
      break;
    case 61: // 15 1
      bidirectional(a, b, 0);
      bidirectional(c, d, 1);
      break;
    case 62: // 15 2
      bidirectional(b, c, 0);
      bidirectional(a, d, 1);
      break;
    case 63: // 15 3
      bidirectional(c, d, 0);
      bidirectional(a, b, 1);
      break;
  };
}

void game::buildEdges() {
  ep = edgePool;
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      buildEdge(place[i][j], findPoint(i, j, 0), findPoint(i, j, 1), findPoint(i, j, 2), findPoint(i, j, 3));
    }
  }
}

int game::checkResult() {
  memset(point, 0, sizeof point);
  buildEdges();
//  cout << "end edges" << endl;
  return resultCode();
}

void swapTurn(char &a, char &b, char &c, char &d) {
  int t = a;
  a = b;
  b = c;
  c = d;
  d = t;
}

int patternToId(char *s) {
  int num[4];
  for (int i = 0; i < 4; ++i) {
    num[i] = 0;
    for (int j = 0; j < Nhole; ++j) {
      num[i] = num[i] * 2 + (s[j]-'0');
    }
    swapTurn(s[0], s[2], s[8], s[6]);
    swapTurn(s[1], s[5], s[7], s[3]);
  }
  for (int i = 0; i < Nblock; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (num[j] == BlockPattern[i]) {
        return i*4+j;
      }
    }
  }
  return -4;
}

void game::getPattern(char *a, int r, int c, const char *pattern) {
  for (int i = 0; i < SH; ++i)
    for (int j = 0; j < SH; ++j)
      a[i*SH+j] = pattern[(i+r*SH)*(W*SH)+(j+c*SH)];
}

int game::play(const char *pattern) {
  for (int i = 0; i < H; ++i) {
    for (int j = 0; j < W; ++j) {
      if (Levels[level][i][j][0] != -1)
        memcpy(place[i][j], Levels[level][i][j], 2*sizeof(int));
      else {
        char a[Nhole+1];
        getPattern(a, i, j, pattern);
        int x = patternToId(a);
        place[i][j][0] = x/4;
        place[i][j][1] = x%4;
      }
    }
  }
//  cout << "end decode" << endl;
  return checkResult();
}

void game::levelUp() {
  level++;
}

int game::getLevel() {
  return level;
}

void game::setLevel(int a) {
  level=a;
}

