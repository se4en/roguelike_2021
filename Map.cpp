#include "Map.h"

Map::Map(Image* Screen, std::map<std::string, std::string> Tiles, 
      std::map<int, std::string> Levels) : 
    screen(Screen),
    cur_lava(0),
    door(Image(Tiles["door"])),
    castle(Image(Tiles["castle"])),
    levels(Levels) {
  lava = new Image[LAVA_COUNT] {
  Image(Tiles["lava_1"]),
  Image(Tiles["lava_2"]),
  Image(Tiles["lava_3"]),
  Image(Tiles["lava_4"]),
  Image(Tiles["lava_5"]),
  Image(Tiles["lava_6"]),
  Image(Tiles["lava_7"]),
  Image(Tiles["lava_8"])};
  floors = new Image[FLOORS_COUNT] {
  Image(Tiles["floor_1"]),
  Image(Tiles["floor_2"]),
  Image(Tiles["floor_3"]),
  Image(Tiles["floor_4"])};
  walls = new Image[WALLS_COUNT] {
  Image(Tiles["wall_A"]),
  Image(Tiles["wall_B"]),
  Image(Tiles["wall_C"]),
  Image(Tiles["wall_D"]),
  Image(Tiles["wall_E"]),
  Image(Tiles["wall_F"]),
  Image(Tiles["wall_G"]),
  Image(Tiles["wall_H"]),
  Image(Tiles["wall_J"]),
  Image(Tiles["wall_K"]),
  Image(Tiles["wall_L"]),
  Image(Tiles["wall_M"]),
  Image(Tiles["wall_N"]),
  Image(Tiles["wall_O"]),
  Image(Tiles["wall_P"]),
  Image(Tiles["wall_Q"]),
  Image(Tiles["wall_R"]),
  Image(Tiles["wall_S"]),
  Image(Tiles["wall_T"]),
  Image(Tiles["wall_U"]),
  Image(Tiles["wall_V"])};
  letters = new Image[LETTERS_COUNT] {
  Image(Tiles["A"]), // 0
  Image(Tiles["L"]), // 1
  Image(Tiles["E"]), // 2
  Image(Tiles["V"]), // 3
  Image(Tiles["1"]), // 4
  Image(Tiles["2"]), // 5
  Image(Tiles["Y"]), // 6
  Image(Tiles["O"]), // 7
  Image(Tiles["U"]), // 8
  Image(Tiles["D"]), // 9
  Image(Tiles["I"]), // 10
  Image(Tiles["!"]), // 11
  Image(Tiles["W"]), // 12
  Image(Tiles["N"]), // 13
  Image(Tiles["T"]), // 14
  Image(Tiles["B"]), // 15
  Image(Tiles[")"])}; // 16
}

Map::~Map() {
  delete[] lava;
  delete[] floors;
  delete[] walls;
  delete[] letters;
}

void Map::Draw(std::pair<Point, Point> pair, double coef) {
  Pixel buf;

  Point left = pair.first;
  Point right = pair.second;

  int ind;

  for(int y = left.y; y <= right.y; ++y) {
    for(int x = left.x; x <= right.x; ++x) {
      switch(data[((WINDOW_HEIGHT - y - 1)/tileSize)*(WINDOW_WIDTH/tileSize) + x/tileSize]) {
        case '.': case '@':
          if (y%2) 
            if (x%2)
              ind = 1;
            else 
              ind = 0;
          else 
            if (x%2) 
              ind = 3;
            else 
              ind = 2;
          buf = floors[ind].GetPixel(x%tileSize, tileSize - (y-1)%tileSize - 1);
          break;
        case ' ':
          buf = lava[0].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'A':
          buf = walls[0].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'B':
          buf = walls[1].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'C':
          buf = walls[2].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'D':
          buf = walls[3].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'E':
          buf = walls[4].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'F':
          buf = walls[5].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'G':
          buf = walls[6].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'H':
          buf = walls[7].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'J':
          buf = walls[8].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'K':
          buf = walls[9].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'L':
          buf = walls[10].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'M':
          buf = walls[11].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'N':
          buf = walls[12].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'O':
          buf = walls[13].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'P':
          buf = walls[14].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'Q':
          buf = walls[15].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'R':
          buf = walls[16].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'S':
          buf = walls[17].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'T':
          buf = walls[18].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'U':
          buf = walls[19].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'V':
          buf = walls[20].GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case '%':
          buf = door.GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
        case 'x':
          buf = castle.GetPixel(x%tileSize, tileSize - (y-1)%tileSize-1);
          break;
      }
      buf.r *= coef; buf.g *= coef; buf.b *= coef; buf.a *= coef;
      screen.get()->PutPixel(x, y , buf);
    }
  }
}

void Map::Map2Dark(double coef) {
  Pixel buf;
  for (int x = 0; x < WINDOW_WIDTH; x++) {
    for (int y = 0; y < WINDOW_HEIGHT; y++) {
      buf = screen.get()->GetPixel(x, y);
      buf.r *= coef; buf.g *= coef; buf.b *= coef; buf.a *= coef;
      screen.get()->PutPixel(x, y, buf);
    }
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(40));
}


void Map::Dark2Level(double coef) {
  Pixel buf;
  Draw(std::pair<Point, Point>(std::pair<Point, Point>({.x=0, .y=0}, {.x=WINDOW_WIDTH-1, .y=WINDOW_HEIGHT-1})), coef);
  std::this_thread::sleep_for(std::chrono::milliseconds(40));
}


bool Map::
_IsWall(int coord) {
  return (
    data[coord]=='A' || data[coord]=='B' || data[coord]=='C' || data[coord]=='D' ||
    data[coord]=='E' || data[coord]=='F' || data[coord]=='G' || data[coord]=='H' ||
    data[coord]=='G' || data[coord]=='K' || data[coord]=='L' || data[coord]=='M' ||
    data[coord]=='N' || data[coord]=='O' || data[coord]=='P' || data[coord]=='Q' ||
    data[coord]=='R' || data[coord]=='S' || data[coord]=='T' || data[coord]=='U' ||
    data[coord]=='V' || data[coord]=='W' || data[coord]=='X' || data[coord]=='J' ||
    data[coord]=='%'
  );
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
  if (_IsWall(left_down) || _IsWall(right_down) || _IsWall(left_up) || _IsWall(right_up)) {
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


void Map::PrintLevel1() {
  int to_x = 350;
  int to_y = 600;
  Pixel buf;

  // L
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[1].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  }  
  to_x += letterSize + 5;
  // E
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[2].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  }  
  to_x += letterSize + 5;
  // V
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[3].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 5;
  // E
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[2].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 5;
  // L
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[1].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 20;
  // 1
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[4].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
}

void Map::PrintDie() {
  int to_x = 325;
  int to_y = 600;
  Pixel buf;

  // Y
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[6].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  }  
  to_x += letterSize + 5;
  // O
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[7].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  }  
  to_x += letterSize + 5;
  // U
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[8].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 20;
  // D
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[9].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 5;
  // I
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[10].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 5;
  // E
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[2].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 20;
  // !
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[11].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
}

void Map::PrintLevel2() {
  int to_x = 350;
  int to_y = 600;
  Pixel buf;

  // L
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[1].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  }  
  to_x += letterSize + 5;
  // E
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[2].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  }  
  to_x += letterSize + 5;
  // V
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[3].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 5;
  // E
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[2].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 5;
  // L
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[1].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 20;
  // 2
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[5].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
}

void Map::PrintWin() {
  int to_x = 325;
  int to_y = 600;
  Pixel buf;

  // Y
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[6].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  }  
  to_x += letterSize + 5;
  // O
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[7].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  }  
  to_x += letterSize + 5;
  // U
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[8].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 20;
  // W
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[12].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 5;
  // I
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[10].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 5;
  // N
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[13].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 20;
  // !
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[11].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
}


void Map::PrintNotBad() {
  int to_x = 325;
  int to_y = 600;
  Pixel buf;

  // N
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[13].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  }  
  to_x += letterSize + 5;
  
  // O
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[7].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  }  
  to_x += letterSize + 5;
  // T
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[14].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 20;
  // B
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[15].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 5;
  // A
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[0].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 5;
  
  // D
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[9].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
  to_x += letterSize + 20;
  
  // !
  for(int y = to_y; y < to_y + letterSize; ++y) {
    for(int x = to_x; x < to_x + letterSize; ++x) {
      buf = letters[16].GetPixel(x%to_x, letterSize - (y)%to_y - 1);
      if (buf.r!=0 || buf.g!=0 || buf.b!=0) {
        screen.get()->PutPixel(x, y, buf);
      }
    }
  } 
}

void Map::Dark() {
  Pixel buf;

  for(int y = 0; y < WINDOW_HEIGHT; ++y) {
    for(int x = 0; x < WINDOW_WIDTH; ++x) {
      buf = letters[1].GetPixel(0, 0);
      screen.get()->PutPixel(x, y, buf);
    }
  }  
}


void Map::StepLava() {
  Pixel buf;
  int to_x, to_y;
  int cur_x, cur_y;
  int ind;

  if (flag) {
    cur_lava++;
    for (int i=0; i<(WINDOW_HEIGHT/tileSize)*(WINDOW_WIDTH/tileSize); ++i) {
    //return Point{.x = , .y = };
      //};
      if (data[i]==' ') {
        to_x = tileSize*(i%(WINDOW_WIDTH/tileSize));
        to_y = WINDOW_HEIGHT - tileSize*(i/(WINDOW_HEIGHT/tileSize) + 1);
        
        for(int y = to_y; y < to_y + tileSize; ++y) {
          for(int x = to_x; x < to_x + tileSize; ++x) {
            cur_x = x%to_x;
            cur_y = y%to_y;
            ind = 0;//cur_x%2;
            buf = lava[(cur_lava+ind)%LAVA_COUNT].GetPixel(cur_x, tileSize - cur_y - 1);
            screen.get()->PutPixel(x, y, buf);
          }
        }
      }
    }
    flag = false;
  }
  else {
    flag = true;
  }
}