#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Image.h"
#include "Map.h"

enum class MovementDir
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

struct Player
{
  Player(Point pos, const std::string &p_path) :
    coords(pos), 
    old_coords(pos),
    img(Image(p_path)) {};

  bool Moved() const;
  void ProcessInput(MovementDir dir);
  void Draw(Image &screen);

private:
  Point coords {.x = 10, .y = 10};
  Point old_coords {.x = 10, .y = 10};
  Pixel color {.r = 255, .g = 255, .b = 0, .a = 255};

  Image img; 
  int move_speed = 3;

};

#endif //MAIN_PLAYER_H
