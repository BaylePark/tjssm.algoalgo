#include <iostream>
using namespace std;

typedef struct tagPoint {
	int x;
	int y;
}Point;

typedef struct tagNode {
	Point point;
	tagNode* prevNode;
	tagNode* nextNode;
}Node;

Node* Head;
Node* Tail;

Point getPoint(int x, int y) {
	Point point;
	point.x = x;
	point.y = y;
	return point;
}

Node* getNode(Point p) {
	if (Head == NULL)
		return NULL;
	Node* cur = Head;
	while (cur) {
		if (cur->point.x == p.x && cur->point.y == p.y) {
			return cur;
		}
		cur = cur->nextNode;
	}
	return NULL;
}

Node* createNode(Point p) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->point = p;
	newNode->nextNode = NULL;
	newNode->prevNode = NULL;
	return newNode;
}

void insertNode(Point p) {
	Node* newNode = createNode(p);
	if (Head == NULL) {
		Head = newNode;
		Tail = Head;
	}
	else {
		Node* cur = Tail;
		cur->nextNode = newNode;
		newNode->prevNode = cur;
		Tail = newNode;
	}
}

void insertNode(Point target, Point p) {
	Node* targetNode = getNode(target);
	if (targetNode == NULL) {
		cout << "insertNode : No target value" << endl;
		return;
	}
	Node* newNode = createNode(p);
	Node* nextNode = targetNode->nextNode;

	targetNode->nextNode = newNode;
	newNode->prevNode = targetNode;
	if (nextNode != NULL) {
		newNode->nextNode = nextNode;
		nextNode->prevNode = newNode;
	}
	if (targetNode == Tail)
		Tail = newNode;
}

void removeNode(Point target) {
	Node* targetNode = getNode(target);
	if (targetNode == NULL) {
		cout << "removeNode : No delete value" << endl;
		return;
	}

	Node* delNode = NULL;
	delNode = targetNode;
	if (targetNode == Head) {
		if (Head->nextNode == NULL) {
			Head = NULL;
			Tail = NULL;
		}
		else {
			Head = Head->nextNode;
			Head->prevNode = NULL;
		}
	}
	else if (targetNode == Tail) {
		Tail = Tail->prevNode;
		Tail->nextNode = NULL;
	}
	else {
		Node* nextNode = targetNode->nextNode;
		Node* prevNode = targetNode->prevNode;
		prevNode->nextNode = nextNode;
		nextNode->prevNode = prevNode;
	}
	free(delNode);
}

void normalPrint() {
	Node* cur = Head;
	if (cur == NULL) {
		cout << "normalPrintAll \t empty" << endl;
	}
	else {
		cout << "normalPrintAll \t => ";
		while (cur->nextNode) {
			cout << "(" << cur->point.x << "," << cur->point.y << "), ";
			cur = cur->nextNode;
		}
		cout << "(" << cur->point.x << "," << cur->point.y << ")" << endl;
	}
}

void reversalPrint() {
	Node* cur = Tail;
	if (cur == NULL) {
		cout << "reversalPrint \t empty" << endl;
	}
	else {
		cout << "reversalPrint \t => ";
		while (cur->prevNode) {
			cout << "(" << cur->point.x << "," << cur->point.y << "), ";
			cur = cur->prevNode;
		}
		cout << "(" << cur->point.x << "," << cur->point.y << ")" << endl;
	}
}

int main() {
	cout << "Input : (1,1), (1,2), (1,3), (2,1), (2,2), (2,3)" << endl;
	for (int i = 1; i < 3; i++) {
		for (int j = 1; j < 4; j++) {
			insertNode(getPoint(i, j));
		}
	}
	normalPrint();
	reversalPrint();

	cout << endl << "Input : (1,1) -> (5,1)" << endl;
	insertNode(getPoint(1, 1), getPoint(5, 1));
	normalPrint();

	cout << endl << "Input : (2,3) -> (6,1)" << endl;
	insertNode(getPoint(2, 3), getPoint(6, 1));
	normalPrint();

	cout << endl << "Input : (5,5) -> (6,2)" << endl;
	insertNode(getPoint(5, 5), getPoint(6, 2));
	normalPrint();

	cout << endl << "removeNode : (1,1), (1,2), (1,3), (2,1), (2,2), (2,3)" << endl;
	for (int i = 1; i < 3; i++) {
		for (int j = 1; j < 4; j++) {
			removeNode(getPoint(i, j));
		}
	}
	normalPrint();
	reversalPrint();

	cout << endl << "removeNode : (5,1)" << endl;
	removeNode(getPoint(5, 1));
	normalPrint();

	cout << endl << "removeNode : (5,1)" << endl;
	removeNode(getPoint(5, 1));
	normalPrint();

	cout << endl << "removeNode : (6,1)" << endl;
	removeNode(getPoint(6, 1));
	normalPrint();

	cout << endl << "removeNode : (6,1)" << endl;
	removeNode(getPoint(6, 1));
	normalPrint();

	cout << endl << "Input : (1,1), (1,2), (1,3), (2,1), (2,2), (2,3)" << endl;
	for (int i = 1; i < 3; i++) {
		for (int j = 1; j < 4; j++) {
			insertNode(getPoint(i, j));
		}
	}
	normalPrint();
	reversalPrint();
}