#include <iostream>
using namespace std;

struct Node {
	char a;
	Node* next;
	Node* prev;
};


char inputLine[100000];
Node node[800000];
int idx;

int myStrlen(char* input) {
	int idx = 0;
	while (input[idx]) {
		idx++;

	}
	return idx;
}
class List {
private:

	Node* cur;
	Node* head;
	Node* tail;
public:
	List() {
		head = &node[idx++];
		tail = head;
		cur = head;
	}
	void insert(char input);
	void goLeft();
	void goRight();
	void remove();
	void print();

};	
Node* getNode() {
	return &node[idx++];
}
int main() {
	cin >> inputLine;
	List list;
	int length = myStrlen(inputLine);
	for (int i = 0; i < length; i++) {
		list.insert(inputLine[i]);
	}
	int tc = 0;
	cin >> tc;
	for (int i = 0; i < tc; i++) {
		char t;
		cin >> t;
		if (t == 'P') {
			char t2;
			cin >> t2;
			list.insert(t2);
		}
		else if (t == 'L') {
			list.goLeft();
		}
		else if (t == 'D') {
			list.goRight();
		}
		else if (t == 'B') {
			list.remove();
		}

	}
	list.print();
	return 0;
}

void List::insert(char input) {
	Node* newNode = getNode();
	newNode->a = input;
	if (cur == tail) {
		tail->next = newNode;
		newNode->prev = tail;
		tail = newNode;
		cur = newNode;
	}
	else {
		cur->next->prev = newNode;
		newNode->next = cur->next;
		cur->next = newNode;
		newNode->prev = cur;
		cur = newNode;
	}
}

void List::goLeft() {
	if (cur == head) return;
	cur = cur->prev;
}

void List::goRight() {
	if (cur == tail) return;
	cur = cur->next;
}

void List::remove() {
	if (cur == head) return;
	if (cur == tail) {
		tail = cur->prev;
		cur = tail;
	}
	else {
		cur->prev->next = cur->next;
		cur->next->prev = cur->prev;
		cur = cur->prev;
	}
}

void List::print() {
	Node* tmp = head->next;
	while (tmp) {
		cout << tmp->a;
		tmp = tmp->next;
	}cout << endl;
}