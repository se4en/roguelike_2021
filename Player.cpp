#include "Player.h"

#include <iostream>

bool Player::Moved() const
{
  return !(coords.x == old_coords.x && coords.y == old_coords.y);
}

void Player::ProcessInput(MovementDir dir, Map &map) 
{
  int move_dist = move_speed * 1;
  switch(dir)
  {
    case MovementDir::UP:
      old_coords.y = coords.y;
      if (map.IsPossible({.x = coords.x, .y = coords.y + move_dist}))
        coords.y += move_dist;
      break;
    case MovementDir::DOWN:
      old_coords.y = coords.y;
      if (map.IsPossible({.x = coords.x, .y = coords.y - move_dist}))
        coords.y -= move_dist;
      break;
    case MovementDir::LEFT:
      old_coords.x = coords.x;
      if (map.IsPossible({.x = coords.x - move_dist, .y = coords.y}))
        coords.x -= move_dist;
      break;
    case MovementDir::RIGHT:
      old_coords.x = coords.x;
      if (map.IsPossible({.x = coords.x + move_dist, .y = coords.y}))
        coords.x += move_dist;
      break;
    default:
      break;
  }
}

std::pair<Point, Point> Player::GetLeftRight() {
  return std::pair<Point, Point>(
    {.x=std::min(old_coords.x, coords.x), .y=std::min(old_coords.y, coords.y)},
    {.x=std::max(old_coords.x, coords.x)+playerSize, .y=std::max(old_coords.y, coords.y)+playerSize});
}

void Player::Draw()
{
  for(int y = coords.y; y <= coords.y + playerSize; ++y)
  {
    for(int x = coords.x; x <= coords.x + playerSize; ++x)
    {
      Pixel buf = img.GetPixel(x - coords.x, playerSize - y + coords.y - 1);
      screen.get()->PutPixel(x, y, buf);
    }
  }
}