#ifndef MAP_H
#define MAP_H

#include "Image.h"

#include <fstream>
#include <iostream>
#include <map>
#define GLFW_DLL
#include <GLFW/glfw3.h>

constexpr GLsizei WINDOW_WIDTH = 960, WINDOW_HEIGHT = 960;

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

  void Draw(Point left, Point right, int level=1);
  bool IsPossible(Point possiblePoint, int level=1);

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

  void load_level(int level);
};

#endif // MAP_H