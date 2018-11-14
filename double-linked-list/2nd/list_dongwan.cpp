#include <iostream>
using namespace std;

typedef struct tagPoint {
	int x;
	int y;
}Point;

typedef struct tagNode {
	Point p;
	tagNode *prevNode;
	tagNode *nextNode;
}Node;

Node *Head = NULL;
Node *Tail = NULL;

Node* createNode(int x, int y) {
	Node *newNode = (Node*)malloc(sizeof(Node));
	newNode->nextNode = NULL;
	newNode->prevNode = NULL;
	newNode->p.x = x;
	newNode->p.y = y;
	return newNode;
}

void insert(int x, int y) {
	Node *newNode = createNode(x, y);
	if (Head == NULL) {
		Head = newNode;
		Tail = Head;
	}
	else {
		Node* cur = Head;
		cur->nextNode = newNode;
		newNode->prevNode = cur;
		if (Head == Tail) {
			Tail = cur;
		}
	}
}

void lastInsert(int x, int y) {
	if (Tail == NULL) {
		insert(x, y);
	}
	else {
		Node *newNode = createNode(x, y);
		Tail->nextNode = newNode;
		newNode->prevNode = Tail;
		Tail = newNode;
	}
}

void removed(int x, int y) {
	Node* cur = Head;
	while (cur) {
		if (cur->p.x == x && cur->p.y == y) {
			cout << "Removed x:" << x << " y:" << y << endl;
			if (Head == cur) {
				Head = NULL;
				Tail = NULL;
				free(cur);
				return;
			}

			Node* prevNode = cur->prevNode;
			Node* nextNode = cur->nextNode;
			if (prevNode) {
				prevNode->nextNode = nextNode;
			}
			if (nextNode) {
				nextNode->prevNode = prevNode;
			}
			if (Tail == cur) {
				Tail = cur->prevNode;
			}
			free(cur);
			cur = NULL;
			return;
		}
		cur = cur->nextNode;
	}
}

void Print() {
	Node* cur = Head;
	while (cur) {
		cout << cur->p.x << "," << cur->p.y << " => ";
		cur = cur->nextNode;
	}
	cout << endl;
}

void ReversalPrint() {
	Node* cur = Tail;
	while (cur) {
		cout << cur->p.x << "," << cur->p.y << " => ";
		cur = cur->prevNode;
	}
	cout << endl;
}


int main() {
	insert(1, 1);
	Print();
	ReversalPrint();
	insert(1, 2);
	Print();
	ReversalPrint();
	return 0;
}