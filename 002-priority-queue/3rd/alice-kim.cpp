// 40 min + a
#include <iostream>
using namespace std;
#define MAX_NODE 100

struct Node {
	char data[12];
	int priority;
	bool isDisabled;
};

int idx;
Node PQ[MAX_NODE];

void swap(Node* node1, Node* node2);
void enqueue(char data[12], int priority);
Node* dequeue();
void deleteNode(int idx);
void arrange(int idx);

int main() {

	int tc = 0;
	cin >> tc;
	while (tc--) {
		int inputNum = 0;
		cin >> inputNum;

		while (inputNum--) {
			char cData[12];
			int qData = 0;
			cin >> cData >> qData;
			enqueue(cData, qData);

		}
		// 그냥 다 출력
		//1 8 10 13 17 38 49 55 56 92                                                                                            
		//1 4 5 7 13 14 21 22 22 35 50 99 100   
		//while (idx) {
		//	cout << dequeue()->priority<< " ";
		//} cout << endl;

		// 3번째 노드 지우고 출력 

		deleteNode(3);
		while (idx) {
			Node* result = dequeue();
			if (!result->isDisabled) {
				cout << result->priority << " ";
			}
		} cout << endl;
	}

}

void enqueue(char data[12], int priority) {
	strcpy(PQ[idx].data, data);
	PQ[idx].priority = priority;
	int child = idx;
	int parent = (child - 1) / 2;;
	while (parent>=0) {
		if (PQ[parent].priority > PQ[child].priority) {
			swap(PQ[parent], PQ[child]);
		}
		else {
			break;
		}
		child = parent;
		parent = (parent - 1) / 2;
	}
	idx++;
}

void swap(Node* node1, Node* node2) {
	char cTemp[12];
	int iTemp;
	strcpy(cTemp, node1->data);
	strcpy(node1->data, node2->data);
	strcpy(node2->data,cTemp);
	iTemp = node1->priority;
	node1->priority = node2->priority;
	node2->priority = iTemp;
}

Node* dequeue() 
{
	Node result = PQ[0];
	swap(PQ[--idx], PQ[0]);
	arrange(0);

	return &result;
}

void arrange(int start) {
	int leftIdx = (start * 2) + 1;
	int rightIdx = leftIdx + 1;
	if (leftIdx >= idx) return;

	int minIdx = leftIdx;
	if (rightIdx < idx) {
		minIdx = PQ[rightIdx].priority > PQ[leftIdx].priority ? leftIdx : rightIdx;
	}
	if (PQ[start].priority > PQ[minIdx].priority) {
		swap(PQ[start], PQ[minIdx]);
		arrange(minIdx);
	}
	return;
}

void deleteNode(int idx) {
	PQ[idx].isDisabled = true;
}