#include <iostream>
using namespace std;
#define MAX_DATA 26
int N;
int arr[MAX_DATA][MAX_DATA][MAX_DATA] = { 0, };
int main() {
	cin >> N;
	for (int i = 0; i < N; i++) {
		char str[4];
		cin >> str;
		int num0 = str[0] - 'a';
		int num1 = str[1] - 'a';
		int num2 = str[2] - 'a';
		arr[num0][num1][num2]++;
	}
	cout << endl;
	for (int i = 0; i < MAX_DATA; i++) {
		for (int j = 0; j < MAX_DATA; j++) {
			for (int k = 0; k < MAX_DATA; k++) {
				for (int q = 0; q < arr[i][j][k]; q++) {
					char ch0 = i + 'a';
					char ch1 = j + 'a';
					char ch2 = k + 'a';
					cout << ch0 << ch1 << ch2 << endl;
				}
			}
		}
	}

	return 0;
}