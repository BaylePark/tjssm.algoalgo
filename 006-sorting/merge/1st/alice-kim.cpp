#include <iostream>
using namespace std;

int Arr[50];

void mergeSort(int L, int R);
void merge(int L, int M, int R);

int main() {

	int tc = 0;
	cin >> tc;

	for (int i = 0; i < tc; i++) {
		cin >> Arr[i];
	}
	mergeSort(0, tc - 1);

	for (int i = 0; i < tc; i++) {
		cout << Arr[i] << " ";
	}
	cout << endl;
	return 0;
}

void mergeSort(int L, int R) {
	if (L >= R) return;

	int m = L + (R-L)/ 2;

	mergeSort(L, m);
	mergeSort(m + 1, R);

	merge(L, m, R);
}


void merge(int L, int M, int R) {
	int n1 = M - L + 1;
	int n2 = R - M;
	int Arr1[50];
	int Arr2[50];

	for (int i = 0; i < n1; i++) {
		Arr1[i] = Arr[L + i];
	}
	for (int i = 0; i < n2; i++) {
		Arr2[i] = Arr[M + i + 1];
	}

	int idx = L;
	int idxL = 0;
	int idxR =0;
	while (idxL < n1 && idxR < n2) {
		if (Arr1[idxL] <= Arr2[idxR]) {
			Arr[idx++] = Arr1[idxL++];
		}
		else {
			Arr[idx++] = Arr2[idxR++];
		}
	}
	while (idxL < n1) {
		Arr[idx++] = Arr1[idxL++];
	}

	while (idxR < n2) {
		Arr[idx++] = Arr2[idxR++];
	}
}