#include <iostream>
using namespace std;

#define MAX_SIZE 30

int arr[MAX_SIZE];
int qSize = 0;

void swap(int *a, int *b) {
	int temp = *a;
	a = b;
	*b = temp;
}

void push(int data) {
	if (qSize == MAX_SIZE)
		return;

	if (qSize == 0) {
		arr[qSize++] = data;
		return;
	}
	arr[qSize] = data;

	int current = qSize;
	int parent = (qSize - 1) / 2;
	while (current > 0 && arr[current] < arr[parent]) {
		swap(arr[current], arr[parent]);
		current = parent;
		parent = (parent - 1) / 2;;
	}
	qSize++;
}

int pop() {
	if (qSize < 0)
		return -1;

	int pop = arr[0];
	qSize--;

	arr[0] = arr[qSize];

	int current = 0;
	int left = (current * 2) + 1;
	int right = (current * 2) + 2;
	int minNode = current;

	while (left < qSize) {
		if (arr[minNode] > arr[left]) {
			minNode = left;
		}
		if (right <qSize && arr[minNode] > arr[right]) {
			minNode = right;
		}
		if (minNode == current)
			break;

		swap(arr[current], arr[minNode]);
		current = minNode;
		left = (current * 2) + 1;
		right = (current * 2) + 2;
	}
	return pop;
}


int main() {
	//push(10);
	//push(49);
	//push(38);
	//push(17);
	//push(56);
	//push(92);
	//push(8);
	//push(1);
	//push(13);
	//push(55);

	//for (int i = 0; i < 10; i++) {
	//   cout << pop() << " ";
	//}
	//cout << endl;

	push(4);
	push(22);
	push(50);
	push(13);
	push(5);
	push(1);
	push(22);
	push(35);
	push(21);
	push(7);
	push(99);
	push(100);
	push(14);

	for (int i = 0; i < 13; i++) {
		cout << pop() << " ";
	}
	cout << endl;


	return 0;
}