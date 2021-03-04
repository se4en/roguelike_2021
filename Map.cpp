#include "Map.h"

void Map::Draw(std::pair<Point, Point> pair, int level) {
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
        case 'x':
          buf = castle.GetPixel(x%tileSize, tileSize - (y+1)%tileSize);
          break;
      }
      screen.get()->PutPixel(x, y, buf);
    }
  }
}

Actions Map::GetAction(Point newPoint, int level) {
  // checking for map end
  if (newPoint.x<0 || newPoint.x>WINDOW_WIDTH-playerSize || newPoint.y<0 || newPoint.y>WINDOW_HEIGHT-playerSize) {
    return PL_STOP;
  }
  // checking for wall or door
  int left_down  = ((WINDOW_HEIGHT - 1 - newPoint.y)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    newPoint.x/tileSize;
  int right_down = ((WINDOW_HEIGHT - 1 - newPoint.y)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    (newPoint.x + playerSize - 1)/tileSize;
  int left_up    = ((WINDOW_HEIGHT - newPoint.y - playerSize)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    newPoint.x/tileSize;
  int right_up   = ((WINDOW_HEIGHT - newPoint.y - playerSize)/tileSize)*(WINDOW_WIDTH/tileSize) +
                    (newPoint.x + playerSize - 1)/tileSize;
  if (data[left_down]=='#' || data[right_down]=='#' || data[left_up]=='#' || data[right_up]=='#' ||
      data[left_down]=='%' || data[right_down]=='%' || data[left_up]=='%' || data[right_up]=='%') {
    return PL_STOP;
  }
  // checking for lava
  left_up    = ((WINDOW_HEIGHT - newPoint.y - playerSize/2)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    (newPoint.x + playerSize/2 - 1)/tileSize;
  right_up   = ((WINDOW_HEIGHT - newPoint.y - playerSize/2)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    (newPoint.x + playerSize/2)/tileSize;
  left_down  = ((WINDOW_HEIGHT - 1 - newPoint.y - playerSize/2)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    (newPoint.x + playerSize/2 - 1)/tileSize;
  right_down = ((WINDOW_HEIGHT - 1 - newPoint.y - playerSize/2)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    (newPoint.x + playerSize/2)/tileSize;
  if (data[left_down]==' ' && data[right_up]==' ' || data[left_up]==' ' && data[right_down]==' ') {
    return PL_DIE;
  }
  // checking for castle
  if (data[left_down]=='x' && data[right_up]=='x' || data[left_up]=='x' && data[right_down]=='x') {
    return PL_WIN;
  }
  return PL_GO;
}

void Map::BreakDoor(Point curPos) {
  int left_up    = ((WINDOW_HEIGHT - curPos.y - playerSize/2)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    (curPos.x - 1)/tileSize;
  int left_down  = ((WINDOW_HEIGHT - 1 - curPos.y - playerSize/2)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    (curPos.x - 1)/tileSize;

  int right_up   = ((WINDOW_HEIGHT - curPos.y - playerSize/2)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    (curPos.x + playerSize)/tileSize;
  int right_down = ((WINDOW_HEIGHT - 1 - curPos.y - playerSize/2)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    (curPos.x + playerSize)/tileSize;

  int down_left  = ((WINDOW_HEIGHT - 1 - curPos.y + playerSize)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    (curPos.x + playerSize/2 - 1)/tileSize;
  int down_right = ((WINDOW_HEIGHT - 1 - curPos.y + playerSize)/tileSize)*(WINDOW_WIDTH/tileSize) + 
                    (curPos.x + playerSize/2)/tileSize;

  int up_left    = ((WINDOW_HEIGHT - curPos.y)/tileSize - 1)*(WINDOW_WIDTH/tileSize) + 
                    (curPos.x + playerSize/2 - 1)/tileSize;
  int up_right   = ((WINDOW_HEIGHT - curPos.y)/tileSize - 1)*(WINDOW_WIDTH/tileSize) + 
                    (curPos.x + playerSize/2)/tileSize;

  if (right_up==right_down && data[right_up]=='%') { 
    data[right_up] = '.';
    // here could be door breaking animation
    Draw(std::pair<Point, Point>(
      {.x = tileSize*(right_up%(WINDOW_WIDTH/tileSize)), .y = WINDOW_HEIGHT - tileSize*(right_up/(WINDOW_HEIGHT/tileSize) + 1)}, 
      {.x = tileSize*(right_up%(WINDOW_WIDTH/tileSize) + 1), .y = WINDOW_HEIGHT - tileSize*(right_up/(WINDOW_HEIGHT/tileSize))}));
  }
  else if (left_up==left_down && data[left_up]=='%') {
    data[left_up] = '.';
    Draw(std::pair<Point, Point>(
      {.x = tileSize*(left_up%(WINDOW_WIDTH/tileSize)), .y = WINDOW_HEIGHT - tileSize*(left_up/(WINDOW_HEIGHT/tileSize) + 1)}, 
      {.x = tileSize*(left_up%(WINDOW_WIDTH/tileSize) + 1), .y = WINDOW_HEIGHT - tileSize*(left_up/(WINDOW_HEIGHT/tileSize))}));
  }
  else if (up_left==up_right && data[up_left]=='%') { 
    data[up_left] = '.';
    Draw(std::pair<Point, Point>(
      {.x = tileSize*(up_left%(WINDOW_WIDTH/tileSize)), .y = WINDOW_HEIGHT - tileSize*(up_left/(WINDOW_HEIGHT/tileSize) + 1)}, 
      {.x = tileSize*(up_left%(WINDOW_WIDTH/tileSize) + 1), .y = WINDOW_HEIGHT - tileSize*(up_left/(WINDOW_HEIGHT/tileSize))}));
  }
  else if (down_left==down_right && data[down_left]=='%') { 
    data[down_left] = '.';
    Draw(std::pair<Point, Point>(
      {.x = tileSize*(down_left%(WINDOW_WIDTH/tileSize)), .y = WINDOW_HEIGHT - tileSize*(down_left/(WINDOW_HEIGHT/tileSize) + 1)}, 
      {.x = tileSize*(down_left%(WINDOW_WIDTH/tileSize) + 1), .y = WINDOW_HEIGHT - tileSize*(down_left/(WINDOW_HEIGHT/tileSize))}));
  }
}

void Map::LoadLevel(int level) {
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

Point Map::GetStart() {
  int pos = data.find("@");
  return Point{.x = tileSize*(pos%(WINDOW_WIDTH/tileSize)), .y = WINDOW_HEIGHT - tileSize*(pos/(WINDOW_HEIGHT/tileSize) + 1)};
}