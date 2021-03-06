#ifndef MAIN_PLAYER_H
#define MAIN_PLAYER_H

#include "Image.h"
#include "Map.h"
#include <tuple>
#include <algorithm> 

#define RUN_CNT 6
#define STAY_CNT 4

enum class MovementDir
{
  UP,
  DOWN,
  LEFT,
  RIGHT, 
  NONE
};

enum Status
{
  ST_ON_RUN, 
  ST_DIED,
  ST_WON
};

enum Icon
{
  STAY_R,
  STAY_L,
  RUN_R, 
  RUN_L
};

struct Player
{
  Player(Image* Screen, Point Pos, std::map<std::string, std::string> Tiles);

  bool Moved() const;
  void ProcessInput(MovementDir dir, Map &map);
  void Draw();
  std::pair<Point, Point> GetLeftRight();
  void Restart();
  Status GetStatus() {return status;};
  Point GetCoords() {return coords;};

  uint8_t cntr;
  Icon icon;
  Status status;
private:
  Point coords {.x = 10, .y = 10};
  Point old_coords {.x = 10, .y = 10};
  Point start {.x = 10, .y = 10};
  Pixel color {.r = 255, .g = 255, .b = 0, .a = 255};


  Image* stay_r;
  Image* stay_l;
  Image* run_r;
  Image* run_l;

  std::shared_ptr<Image> screen;
  int move_speed = 4;
};

#endif //MAIN_PLAYER_H
