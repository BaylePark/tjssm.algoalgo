#include <iostream>
using namespace std;

#define MAX_NODE 1000


struct Node {
	Node* prev;
	Node* next;
	int x;
	int y;
};

class list {
private:
	Node* head;
	Node* tail;
	int nodeIdx;
	int cnt;
	Node listNode[MAX_NODE];
public:
	list() {
		head = 0;
		tail = 0;
		nodeIdx = 0;
	}
	Node* getNode() {
		listNode[nodeIdx].next = 0;
		listNode[nodeIdx].prev = 0;
		return &listNode[nodeIdx++];
	}
	void pushNode(int x,int y);
	void insertNode(Node* node, int x, int y);
	void removeNode(Node* node);
	Node* findNode(int x, int y);
	void printNode();
	void printNode(Node* node);
	void reversePrint();
};

int main()
{
	list ll;
	ll.pushNode(1, 1);
	ll.printNode();
	ll.reversePrint();

	ll.pushNode(1, 2);
	ll.printNode();
	ll.reversePrint();

	ll.pushNode(2,2);
	ll.printNode();
	ll.reversePrint();
	Node* find = ll.findNode(1, 2);
	ll.printNode(find);
	find->x = 9;
	find->y = 9;
	find = ll.findNode(9, 9);
	ll.printNode();
	ll.reversePrint();

	ll.insertNode(ll.findNode(9,9), 4, 1);
	ll.printNode();
	ll.reversePrint();
	
	ll.removeNode(ll.findNode(1, 1));
	ll.printNode();
	ll.reversePrint();
	ll.removeNode(ll.findNode(2,2));
	ll.printNode();
	ll.reversePrint();
	ll.removeNode(ll.findNode(4,1));
	ll.printNode();
	ll.reversePrint();
	ll.removeNode(ll.findNode(9,9));
	ll.printNode();
	ll.reversePrint();

	
	
	return 0;
}

void list::pushNode(int x,int y) {
	Node* node = getNode();
	node->x = x;
	node->y = y;

	if (head == 0) {
		head = node;
		tail = node;
	}
	else {
		tail->next = node;
		node->prev = tail;
		tail = node;
	}
}

void list::insertNode(Node* node, int x, int y) {
	Node* temp = getNode();
	temp->x = x;
	temp->y = y;

	if (node== tail) {
		node->next = temp;
		temp->prev = node;
		tail = node;
	}
	else {
		node->next->prev = temp;
		temp->next = node->next;
		node->next = temp;
		temp->prev = node;
	}
}

void list::removeNode(Node* node) {
	cnt--;
	if (node == head && node == tail) {
		head = 0;
		tail = 0;
	}
	else if (node == head) {
		node->next->prev = 0;
		head = node->next;
	}
	else if (node == tail) {
		node->prev->next = 0;
		tail = node->prev;
	} else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}
}

Node* list::findNode(int x, int y) {
	for (Node* temp = head; temp != 0; temp = temp->next) {
		if (temp->x == x && temp->y == y) {
			return temp;
		}
	}
	return 0;
}

void list::printNode() {
	for (Node* temp = head; temp != 0; temp = temp->next) {
		cout << "(" << temp->x << " , " << temp->y << ") ";
	}cout << endl;
}

void list::printNode(Node* node) {
	cout << "(" <<node->x << " , " << node->y << ") " <<endl;
}

void list::reversePrint() {
	for (Node* temp = tail; temp != 0; temp = temp->prev) {
		cout<< "(" << temp->x << " , " << temp->y << ") ";
	}cout << endl;
}