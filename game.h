#ifndef GAME_H
#define GAME_H

#include "limit.h"
#include "edge.h"
#include <ArduinoSTL.h>

int isanimal(int tile);
int isroad(int tile);
void swapTurn(char &a, char &b, char &c, char &d);
int patternToId(char *s);

class game
{
public:
  game();
  int play(const char *pattern);
  int getLevel();
  void levelUp();
  void setLevel(int a);
private:
  struct Tile{
    Tile() : i(-1), j(-1), d(-1) {}
    int i, j, d;
    Tile(int i, int j, int d) : i(i), j(j), d(d) {}
  };
  typedef std::vector<game::Tile> v_T;
  void bidirectional(int a, int b, int label);
  void buildEdge(int tile[2], int a, int b, int c, int d);
  void dfs(int x, limit *l);
  int findPoint(int i, int j, int d);
  int findPoint(int i, int j);
  int checkTile(int i, int j, int d, limit *l);
  v_T tiles(int x);
  int checkTile(int x, limit *l);
  int sameTile(int x, int y);
  int animalTile(int x);
  int checkFill();
  int checkHome();
  int checkExtra();
  int resultCode();
  int checkResult();
  void buildEdges();
  void getPattern(char *a, int r, int c, const char *pattern);
  Edge edgePool[TE];
  Edge *point[TP];
  Edge *ep;
  int place[H][W][2];
  int level;
};

#endif // GAME_H

