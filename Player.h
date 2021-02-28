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
  Player(Image* Screen, Point Pos, const std::string &P_path) :
    screen(Screen),
    coords(Pos), 
    old_coords(Pos),
    img(Image(P_path)) {};

  bool Moved() const;
  void ProcessInput(MovementDir dir);
  void Draw();

private:
  Point coords {.x = 10, .y = 10};
  Point old_coords {.x = 10, .y = 10};
  Pixel color {.r = 255, .g = 255, .b = 0, .a = 255};

  Image img; 
  std::shared_ptr<Image> screen;
  int move_speed = 3;

};

#endif //MAIN_PLAYER_H
