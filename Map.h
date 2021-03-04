#ifndef MAP_H
#define MAP_H

#include "Image.h"

#include <fstream>
#include <iostream>
#include <map>
#define GLFW_DLL
#include <GLFW/glfw3.h>

constexpr GLsizei WINDOW_WIDTH = 960, WINDOW_HEIGHT = 960;

enum Actions 
{
  PL_DIE,
  PL_STOP,
  PL_GO, 
  PL_WIN
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

  void Draw(std::pair<Point, Point>, int level=1);
  void BreakDoor(Point curPps);
  Actions GetAction(Point possiblePoint, int level=1);
  void LoadLevel(int level);
  Point GetStart();
private:
  std::shared_ptr<Image> screen;
  Image lava;
  Image floor;
  Image wall;
  Image door;
  Image castle;

  std::map<int, std::string> levels;
  int cur_level;
  std::string data;
};

#endif // MAP_H