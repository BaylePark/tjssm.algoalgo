#include <stdio.h>
#define MAX_N 100
int ARR[MAX_N];
int tempArr[MAX_N];

typedef bool(*compare)(int a, int b);

bool compare_asc(int a, int b) {
	return a > b;
}
bool compare_desc(int a, int b) {
	return a < b;
}

void merge(int arr[], const int left, const int mid, const int right, compare cmp_fn) {
	int i = left;
	int j = mid;
	int sorted = left;

	while (i < mid && j <= right) {
		if (cmp_fn(arr[i], arr[j])) {
			tempArr[sorted] = arr[j];
			j++;
		}
		else {
			tempArr[sorted] = arr[i];
			i++;
		}
		sorted++;
	}

	while (i < mid) {
		tempArr[sorted++] = arr[i++];
	}
	while (j <= right) {
		tempArr[sorted++] = arr[j++];
	}

	for (int idx = left; idx <= right; idx++) {
		arr[idx] = tempArr[idx];
	}
}

void mergesort(int arr[], int left, int right, compare cmp_fn) {
	if (left == right) return;

	int mid = (left + right) / 2;

	mergesort(arr, left, mid, cmp_fn);
	mergesort(arr, mid + 1, right, cmp_fn);
	merge(arr, left, mid + 1, right, cmp_fn);
}

int main() {
	int N;
	scanf("%d", &N);

	for (int i = 0; i < N; i++) {
		scanf("%d", &ARR[i]);
	}

	mergesort(ARR, 0, N - 1, compare_asc);
	for (int i = 0; i < N; i++) {
		printf("%d ", ARR[i]);
	}
	printf("\n");

	mergesort(ARR, 0, N - 1, compare_desc);
	for (int i = 0; i < N; i++) {
		printf("%d ", ARR[i]);
	}
	printf("\n");

	return 0;
}
