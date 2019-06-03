#include <stdio.h>
#define MAX_ARR 10000000

const int kAlphabetCount = 'z' - 'a' + 1;
int countingArr[MAX_ARR] = { 0 };
int _ctoi(const char c) {
	return c - 'a';
}
char _itoc(const int n) {
	return n + 'a';
}

int get_integer(char str[]) {
	int ret = 0;
	for (int i = 0; i < 3; i++) {
		ret *= kAlphabetCount;
		ret += _ctoi(str[i]);
	}
	return ret;
}

void get_string(int number, char str[]) {
	for (int i = 2; i >= 0; i--) {
		str[i] = _itoc(number % kAlphabetCount);
		number /= kAlphabetCount;
	}
	str[3] = 0;
}

int main() {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		char str[4];
		scanf("%s", str);
		countingArr[get_integer(str)]++;
	}

	for (int i = 0; i < MAX_ARR; i++) {
		if (countingArr[i] == 0) continue;
		char str[4] = { 0 };
		get_string(i, str);
		printf("%s\n", str);
		countingArr[i]--;
		i--;
	}
}