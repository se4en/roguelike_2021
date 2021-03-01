#include "Map.h"

void Map::Draw(Point left, Point right, int level) {
  load_level(level);  
  Pixel buf;

  for(int y = left.y; y <= right.y; ++y) {
    for(int x = left.x; x <= right.x; ++x) {
      switch(data[((WINDOW_HEIGHT - y)/tileSize)*(WINDOW_WIDTH/tileSize) + x/tileSize]) {
        case ' ' : {
          buf = floor.GetPixel(x%tileSize, tileSize - y%tileSize);
          break;
        }
        case '#' : {
          buf = wall.GetPixel(x%tileSize, tileSize - y%tileSize);
          break;
        }
      }
      screen.get()->PutPixel(x, y, buf);
    }
  }
}

bool Map::IsPossible(Point left, Point right, int level) {
  return true;
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