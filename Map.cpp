#include "Map.h"

void Map::Draw(std::pair<Point, Point> pair, int level) {
  load_level(level);  
  Pixel buf;

  Point left = pair.first;
  Point right = pair.second;

  for(int y = left.y; y <= right.y; ++y) {
    for(int x = left.x; x <= right.x; ++x) {
      switch(data[((WINDOW_HEIGHT - y)/tileSize)*(WINDOW_WIDTH/tileSize) + x/tileSize]) {
        case '.' : {
          buf = floor.GetPixel(x%tileSize, tileSize - (y+1)%tileSize);
          break;
        }
        case ' ' : {
          buf = lava.GetPixel(x%tileSize, tileSize - (y+1)%tileSize);
          break;
        }
        case '#' : {
          buf = wall.GetPixel(x%tileSize, tileSize - (y+1)%tileSize);
          break;
        }
        case '%' : {
          buf = door.GetPixel(x%tileSize, tileSize - (y+1)%tileSize);
          break;
        }
      }
      screen.get()->PutPixel(x, y, buf);
    }
  }
}

bool Map::IsPossible(Point newPoint, int level) {
  if (newPoint.x<0 || newPoint.x>WINDOW_WIDTH-playerSize || newPoint.y<0 || newPoint.y>WINDOW_HEIGHT-playerSize)
    return false;
  if (level!=cur_level)
    load_level(level);
  int left_down  = ((WINDOW_HEIGHT - 1 - newPoint.y)/tileSize)*(WINDOW_WIDTH/tileSize) + newPoint.x/tileSize;
  int right_down = ((WINDOW_HEIGHT - 1 - newPoint.y)/tileSize)*(WINDOW_WIDTH/tileSize) + (newPoint.x + playerSize - 1)/tileSize;
  int left_up    = ((WINDOW_HEIGHT - newPoint.y - playerSize)/tileSize)*(WINDOW_WIDTH/tileSize) + newPoint.x/tileSize;
  int right_up   = ((WINDOW_HEIGHT - newPoint.y - playerSize)/tileSize)*(WINDOW_WIDTH/tileSize) + (newPoint.x + playerSize - 1)/tileSize;
  return (data[left_down]!='#' && data[right_down]!='#' && data[left_up]!='#' && data[right_up]!='#');
}

void Map::load_level(int level) {
  std::string line;
  std::ifstream level_file(levels[level]);
  
  if (level_file.is_open()) {
    data = "";
    while (!level_file.eof()) {
      std::getline(level_file, line);
      data += line;
    }
    level_file.close();
  }
}