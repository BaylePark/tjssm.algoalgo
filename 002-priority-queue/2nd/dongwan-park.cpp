#include <iostream>
#define MAX_SIZE 20
using namespace std;

int queueSize = 0;
int queueArr[MAX_SIZE];

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

int push(int value) {
	if (queueSize + 1 > MAX_SIZE)
		return 0;

	if (queueSize == 0) {
		queueArr[queueSize++] = value;
		return 1;
	}
	queueArr[queueSize] = value;

	int current = queueSize;
	int parent = (queueSize - 1) / 2;

	while (current != 0 && queueArr[current] < queueArr[parent]) {
		swap(queueArr[current], queueArr[parent]);
		current = parent;
		parent = (queueSize - 1) / 2;
	}
	queueSize++;
	return 1;
}

int pop() {
	if (queueSize == 0)
		return -1;
	int ret = queueArr[0];
	queueSize--;

	swap(queueArr[0], queueArr[queueSize]);

	int current = 0;
	int leftChild = (current) * 2 + 1;
	int rightChild = (current) * 2 + 2;
	int minIndex = current;

	while (leftChild < queueSize) {
		if (queueArr[minIndex] > queueArr[leftChild]) {
			minIndex = leftChild;
		}
		if (rightChild < queueSize&& queueArr[minIndex] > queueArr[rightChild]) {
			minIndex = rightChild;
		}
		if (minIndex == current)
			break;
		swap(queueArr[minIndex], queueArr[current]);
		minIndex = current;
		leftChild = (current) * 2 + 1;
		rightChild = (current) * 2 + 2;
	}
	return ret;
}

int main() {
	push(1);
	push(4);
	push(2);
	push(3);

	for (int i = 0; i < 4; i++) {
		cout << pop() << " ";
	}
	cout << endl;
	return 0;
}