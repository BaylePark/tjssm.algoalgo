#include <iostream>
using namespace std;
/*
10
aaa
zzz
adb
cse
ldk
ckw
cse
cse
kej
kej
*/

#define MAX_SIZE 26
int main() {
	freopen("input.txt", "r", stdin);

	int n;
	cin >> n;

	int arr[MAX_SIZE][MAX_SIZE][MAX_SIZE] = { 0, };
	for (int i = 0; i < n; i++) {
		char str[5];
		cin >> str;

		int num1 = str[0] - 'a';
		int num2 = str[1] - 'a';
		int num3 = str[2] - 'a';

		arr[num1][num2][num3] = arr[num1][num2][num3] + 1;
	}


	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < MAX_SIZE; j++) {
			for (int k = 0; k < MAX_SIZE; k++) {
				if (arr[i][j][k] != 0) {
					for (int p = 0; p < arr[i][j][k]; p++) {
						char ch1 = i + 'a';
						char ch2 = j + 'a';
						char ch3 = k + 'a';
						cout << ch1 << ch2 << ch3 << endl;
					}
				}
			}
		}
	}
	cout << "arr size : 17576" << endl;
	return 0;
}

/*
aaa
adb
ckw
cse
cse
cse
kej
kej
ldk
zzz
arr size : 17576
*/