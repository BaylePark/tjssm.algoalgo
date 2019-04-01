#include <iostream>
using namespace std;
#define MAX_SIZE 22

int arr[MAX_SIZE];
int sortArr[MAX_SIZE];
void merge(int mid, int left, int right) {
	int K = left;
	int L = left;
	int R = right;
	
	for (int i = L; i < right; i++) {
		if (arr[L] < arr[R]) {
			sortArr[K++] = arr[L++];
		}
		else {
			sortArr[K++] = arr[R++];
		}
	}
	
	for (int i = L; i< mid; i++) {
		sortArr[K++] = arr[i];
	}

	for (int i = mid; i< right; i++) {
		sortArr[K++] = arr[i];
	}

	for (int i = left; i < right; i++) {
		arr[i] = sortArr[i];
	}
}

void mergeSort(int left, int right) {
	int mid = (left + right) / 2;
	if (left < right) {
		cout << "left:" << left << " / right:" << right << endl;
		mergeSort(left, mid);
		mergeSort(mid + 1, right);
		merge(mid, left, right);
	}
}

int main() {
	freopen("sample.txt", "r", stdin);
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin>>arr[i];
	}
	mergeSort(0, n - 1);
	for (int i = 0; i < n; i++) {
		cout<< arr[i] <<" ";
	}
	cout << endl;
	return 0;
}