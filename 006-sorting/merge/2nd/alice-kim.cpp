#include <iostream>
using namespace std;

int Arr[50];
int tmpArr[50];

void mergeSort(int L, int R, bool desc);
void merge(int L, int M, int R, bool desc);

int main() {
	int tc = 0;
	cin >> tc;

	for (int i = 0; i < tc; i++) {
		cin >> Arr[i];
	}
	mergeSort(0, tc - 1, true);
	for (int i = 0; i < tc; i++) {
		cout << Arr[i] << " ";
	} cout << endl;
	mergeSort(0, tc - 1, false);
	for (int i = 0; i < tc; i++) {
		cout << Arr[i] << " ";
	} cout << endl;

	return 0;
}

void mergeSort(int L, int R, bool desc) {
	if (L >= R) return;

	int M = (L + R) / 2;
	mergeSort(L, M, desc);
	mergeSort(M + 1, R, desc);

	merge(L, M, R, desc);
}
void merge(int L, int M, int R, bool desc) {
	int n1 = M - L + 1;
	int n2 = R - M;

	int idx = 0;
	int idxL = 0;
	int idxR = 0;
	while (idxL < n1&& idxR < n2) {
		if (desc) {
			tmpArr[idx++] = Arr[L + idxL] <= Arr[M + 1 + idxR] ? Arr[L + idxL++] : Arr[M + 1 + idxR++];
		}
		else {
			tmpArr[idx++] = Arr[L + idxL] > Arr[M + 1 + idxR] ? Arr[L + idxL++] : Arr[M + 1 + idxR++];
		}
	}
	while (idxL < n1) {
		tmpArr[idx++] = Arr[L + idxL++];
	}
	while (idxR < n2) {
		tmpArr[idx++] = Arr[M + 1 + idxR++];
	}

	for (int i = L; i <= R; i++) {
		Arr[i] = tmpArr[i - L];
	}
}