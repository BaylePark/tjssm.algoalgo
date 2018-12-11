#include <iostream>
using namespace std;

#define MAX_NODE 100

struct Node {
	int priority;
};

Node PQ[MAX_NODE];
int nodeCnt;

void init() {
	for (int i = 0; i < MAX_NODE; i++) {
		PQ[i].priority = -1;
	}
}

void enqueue(int data) {
	PQ[nodeCnt].priority = data;
	int idx = nodeCnt;
	nodeCnt++;
	while (idx != 0) {
		int parent = (idx - 1) / 2;
		if (PQ[parent].priority < PQ[idx].priority) {
			break;
		}
		int tmp = PQ[parent].priority;
		PQ[parent].priority = data;
		PQ[idx].priority = tmp;
		idx = parent;
	}
}

int dequeue() {
	int result = PQ[0].priority;
	PQ[0].priority = PQ[nodeCnt - 1].priority;
	PQ[nodeCnt - 1].priority = -1;
	int idx = 0;
	nodeCnt--;
	int next = 2 * idx + 1;
	while (next<nodeCnt) {
		if (PQ[next].priority > PQ[idx].priority && PQ[next + 1].priority > PQ[idx].priority) {
			break;
		}
		if (PQ[next].priority < PQ[next + 1].priority || PQ[next+1].priority == -1) {
			if (PQ[next].priority < PQ[idx].priority) {
				int tmp = PQ[next].priority;
				PQ[next].priority = PQ[idx].priority;
				PQ[idx].priority = tmp;
				idx = next;
			}
			else if (PQ[next + 1].priority < PQ[idx].priority) {
				int tmp = PQ[next + 1].priority;
				PQ[next + 1].priority = PQ[idx].priority;
				PQ[idx].priority = tmp;
				idx = next + 1;
			}
		}
		else {
			if (PQ[next+1].priority < PQ[idx].priority) {
				int tmp = PQ[next + 1].priority;
				PQ[next + 1].priority = PQ[idx].priority;
				PQ[idx].priority = tmp;
				idx = next + 1;

			}
			else if (PQ[next].priority < PQ[idx].priority) {
				int tmp = PQ[next].priority;
				PQ[next].priority = PQ[idx].priority;
				PQ[idx].priority = tmp;
				idx = next;
			}
		}

		next = 2 * idx + 1;
		
	}


	return result;
}

int main()
{
	int tc = 0;
	cin >> tc;
	for (int i = 0; i < tc; i++) {
		int qCnt = 0;
		cin >> qCnt;
		init();
		for (int j = 0; j < qCnt; j++) {
			int tmp = 0;
			cin >> tmp; 
			enqueue(tmp);


		}
		for (int ff = 0; ff < qCnt; ff++) {
			cout << dequeue() << "  ";
		}
		cout << endl;
	}
	return 0;
}