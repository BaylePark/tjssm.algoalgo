#include <iostream>
using namespace std;
#define MAX_SIZE 22
int arr[MAX_SIZE];

int kArr[MAX_SIZE];
void merge(int left, int right) {
	int L = left;
	int M = (left + right) / 2;
	int R = M+1;
	int K = 0;

	while (L <= M && R <= right) {
		if (arr[L] < arr[R]) {
			kArr[K++] = arr[L++];
		}
		else {
			kArr[K++] = arr[R++];
		}
	}

	for (int i = L; i <= M; i++) {
		kArr[K++] = arr[i];
	}
	for (int i = R; i <= right; i++) {
		kArr[K++] = arr[i];
	}
	K = 0;
	for (int i = left; i <= right; i++) {
		arr[i] = kArr[K++];
	}
}

void mergeSort(int left, int right) {
	int mid = (left + right) / 2;
	if (left < right) {
		mergeSort(left, mid);
		mergeSort(mid + 1, right);
		merge(left, right);
	}
}

int main() {
	freopen("sample.txt", "r", stdin);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin>>arr[i];
	}
	mergeSort(0, n-1);
	for (int i = 0; i < n; i++) {
		cout<< arr[i] <<" ";
	}
	cout << endl;
	return 0;
}