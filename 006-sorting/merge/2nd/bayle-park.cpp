#include <stdio.h>
#define MAX_N 100

int ARR[MAX_N];
int TEMP[MAX_N];

typedef bool(*compare_fn)(const int A, const int B);

static bool compare_asc(const int A, const int B) {
	return A < B;
}
static bool compare_desc(const int A, const int B) {
	return A > B;
}

void merge(const int L, const int M, const int R, compare_fn cmp) {
	int l = L;
	int r = M;
	int k = L;
	while (l < M && r <= R) {
		if (cmp(ARR[l], ARR[r])) {
			TEMP[k++] = ARR[l++];
		}
		else {
			TEMP[k++] = ARR[r++];
		}
	}
	while (l < M) {
		TEMP[k++] = ARR[l++];
	}
	while (r <= R) {
		TEMP[k++] = ARR[r++];
	}
	for (int i = L; i <= R; i++) {
		ARR[i] = TEMP[i];
	}
}
void print(const int N) {
	for (int i = 0; i < N; i++) {
		printf("%d ", ARR[i]);
	}
	printf("\n");
}

void mergesort(const int L, const int R, compare_fn cmp) {
	if (L == R) return;

	int mid = L + (R - L) / 2;
	mergesort(L, mid, cmp);
	mergesort(mid + 1, R, cmp);
	merge(L, mid + 1, R, cmp);
}

int main() {
	int N;
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &ARR[i]);
	}
	mergesort(0, N - 1, compare_desc);
	print(N);
	mergesort(0, N - 1, compare_asc);
	print(N);

	return 0;
}