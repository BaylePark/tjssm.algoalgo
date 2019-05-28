#include <iostream>
using namespace std;
long long mArr[1000000];
long long mTree[1000000];
long long start, end;
int N, M, K;
int a, b, c;

long long init(long long *arr, long long*tree, long long node, long long start, long long end)
{
	if (start == end)
			return tree[node] = arr[start];
	int mid = (start + end) / 2;
	return tree[node] = init(arr, tree, node * 2, start, mid) + init(arr, tree, node * 2 + 1, mid + 1, end);
}

void update(long long* tree, long long node, long long start, long long end, long long index, long long diff)
{
	if (!(start <= index && index <= end))
		return;

	tree[node] += diff;

	if (start != end)
	{
		int mid = (start + end) / 2;
		update(tree, node * 2, start, mid, index, diff);
		update(tree, node * 2 + 1, mid + 1, end, index, diff);
	}

}

int main() {
	cin >> N;
	cin >> M;
	cin >> K;
	for (int i = 0; i < N; i++) {
		cin >> mArr[i];
	}
	init(mArr, mTree, 1, 1, N);
	for (int i = 0; i < M + K; i++) {
		cin >> a;
		cin >> b;
		cin >> c;
	}

	return 0;
}