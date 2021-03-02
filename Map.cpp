#include "Map.h"

void Map::Draw(std::pair<Point, Point> pair, int level) {
  load_level(level);  
  Pixel buf;

  Point left = pair.first;
  Point right = pair.second;

  for(int y = left.y; y <= right.y; ++y) {
    for(int x = left.x; x <= right.x; ++x) {
      switch(data[((WINDOW_HEIGHT - y)/tileSize)*(WINDOW_WIDTH/tileSize) + x/tileSize]) {
        case '.': case '@':
          buf = floor.GetPixel(x%tileSize, tileSize - (y+1)%tileSize);
          break;
        case ' ':
          buf = lava.GetPixel(x%tileSize, tileSize - (y+1)%tileSize);
          break;
        case '#':
          buf = wall.GetPixel(x%tileSize, tileSize - (y+1)%tileSize);
          break;
        case '%':
          buf = door.GetPixel(x%tileSize, tileSize - (y+1)%tileSize);
          break;
      }
      screen.get()->PutPixel(x, y, buf);
    }
  }
}

Actions Map::GetAction(Point newPoint, int level) {
  // checking for map end
  if (newPoint.x<0 || newPoint.x>WINDOW_WIDTH-playerSize || newPoint.y<0 || newPoint.y>WINDOW_HEIGHT-playerSize)
    return PL_STOP;
  if (level!=cur_level)
    load_level(level);
  // checking for wall
  int left_down  = ((WINDOW_HEIGHT - 1 - newPoint.y)/tileSize)*(WINDOW_WIDTH/tileSize) + newPoint.x/tileSize;
  int right_down = ((WINDOW_HEIGHT - 1 - newPoint.y)/tileSize)*(WINDOW_WIDTH/tileSize) + (newPoint.x + playerSize - 1)/tileSize;
  int left_up    = ((WINDOW_HEIGHT - newPoint.y - playerSize)/tileSize)*(WINDOW_WIDTH/tileSize) + newPoint.x/tileSize;
  int right_up   = ((WINDOW_HEIGHT - newPoint.y - playerSize)/tileSize)*(WINDOW_WIDTH/tileSize) + (newPoint.x + playerSize - 1)/tileSize;
  if (data[left_down]=='#' || data[right_down]=='#' || data[left_up]=='#' || data[right_up]=='#')
    return PL_STOP;
  // checking for lava
  left_up    = ((WINDOW_HEIGHT - newPoint.y - playerSize/2)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    (newPoint.x + playerSize/2 - 1)/tileSize;
  right_up   = ((WINDOW_HEIGHT - newPoint.y - playerSize/2)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    (newPoint.x + playerSize/2)/tileSize;
  left_down  = ((WINDOW_HEIGHT - 1 - newPoint.y - playerSize/2)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    (newPoint.x + playerSize - 1)/tileSize;
  right_down = ((WINDOW_HEIGHT - 1 - newPoint.y - playerSize/2)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    (newPoint.x + playerSize)/tileSize;
  if (data[left_down]==' ' && data[right_up]==' ' || data[left_up]==' ' && data[right_down]==' ')
    return PL_DIE;
  return PL_GO;
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