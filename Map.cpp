#include "Map.h"

void Map::Draw(Point left, Point right, int level) {
  for(int y = left.y; y <= right.y; ++y) {
    for(int x = left.x; x <= right.x; ++x) {
      Pixel buf = floor.GetPixel(x - left.x, y - left.y);
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