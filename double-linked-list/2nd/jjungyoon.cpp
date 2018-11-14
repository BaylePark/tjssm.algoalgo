#include <iostream>
using namespace std;

#define MAX_NODE 1000

struct Node {
	int x, y;
	Node* prev;
	Node* next;
};

class List {
private:
	int idx;
	Node node[MAX_NODE];
	Node* head;
	Node* tail;
	Node* getNode(int x, int y) {
		node[idx].x = x;
		node[idx].y = y;
		node[idx].next = NULL;
		node[idx].prev = NULL;
		return &node[idx++];
	}
public:
	List() {
		idx = 0;
		head = NULL;
		tail = NULL;
	}
	void pushNode(int x, int y);
	void insertNode(Node* target, int x, int y);
	Node* findNode(int x, int y);
	void remove(Node* node);
	void print();
	void printNode(Node* node);
	void printReverse();
};

int main() {
	List list;
	list.pushNode(1, 1);
	list.print();
	list.printReverse();
	list.pushNode(1, 2);
	list.print();
	list.printReverse();
	list.pushNode(2, 2);
	Node* foundNode = list.findNode(1, 2);
	list.printNode(foundNode);
	foundNode->x = 9;
	foundNode->y = 9;
	list.printNode(list.findNode(9, 9));
	list.print();
	list.printReverse();
	list.insertNode(foundNode, 4, 1);
	list.print();
	list.printReverse();
	list.remove(list.findNode(2, 2));
	list.print();
	list.printReverse();
	return 0;
}


void List::pushNode(int x, int y) {
	Node* node = getNode(x, y);
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

void List::insertNode(Node* target, int x, int y) {
	Node* node = getNode(x, y);
	if (target == tail) {
		node = tail->next;
		node->prev = tail;
		tail = node;
	}
	else {
		target->next->prev = node;
		node->next = target->next;
		node->prev = target;
		target->next = node;
	}
}

Node* List::findNode(int x, int y) {
	Node* find = head;
	for (int i = 0; i < idx; i++) {
		if (find->x == x && find->y == y) {
			return find;
		}
		find = find->next;
	}
	return NULL;
}

void List::remove(Node* node) {
	idx--;
	if (idx < 0) return;
	if (node == tail) {
		tail = node->prev;
		tail->next = NULL;
	}
	else if (node == head) {
		head = node->next;
		head->prev = NULL;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
}

void List::print() {
	Node* print = head;
	while (print != NULL) {
		printf("(%d, %d)", print->x, print->y);
		print = print->next;
	}
	printf("\n");
}

void List::printNode(Node* node) {
	if (node == NULL) return;
	printf("(%d,%d)\n", node->x, node->y);

}

void List::printReverse() {
	Node* print = tail;
	while (print != NULL) {
		printf("(%d, %d) ", print->x, print->y);
		print = print->prev;
	}
	printf("\n");
}


//(1, 1)
//(1, 1)
//(1, 1)(1, 2)
//(1, 2) (1, 1)
//(1, 2)
//(9, 9)
//(1, 1)(9, 9)(2, 2)
//(2, 2) (9, 9) (1, 1)
//(1, 1)(9, 9)(4, 1)(2, 2)
//(2, 2) (4, 1) (9, 9) (1, 1)
//(1, 1)(9, 9)(4, 1)
//(4, 1) (9, 9) (1, 1)