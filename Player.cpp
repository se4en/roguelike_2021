#include "Player.h"

#include <iostream>

Player::Player(Image* Screen, Point Pos, std::map<std::string, std::string> Tiles) :
  screen(Screen),
  start(Pos), 
  coords(Pos), 
  old_coords(Pos),
  status(ST_ON_RUN),
  icon(STAY_R),
  cntr(0) {


  stay_r = new Image[STAY_CNT] {
  Image(Tiles["stay_r-0"]),
  Image(Tiles["stay_r-1"]),
  Image(Tiles["stay_r-2"]),
  Image(Tiles["stay_r-3"])};
  stay_l = new Image[STAY_CNT] {
  Image(Tiles["stay_l-0"]),
  Image(Tiles["stay_l-1"]),
  Image(Tiles["stay_l-2"]),
  Image(Tiles["stay_l-3"])};
  run_r = new Image[RUN_CNT] {
  Image(Tiles["run_r-0"]),
  Image(Tiles["run_r-1"]),
  Image(Tiles["run_r-2"]),
  Image(Tiles["run_r-3"]),
  Image(Tiles["run_r-4"]),
  Image(Tiles["run_r-5"])};
  run_l = new Image[RUN_CNT] {
  Image(Tiles["run_l-0"]),
  Image(Tiles["run_l-1"]),
  Image(Tiles["run_l-2"]),
  Image(Tiles["run_l-3"]),
  Image(Tiles["run_l-4"]),
  Image(Tiles["run_l-5"])};
}

bool Player::Moved() const {
  return !(coords.x == old_coords.x && coords.y == old_coords.y);
}

void Player::ProcessInput(MovementDir dir, Map &map) {
  int move_dist = move_speed * 1;
  switch(dir) {
    case MovementDir::UP:
      old_coords.y = coords.y;
      switch (map.GetAction({.x = coords.x, .y = coords.y + move_dist})) {
        case PL_DIE: 
          status = ST_DIED;
          coords.y += move_dist;
          break;
        case PL_WIN: 
          status = ST_WON;
          coords.y += move_dist;
          break;
        case PL_GO: 
          coords.y += move_dist;
          break;
        case PL_STOP:
          break;
      }
      break;
    case MovementDir::DOWN:
      old_coords.y = coords.y;
      switch (map.GetAction({.x = coords.x, .y = coords.y - move_dist})) {
        case PL_DIE: 
          status = ST_DIED;
          coords.y -= move_dist;
          break;
        case PL_WIN: 
          status = ST_WON;
          coords.y -= move_dist;
          break;
        case PL_GO: 
          coords.y -= move_dist;
          break;
        case PL_STOP:
          break;
      }
      break;
    case MovementDir::LEFT:
      icon = RUN_L;
      old_coords.x = coords.x;
      switch (map.GetAction({.x = coords.x - move_dist, .y = coords.y})) {
        case PL_DIE: 
          status = ST_DIED;
          coords.x -= move_dist;
          break;
        case PL_WIN: 
          status = ST_WON;
          coords.x -= move_dist;
          break;
        case PL_GO: 
          coords.x -= move_dist;
          break;
        case PL_STOP:
          break;
      }
      break;
    case MovementDir::RIGHT:
      icon = RUN_R;
      old_coords.x = coords.x;
      switch (map.GetAction({.x = coords.x + move_dist, .y = coords.y})) {
        case PL_DIE: 
          status = ST_DIED;
          coords.x += move_dist;
          break;
        case PL_WIN: 
          status = ST_WON;
          coords.x += move_dist;
          break;
        case PL_GO: 
          coords.x += move_dist;
          break;
        case PL_STOP:
          break;
      }
      break;
    default:
      old_coords.x = coords.x;
      old_coords.y = coords.y;
      break;
  }
}

std::pair<Point, Point> Player::GetLeftRight() {
  return std::pair<Point, Point>(
    {.x=std::min(old_coords.x, coords.x), .y=std::min(old_coords.y, coords.y)},
    {.x=std::max(old_coords.x, coords.x)+playerSize, .y=std::max(old_coords.y, coords.y)+playerSize});
}

void Player::Draw() {
  Image* img;
  switch (icon) {
    case RUN_R:
      img = run_r + cntr%RUN_CNT;
      break;
    case RUN_L:
      img = run_l + cntr%RUN_CNT;
      break;
    case STAY_R:
      img = stay_r + cntr%STAY_CNT;
      break;
    case STAY_L:
      img = stay_l + cntr%STAY_CNT;
      break;
  }
  for(int y = coords.y; y <= coords.y + playerSize; ++y) {
    for(int x = coords.x; x <= coords.x + playerSize; ++x) {
      Pixel buf = img->GetPixel(x - coords.x, playerSize - y + coords.y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  }
}

void Player::Restart() {
  old_coords = start;
  coords = start;
  status = ST_ON_RUN;
}