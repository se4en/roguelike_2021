#ifndef MAP_H
#define MAP_H

#include "Image.h"

#include <fstream>
#include <iostream>
#include <map>
#include <chrono>
#include <thread>

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
      std::map<int, std::string> Levels) :
    screen(Screen),
    lava(Image(Tiles["lava"])),
    floor(Image(Tiles["floor"])),
    wall(Image(Tiles["wall"])),
    door(Image(Tiles["door"])),
    castle(Image(Tiles["castle"])),
    levels(Levels),
    cur_level(1) {};

  void Draw(std::pair<Point, Point>, double coef=1);
  void Map2Dark(double coef);
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
  Image floor;
  Image wall;
  Image door;
  Image castle;

  GameStatus status = MP_INGAME;
  int cur_level;
  std::map<int, std::string> levels;
  std::string data;
};

#endif // MAP_H