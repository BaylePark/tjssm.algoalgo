#include <iostream>
using namespace std;
#define MAX_NODE 1000
#define MAX (A>B) ? A : B

struct Node {
	int data;
};

Node qNode[MAX_NODE];
int nodeCount;

void swapData(Node& node1, Node& node2) {
	int tmp = node1.data;
	node1.data = node2.data;
	node2.data = tmp;
}

void enQueue(int data) {
	qNode[nodeCount].data = data;
	int parent = (nodeCount - 1) / 2;
	int idx = nodeCount;
	while (parent >=0 && idx != 0) {
		if (qNode[parent].data < qNode[idx].data) {
			break;
		}
		swapData(qNode[parent], qNode[idx]);
		idx = parent;
		parent = (parent - 1) / 2;
	}
	nodeCount++;
}

int deQueue() {
	int result = qNode[0].data;
	qNode[0].data = qNode[--nodeCount].data;
	int idx = 0;
	int Left = (idx * 2) + 1;
	int Right = Left + 1;
	while (Left < nodeCount) {
		if (Right < nodeCount) {
			if (qNode[Left].data < qNode[Right].data) {
				if (qNode[idx].data < qNode[Left].data) {
					break;
				}
				else {
					swapData(qNode[idx], qNode[Left]);
					idx = Left;
				}
			}
			else {
				if (qNode[idx].data < qNode[Right].data) {
					break;
				}
				else {
					swapData(qNode[idx], qNode[Right]);
					idx = Right;
				}
			}
		}
		else {
			if (qNode[idx].data < qNode[Left].data) {
				break;
			}
			else {
				swapData(qNode[idx], qNode[Left]);
				idx = Left;
			}
		}
		Left = (idx * 2) + 1;
		Right = Left + 1;
	}
	return result;
}

int main() {

	int tc = 0;
	cin >> tc;
	while (tc--) {
		int inputNum = 0;
		cin >> inputNum;

		while (inputNum--) {
			int qData = 0;
			cin >> qData;
			enQueue(qData);

		}
		while (nodeCount) {
			cout << deQueue() << " ";
		} cout << endl;
	}
			
	return 0;
}