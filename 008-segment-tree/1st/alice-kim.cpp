#include <iostream>
#include <math.h>
using namespace std;

#define MAX_SIZE 1000
long long tree[MAX_SIZE];
long long arr[MAX_SIZE];

long long init(int idx, int start, int end);
void update(int idx, int flag, int start, int end, int diff);
long long sum(int idx, int start, int end, int left, int right);

int main() {
	int N;
	cin >> N;
	int h = ceil(log2(N));
	int tree_size = 1 << (h + 1);
	int changeTime = 0;
	int resultTime = 0;
	cin >> changeTime >> resultTime;
	for (int i = 0; i < N; i++) {
		cin >> arr[i];
	}
	init(0, 0, N-1);
	resultTime += changeTime;
	for (int i = 0; i < resultTime; i++) {
		int t1, t2, t3;
		cin >> t1 >> t2 >> t3;
		if (t1 == 1) {
			t2--;
			update(0, t2, 0, N-1, t3 - arr[t2]);
			arr[t2] = t3;
		}
		else {
			cout << sum(0, 0, N - 1, t2 - 1, t3 - 1) << endl;
		}
	}

	return 0;
}

long long init(int idx, int start, int end) {
	if (start == end) {
		return tree[idx] = arr[start];
	}
	else {
		return tree[idx] = init((idx+1) * 2 - 1, start, (start + end) / 2) + init((idx+1) * 2, (start + end) / 2 + 1, end);
	}
}

void update(int idx, int flag, int start, int end,  int diff) {
	if (flag<start || flag>end) return;
	tree[idx] = tree[idx] + diff;
	if (start != end) {
		update((idx + 1) * 2 - 1, flag,  start, (start + end) / 2, diff);
		update((idx + 1) * 2, flag, (start + end) / 2 + 1, end, diff);
	}
}

long long sum(int idx, int start, int end, int left, int right) {
	if (start > right || end < left) return 0;
	if (start >= left && end <= right) {
		return tree[idx];
	}
	return sum((idx + 1) * 2 - 1, start, (start + end) / 2,left,right) + sum((idx + 1) * 2, (start + end) / 2 + 1, end,left,right);
}