#include <iostream>
using namespace std;

typedef struct tagPoint {
	int xPos;
	int yPos;
}Point;

typedef struct tagList {
	Point* point;
	tagList* prevNode;
	tagList* nextNode;
}Node;

Node *Head;

void initList() {
	Head = NULL;
}

Node* createNode() {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->point = NULL;
	newNode->prevNode = NULL;
	newNode->nextNode = NULL;
	return newNode;
}

Point* createPoint(int xPos, int yPos) {
	Point* newPoint = (Point*)malloc(sizeof(Point));
	newPoint->xPos = xPos;
	newPoint->yPos = yPos;
	return newPoint;
}

void destroyPoint(Point * p) {
	free(p);
}

void destroyNode(Node * n) {
	free(n);
}

void insertPoint(int xPos, int yPos) {
	Point *newPoint = createPoint(xPos, yPos);
	if (Head == NULL) {
		Head = createNode();
		Head->point = newPoint;
	}
	else {
		Node* cur = Head;
		cur->nextNode = createNode();
		cur->nextNode->point = newPoint;
		cur->nextNode->prevNode = cur;
		Head = cur->nextNode;
	}
}

Node* findNode(int xPos, int yPos) {
	Node* cur = Head;
	while (cur != NULL) {
		if (cur->point->xPos == xPos && cur->point->yPos)
			return cur;
		cur = cur->prevNode;
	}
	return NULL;
}

void removeNode(int xPos, int yPos) {
	Node* targetNode = findNode(xPos, yPos);
	if (Head == targetNode) {
		if (Head->prevNode != NULL) {
			Head = targetNode->prevNode;
		}
		else {
			Head = NULL;
		}
	}
	else {
		Node* tempPrevNode = targetNode->prevNode;
		Node* tempNextNode = targetNode->nextNode;
		tempPrevNode->nextNode = tempNextNode;
		tempNextNode->prevNode = tempPrevNode;
	}
	destroyPoint(targetNode->point);
	destroyNode(targetNode);
}

void printAll() {
	Node* cur = Head;
	while (cur != NULL) {
		cout << cur->point->xPos << "," << cur->point->yPos << "  ";
		cur = cur->prevNode;
	}
	cout << endl;
}

int main() {
	initList();
	insertPoint(1, 2);
	insertPoint(2, 3);
	insertPoint(3, 4);
	insertPoint(5, 6);
	printAll();
	removeNode(3, 4);
	printAll();
	removeNode(5, 6);
	printAll();
	removeNode(2, 3);
	printAll();
	removeNode(1, 2);
	printAll();
	return 0;
}

