#include <iostream>
using namespace std;

#define MAX_WORD 29

int counting[MAX_WORD][MAX_WORD][MAX_WORD];

int main() {
	int tc = 0;
	cin >> tc;

	while (tc--) {
		char tmp[5];
		cin >> tmp;
		counting[tmp[0] - 'a'][tmp[1] - 'a'][tmp[2] - 'a']++;
	}

	for (int i = 0; i < MAX_WORD; i++) {
		for (int j = 0; j < MAX_WORD; j++) {
			for (int k = 0; k < MAX_WORD; k++) {
				while (counting[i][j][k] != 0) {
					char tmp[4] = { 'a' + i, 'a' + j, 'a' + k, '\0' };
					cout << tmp << endl;
					counting[i][j][k]--;
				}
			}
		}
	}

	return 0;
}