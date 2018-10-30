#include <iostream>
using namespace std;

struct Node {
	int x;
	int y;
	Node* next;
	Node* prev;
};

class List {
private:
	int nodeCnt;
	Node* head;
	Node* tail;
public:
	List() {
		head = NULL;
		tail = NULL;
	}
	void insertNode(int x, int y,int idx);
	void push(int x, int y);
	Node* findNode(int x, int y);
	void removeNode(int x, int y);
	void printNode();
};



int main()
{
	List* list = new List;
	list->push(1, 1);
	list->push(2, 2);
	list->push(3, 3);
	list->insertNode(5, 5, 3);
	list->removeNode(2, 2);
	list->printNode();
	return 0;
}

void List::insertNode(int x, int y,int idx) {
	if (nodeCnt <=idx) {
		printf("노드 갯수보다 큰 idx 삽입 불가\n");
	}
	nodeCnt++;
	Node* tmp = head;
	Node* node = new Node;
	node->next = NULL;
	node->prev = NULL;
	node->x = x;
	node->y = y;
	for (int i = 0; i < idx; i++) {
		tmp = tmp->next;
	}

	tmp->prev->next = node;
	node->prev = tmp->prev;
	node->next = tmp;
	tmp->prev = node;

}

void List::push(int x, int y) {
	nodeCnt++;
	Node* node = new Node;
	node->next = NULL;
	node->prev = NULL;
	node->x = x;
	node->y = y;
	if (head == NULL) {
		head = node;
		tail = node;
	}
	else {
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
}

Node* List::findNode(int x, int y) {
	Node* node = head;
	for (int i = 0; i < nodeCnt; i++) {
		if (node->x == x && node->y == y) {
			return node;
		}
		node = node->next;
	}
	return NULL;
}

void List::removeNode(int x, int y) {
	nodeCnt--;
	Node* node = findNode(x, y);
	if (node == head) {
		node->next->prev = NULL;
		head = node->next;
	}
	else if (node == tail) {
		node->prev->next = NULL;
		tail = node->prev;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	delete node;
	node = NULL;
}

void List::printNode() {
	Node* node = head;
	for (int i = 0; i < nodeCnt; i++) {
		printf("%d 번째 노드 x : %d, y : %d\n", i, node->x, node->y);
		node = node->next;
	}
}