#include <stdio.h>

const int NUM_ALPHA = ((int)('z' - 'a' + 1));
const int MAX_SIZE = (NUM_ALPHA * NUM_ALPHA * NUM_ALPHA);

int Array[MAX_SIZE] = { 0 };

int toNumber(char str[4]) {
	int idx = 0;
	int num = 0;
	while (str[idx]) {
		num *= NUM_ALPHA;
		num += (int)(str[idx] - 'a');
		idx++;
	}
	return num;
}
void toString(int num, char str[4]) {
	for (int i = 2; i >= 0; i--) {
		str[i] = (num%NUM_ALPHA) + 'a';
		num /= NUM_ALPHA;
	}
}

/*
12
aaa
zzz
adb
dab
cse
esc
ldk
ckw
cse
cse
kej
kej
*/

int main() {
	printf("AlphaNum(%d) ArrSize(%d)\n", NUM_ALPHA, MAX_SIZE);
	int N;
	scanf("%d", &N);
	while (N--) {
		char str[4];
		scanf("%s", str);
		int num = toNumber(str);
		Array[num]++;
	}
	printf("\n\n:: ANSWER ::\n");
	for (int i = 0; i < MAX_SIZE; i++) {
		for (int j = 0; j < Array[i]; j++) {
			char decodedStr[4] = { 0 };
			toString(i, decodedStr);
			printf(decodedStr);
			printf("\n");
		}
	}
	return 0;
}