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

Point Player::GetLeft() {
  return old_old_coords;
}

Point Player::GetRight() {
  return coords;
}

void Player::Draw()
{
  if(Moved())
  {
    // need check is it possible
    // if (map.IsPossible()) {
    //  
    // } 

	  Point left{.x = WINDOW_WIDTH / 2, .y = WINDOW_HEIGHT / 2};
    // map.Draw();
    for(int y = old_coords.y; y <= old_coords.y + playerSize; ++y)
    {
      for(int x = old_coords.x; x <= old_coords.x + playerSize; ++x)
      {
        screen.get()->PutPixel(x, y, backgroundColor);
      }
    }
    old_old_coords = old_coords;
    old_coords = coords;
  }

  for(int y = coords.y; y <= coords.y + playerSize; ++y)
  {
    for(int x = coords.x; x <= coords.x + playerSize; ++x)
    {
      //std::cout << "here" << std::endl;
      Pixel buf = img.GetPixel(x - coords.x, playerSize - y + coords.y - 1);
      //Pixel buf = img.GetPixel(1, 1);
      screen.get()->PutPixel(x, y, buf);
      //screen.PutPixel(x, y, color);
    }
  }
}