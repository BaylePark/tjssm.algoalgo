//결과
//aaa
//adb
//ckw
//cse
//cse
//cse
//dab
//esc
//kej
//kej
//ldk
//zzz
//배열 : 24389

#include <iostream>
using namespace std;

#define MAX_WORD 29
#define TC 12

int counting[MAX_WORD][MAX_WORD][MAX_WORD];
int origin[TC];

int main() {
	int tc = 0;
	cin >> tc;

	while (tc--) {
		char tmp[4];
		cin >> tmp;
		int idx = 0;
		int arr[3];
		while (tmp[idx] != '\0') {
			arr[idx] = tmp[idx] - 'a';
			idx++;
		}
		counting[arr[0]][arr[1]][arr[2]]++;
	}
	for (int i = 0; i < MAX_WORD; i++) {
		for (int j = 0; j < MAX_WORD; j++) {
			for (int k = 0; k < MAX_WORD; k++) {
				while (counting[i][j][k] != 0) {
					char ttt[4] = { 'a'+i,'a'+j,'a'+k, '\0'};
					cout << ttt << endl;
					counting[i][j][k]--;
				}
			}
		}
	}

	cout << "배열 : " << MAX_WORD*MAX_WORD*MAX_WORD << endl;
	return 0;
}