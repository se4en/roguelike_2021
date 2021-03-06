#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Image.h"
#include "Map.h"
#include <tuple>
#include <algorithm> 

enum class MovementDir
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

enum Status
{
  ST_ON_RUN, 
  ST_DIED,
  ST_WON
};

struct Player
{
  Player(Image* Screen, Point Pos, const std::string &P_path) :
    screen(Screen),
    start(Pos), 
    coords(Pos), 
    old_coords(Pos),
    status(ST_ON_RUN),
    cntr(0),
    img(Image(P_path)) {};

  bool Moved() const;
  void ProcessInput(MovementDir dir, Map &map);
  void Draw();
  std::pair<Point, Point> GetLeftRight();
  void Restart();
  Status GetStatus() {return status;};
  Point GetCoords() {return coords;};

  uint8_t cntr;
private:
  Point coords {.x = 10, .y = 10};
  Point old_coords {.x = 10, .y = 10};
  Point start {.x = 10, .y = 10};
  Pixel color {.r = 255, .g = 255, .b = 0, .a = 255};
  Status status;

  Image img; 
  std::shared_ptr<Image> screen;
  int move_speed = 4;
};

#endif //MAIN_PLAYER_H
