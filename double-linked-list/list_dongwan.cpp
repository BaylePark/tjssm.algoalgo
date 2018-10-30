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
	Head = (Node*)malloc(sizeof(Node));
	Head->point = NULL;
	Head->prevNode = NULL;
	Head->nextNode = NULL;
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

void insertPoint(int xPos, int yPos) {
	Point *point = createPoint(xPos, yPos);
	if (Head->nextNode == NULL) {
		Head->nextNode->point = point;
	}
	else {
		Node* cur = Head;
		while (cur->nextNode != NULL) {
			cur = cur->nextNode;
		}
		cur->nextNode = createNode();
		cur->nextNode->prevNode = cur;
		cur->nextNode->point = point;
	}
}

void printAll() {
	Node* cur = Head->nextNode;
	while (cur != NULL) {
		cout << cur->point->xPos << ","<<cur->point->yPos << "  ";
		cur = cur->nextNode;
	}
	cout << endl;
}

int main() {
	initList();
	insertPoint(1, 2);
	insertPoint(2, 3);
	insertPoint(3, 4);
	printAll();
	return 0;
}

