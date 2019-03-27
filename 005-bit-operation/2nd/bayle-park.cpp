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
	unsigned long long g_pattern[PATTERN_SIZE][PATTERN_SIZE];

	template <const int Size>
	unsigned long long get_pattern(const unsigned char picture[Size][Size], pos_s&& pos = { 0, 0 }) {
		unsigned long long pattern = 0;
		for (int dy = 0; dy < 4; dy++) {
			for (int dx = 0; dx < 4; dx++) {
				pattern <<= 4;
				pattern |= picture[pos.y + dy][pos.x + dx];
			}
		}
		return pattern;
	}
	void init(const unsigned char picture[PICT_SIZE][PICT_SIZE]) {
		for (int y = 0; y < PATTERN_SIZE; y++) {
			for (int x = 0; x < PATTERN_SIZE; x++) {
				g_pattern[y][x] = get_pattern<PICT_SIZE>(picture, { x * 4, y * 4 });
			}
		}
		return; 
	}
	int search(const unsigned char pattern[CELL_SIZE][CELL_SIZE],
		pos_s pos[MAX_POS]) {
		unsigned long long targetPattern = get_pattern<CELL_SIZE>(pattern);
		int searchCount = 0;
		for (int y = 0; searchCount < 10 && y < PATTERN_SIZE; y++) {
			for (int x = 0; searchCount < 10 && x < PATTERN_SIZE; x++) {
				if (g_pattern[y][x] == targetPattern) {
					pos[searchCount++] = {x * 4, y * 4};
				}
			}
		}
		return searchCount;
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