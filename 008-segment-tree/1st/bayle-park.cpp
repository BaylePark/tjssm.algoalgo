#include <stdio.h>

typedef long long VALUE_TYPE;

const int MAX_N = 1000000;
const int MAX_NODE = (1 << 21);

enum TYPE {
	UPDATE = 1,
	SUM = 2
};

VALUE_TYPE VALUE[MAX_N] = { 0 };
VALUE_TYPE TREE[MAX_NODE] = { 0 };

VALUE_TYPE init_tree(int node, int start, int end) {
	if (start == end) {
		TREE[node] = VALUE[start];
	}
	else {
		int mid = (start + end) / 2;
		TREE[node] = init_tree(node * 2, start, mid) + init_tree(node * 2 + 1, mid + 1, end);
	}
	return TREE[node];
}

void update_tree(int node, int start, int end, const int index, const VALUE_TYPE diff) {
	if (index < start || index > end) return;
	TREE[node] += diff;
	if (start == end) return;
	int mid = (start + end) / 2;
	update_tree(node * 2, start, mid, index, diff);
	update_tree(node * 2 + 1, mid + 1, end, index, diff);
}

VALUE_TYPE sum_tree(int node, int start, int end, int left, int right) {
	if (left > end || right < start) return 0;
	else if (left <= start && right >= end) {
		return TREE[node];
	}
	else {
		int mid = (start + end) / 2;
		return sum_tree(node * 2, start, mid, left, right) + sum_tree(node * 2 + 1, mid + 1, end, left, right);
	}
}

int main() {
	int N, M, K;
	scanf("%d %d %d", &N, &M, &K);
	for (int i = 0; i < N; i++) {
		scanf("%lld", &VALUE[i]);
	}
	init_tree(1, 0, N - 1);

	int L = M + K;
	while (L--) {
		int type;
		scanf("%d", &type);
		switch (type)
		{
		case UPDATE:
		{
			int idx;
			VALUE_TYPE val;
			scanf("%d %lld", &idx, &val);
			VALUE_TYPE diff = val - VALUE[idx - 1];
			VALUE[idx - 1] = val;
			update_tree(1, 0, N - 1, idx - 1, diff);
			break;
		}
		case SUM:
		{
			int left, right;
			scanf("%d %d", &left, &right);
			VALUE_TYPE sum = sum_tree(1, 0, N - 1, left - 1, right - 1);
			printf("%lld\n", sum);
			break;
		}
		}
	}
}