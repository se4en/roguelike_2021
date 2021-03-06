#ifndef MAP_H
#define MAP_H

#include "Image.h"

#include <fstream>
#include <iostream>
#include <map>
#include <chrono>
#include <thread>
#include <list>

#define WALLS_COUNT 8
#define FLOORS_COUNT 4
#define LETTERS_COUNT 6

#define GLFW_DLL
#include <GLFW/glfw3.h>

constexpr GLsizei WINDOW_WIDTH = 960, WINDOW_HEIGHT = 960;

enum Actions 
{
  PL_DIE,
  PL_STOP,
  PL_GO, 
  PL_WIN,
};

enum GameStatus 
{
  MP_INGAME,
  MP_2DARK,
  MP_2LVL
};

struct Map
{
  Map(Image* Screen, std::map<std::string, std::string> Tiles, 
      std::map<int, std::string> Levels);

  void Draw(std::pair<Point, Point>, double coef=1);
  void Map2Dark(double coef);
  void PrintLevel1();
  void PrintDie();
  void PrintLevel2();
  void PrintWin();
  void Dark();
  void Dark2Level(double coef);
  void BreakDoor(Point curPps);
  Actions GetAction(Point possiblePoint, int level=1);
  void LoadLevel(int level);
  Point GetStart();
  GameStatus GetStatus() {return status;}
  void SetStatus(GameStatus new_status) {status = new_status;}
private:
  std::shared_ptr<Image> screen;
  Image lava;
  Image* floors;
  Image* walls;
  Image* letters;
  Image door;
  Image castle;

  GameStatus status = MP_INGAME;
  int cur_level = 1;
  std::map<int, std::string> levels;
  std::string data;

  bool _IsWall(int coord);
};

#endif // MAP_H