#include <iostream>
using namespace std;

#define MAX_NODE 10000
struct Node {
	int x;
	int y;
	Node* prev;
	Node* next;
};

class DDL {
public:
	Node* Find(int x, int y);
	void Remove(Node* n);
	Node* Insert(Node* n, int x, int y);
	Node* Push(int x, int y);
	void Swap(Node* n1, Node* n2);
	void Print();
	void PrintNode(Node* n);
	void ReversalPrint();
	void Sort();
private: 
	Node* getNode(int x, int y) {
		Node* tmp = &node[idx++];
		tmp->x = x;
		tmp->y = y;
		tmp->prev = NULL;
		tmp->next = NULL;
		return tmp;
	}
	Node* head;
	Node* tail;
	Node node[MAX_NODE];
	int idx=0;
};

int main() {

	DDL ddl;
	Node* Node1 = ddl.Push(1, 1);
	ddl.Print();
	ddl.ReversalPrint();
	Node* Node2 = ddl.Push(1, 2);
	ddl.Print();
	ddl.ReversalPrint();
	Node* Node3 = ddl.Push(2, 2);
	ddl.Print();
	ddl.ReversalPrint();
	Node* FoundNode2 = ddl.Find(1, 2);
	ddl.PrintNode(FoundNode2);
	FoundNode2->x = 9;
	FoundNode2->y = 9;
	FoundNode2 = ddl.Find(9, 9);
	ddl.PrintNode(FoundNode2);
	ddl.Print();
	ddl.ReversalPrint();
	Node* Node4 = ddl.Insert(Node2, 4, 1);
	ddl.Print();
	ddl.ReversalPrint();
	cout << "sort " << endl;
	ddl.Sort();
	ddl.Print();
	ddl.ReversalPrint();
	ddl.Remove(Node1);
	ddl.Print();
	ddl.ReversalPrint();
	ddl.Remove(Node3);
	ddl.Print();
	ddl.ReversalPrint();
	ddl.Remove(Node4);
	ddl.Print();
	ddl.ReversalPrint();
	ddl.Remove(FoundNode2);
	ddl.Print();
	ddl.ReversalPrint();

	return 0;
}

Node* DDL::Push(int x, int y) {
	Node* tmp = getNode(x,y);
	if (tail == NULL) {
		head = tmp;
		tail = tmp;
	}
	else {
		tmp->prev = tail;
		tail->next = tmp;
		tail = tmp;
	}
	return tmp;
}

Node* DDL::Insert(Node* n, int x, int y) {
	Node* tmp = getNode(x, y);
	if (n == tail) {
		tmp->prev = tail;
		tail->next = tmp;
		tail = tmp;
	}
	else {
		tmp->next = n->next;
		n->next->prev = tmp;
		n->next = tmp;
		tmp->prev = n;
	}
	return tmp;
}

void DDL::Remove(Node* n) {
	idx--;
	if (n == tail && n == head) {
		head = NULL;
		tail = NULL;
	}
	else if (n == tail) {
		n->prev->next = NULL;
		tail = n->prev;
	}
	else if (n == head) {
		n->next->prev = NULL;
		head = n->next;
	}
	else {
		n->prev->next = n->next;
		n->next->prev = n->prev;
	}
}

Node* DDL::Find(int x, int y) {
	Node* tmp = head;
	while (tmp) {
		if (tmp->x == x && tmp->y == y) {
			return tmp;
		}
		tmp = tmp->next;
	}
}

void DDL::Print() {
	Node* tmp = head;
	while (tmp) {
		cout << "(" << tmp->x << " , " << tmp->y << ")" << " ";
		tmp = tmp->next;
	}
	cout << endl;
}
void DDL::PrintNode(Node* n) {

	cout << "(" << n->x << " , " << n->y << ")" << " " <<endl;
}
void DDL::ReversalPrint() {
	Node* tmp = tail;
	while (tmp) {
		cout << "(" << tmp->x << " , " << tmp->y << ")" << " ";
		tmp = tmp->prev;
	}
	cout << endl;
}

void DDL::Sort() {
	for (int i = 0; i < idx-1; i++) {
		Node* tmp = head;
		for (int j = i+1; j < idx; j++) {
			Node* tmp2 = tmp->next;
			if (tmp->x > tmp2->x) {
				Swap(tmp, tmp2);
			}
			else if (tmp->x == tmp2->x && tmp->y > tmp2->y) {
				Swap(tmp, tmp2);
			}
			else {
				tmp = tmp->next;
			}
		}
	}
}


void DDL::Swap(Node* n1, Node* n2) {
	if (n2 == tail) {
		n1->prev->next = n2;
		n2->prev = n1->prev;
		n2->next = n1;
		n1->prev = n2;
		n1->next = NULL;
		tail = n1;
	}
	else if (n1 == head) {
		n2->next->prev = n1;
		n1->next = n2->next;
		n2->next = n1;
		n2->prev = NULL;
		head = n2;
	}
	else {
		n2->next->prev = n1;
		n1->next = n2->next;
		n1->prev->next = n2;
		n2->prev = n1->prev;
		n1->prev = n2;
		n2->next = n1;
	}
}