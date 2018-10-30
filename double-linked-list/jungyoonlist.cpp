#include <iostream>
using namespace std;

template <typename T>
struct Node {
	T data;
	Node* next;
	Node* prev;
};

template <typename T>
class List {
private:
	int nodeCnt;
	Node<T>* head;
	Node<T>* tail;
public:
	List() {
		head = NULL;
		tail = NULL;
	}
	void insertNode(T data,int idx);
	void push(T data);
	Node<T>* findNode(T data);
	void removeNode(T data);
};


struct Point_2D {
	int x;
	int y;
};



int main()
{
	List<Point_2D>* list = new List<Point_2D>;
	Point_2D first;
	first.x = first.y = 1;
	
	Point_2D second;
	second.x = second.y = 2;

	Point_2D third;
	third.x = third.y = 5;

	Point_2D ten;
	ten.x = ten.y = 10;

	list->push(first);
	list->push(second);
	list->push(third);
	list->insertNode(ten, 1);
	list->removeNode(third);
	//list->printNode();
	return 0;
}

template <typename T>
void List<T>::insertNode(T data,int idx) {
	idx--;
	if (nodeCnt <=idx) {
		printf("노드 갯수보다 큰 idx 삽입 불가\n");
	}
	nodeCnt++;
	Node<T>* tmp = head;
	Node<T>* node = new Node<T>;
	node->next = NULL;
	node->prev = NULL;
	node->data = data;
	for (int i = 0; i < idx; i++) {
		tmp = tmp->next;
	}

	if (tmp == head) {
		node->next = tmp;
		tmp->prev = node;
		head = node;
	}
	else {
		tmp->prev->next = node;
		node->prev = tmp->prev;
		node->next = tmp;
		tmp->prev = node;
	}
}


template <typename T>
void List<T>::push(T data) {
	nodeCnt++;
	Node<T>* node = new Node<T>;
	node->next = NULL;
	node->prev = NULL;
	node->data = data;
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

template <typename T>
Node<T>* List<T>::findNode(T data) {
	Node<T>* node = head;
	for (int i = 0; i < nodeCnt; i++) {
		//if (node->data == data) {
		//	return node;
		//}
		node = node->next;
	}
	return NULL;
}

template <typename T>
void List<T>::removeNode(T data) {
	nodeCnt--;
	Node<T>* node = findNode(data);
	if (node == head) {
		if (node->next) {
			node->next->prev = NULL;
		}
		head = node->next;
	}
	else if (node == tail) {
		if (node->prev) {
			node->prev->next = NULL;
		}
		tail = node->prev;
	}
	else {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	delete node;
	node = NULL;
}






//void List::printNode() {
//	Node* node = head;
//	for (int i = 0; i < nodeCnt; i++) {
//		printf("%d 번째 노드 x : %d, y : %d\n", i, node->x, node->y);
//		node = node->next;
//	}
//}