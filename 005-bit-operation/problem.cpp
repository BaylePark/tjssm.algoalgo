#include <cstdlib>
#include <ctime>
#include <iostream>

const int CELL_SIZE = 4;
const int PATTERN_SIZE = 1000;
const int PICT_SIZE = (CELL_SIZE * PATTERN_SIZE);
const int MAX_POS = 10;

struct pos_s {
  int x, y;
};

namespace algo {
void init(const unsigned char picture[PICT_SIZE][PICT_SIZE]) { return; }
int search(const unsigned char pattern[CELL_SIZE][CELL_SIZE],
           pos_s pos[MAX_POS]) {
  return 0;
}
}  // namespace algo

namespace {
bool is_same(const unsigned char pattern[CELL_SIZE][CELL_SIZE],
             const unsigned char pict[PICT_SIZE][PICT_SIZE], const pos_s& pos) {
  for (int y = 0; y < CELL_SIZE; y++) {
    for (int x = 0; x < CELL_SIZE; x++) {
      if (pict[pos.y + y][pos.x + x] != pattern[y][x]) return false;
    }
  }
  return true;
}
}  // namespace

unsigned char picture[PICT_SIZE][PICT_SIZE];

int main() {
  std::srand(std::time(0));
  for (int y = 0; y < PICT_SIZE; y++) {
    for (int x = 0; x < PICT_SIZE; x++) {
      picture[y][x] = rand() % 16;
    }
  }

  algo::init(picture);

  int SCORE = 1000;
  int TC = 1000;
  while (TC--) {
    unsigned char pattern[CELL_SIZE][CELL_SIZE];
    int X = (rand() % 1000) * 4;
    int Y = (rand() % 1000) * 4;
    for (int y = 0; y < 4; y++) {
      for (int x = 0; x < 4; x++) {
        pattern[y][x] = picture[Y + y][X + x];
      }
    }
    pos_s pos[MAX_POS];
    memset(pos, 0, sizeof(pos_s) * MAX_POS);
    int count = algo::search(pattern, pos);
    if (count == 0) SCORE--;
    for (int i = 0; i < count; i++) {
      if (::is_same(pattern, picture, pos[i]) == false) {
        SCORE--;
        break;
      }
    }
  }

  std::cout << "SCORE: " << SCORE << "/1000" << std::endl;
  return 0;
}
