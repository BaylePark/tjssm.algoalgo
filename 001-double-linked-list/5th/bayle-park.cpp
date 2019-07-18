#include <stdio.h>

constexpr unsigned int kMaxMemPool = 10000;

template <typename T>
struct Allocator {
	T* alloc() {
		T* ret = &pool[index++];
		ret->init();
		return ret;
	}
	T pool[kMaxMemPool];
	int index = 0;
	void init() {
		index = 0;
	}
};

template <typename T>
struct Node {
	T data;
	Node<T>* prev;
	Node<T>* next;
	void init() {
		prev = NULL;
		next = NULL;
	}
};

template <typename T>
struct List {
	Node<T>* head = 0;
	Node<T>* tail = 0;
	Allocator< Node<T> > allocator;
	int size = 0;

	Node<T>* find(const T&& data) {
		Node<T>* target = head;
		while (target) {
			if (target->data.compare(data)) {
				return target;
			}
			target = target->next;
		}
		return NULL;
	}

	void remove(Node<T>* node) {
		if (node == NULL) return;
		if (node->prev) {
			node->prev->next = node->next;
		}
		if (node->next) {
			node->next->prev = node->prev;
		}
		if (node == head) {
			head = node->next;
		}
		if (node == tail) {
			tail = node->prev;
		}
		size--;
	}

	Node<T>* insert(Node<T>* node, const T&& data) {
		Node<T>* newNode = allocator.alloc();
		newNode->data = data;
		if (node == NULL) {
			head->prev = newNode;
			newNode->next = head;
			head = newNode;
		}
		else {
			if (node->next) {
				node->next->prev = newNode;
			}
			newNode->next = node->next;
			node->next = newNode;
			newNode->prev = node;
		}
		size++;
		return newNode;
	}

	Node<T>* push(const T&& data) {
		Node<T>* newNode = allocator.alloc();
		newNode->data = data;
		if (head == NULL) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
		size++;
		return newNode;
	}

	void print() {
		Node<T>* target = head;
		while (target) {
			target->data.print();
			printf(", ");
			target = target->next;
		}
		printf("\n");
	}

	void reversalPrint() {
		Node<T>* target = tail;
		while (target) {
			target->data.print();
			printf(", ");
			target = target->prev;
		}
		printf("\n");
	}

	Node<T>* TEMP[kMaxMemPool];
	void merge(Node<T>* nodeList[], int L, int M, int R) {
		int l = L;
		int r = M;
		int k = L;
		while (l < M && r <= R) {
			if (nodeList[l]->data.compare_asc(nodeList[r]->data)) {
				TEMP[k++] = nodeList[l++];
			}
			else {
				TEMP[k++] = nodeList[r++];
			}
		}
		while (l < M) {
			TEMP[k++] = nodeList[l++];
		}
		while (r <= R) {
			TEMP[k++] = nodeList[r++];
		}
		for (int i = L; i <= R; i++) {
			nodeList[i] = TEMP[i];
		}
	}
	void mergeSort(Node<T>* nodeList[], int l, int r) {
		if (l == r) return;
		int m = l + (r - l) / 2;
		mergeSort(nodeList, l, m);
		mergeSort(nodeList, m + 1, r);
		merge(nodeList, l, m + 1, r);
	}

	void sort() {
		Node<T>* nodeList[kMaxMemPool] = { 0 };
		int idx = 0;
		Node<T>* target = head;
		while (target) {
			nodeList[idx++] = target;
			target = target->next;
		}
		mergeSort(nodeList, 0, size - 1);

		for (int i = 0; i < size; i++) {
			if (i == 0) {
				head = nodeList[i];
				nodeList[i]->prev = NULL;
				nodeList[i]->next = nodeList[i + 1];
			}
			else if (i == size - 1) {
				tail = nodeList[i];
				nodeList[i]->next = NULL;
				nodeList[i]->prev = nodeList[i - 1];
			}
			else {
				nodeList[i]->next = nodeList[i + 1];
				nodeList[i]->prev = nodeList[i - 1];
			}
		}
	}
};

struct Point {
	int x = 0, y = 0;
	Point() {}
	Point(int x, int y) : x(x), y(y) {}
	bool compare(const Point& p) {
		return x == p.x && y == p.y;
	}
	bool compare_asc(const Point& p) {
		return x < p.x || (x == p.x && y < p.y);
	}
	void print() {
		printf("(%d, %d)", x, y);
	}
};

int main() {
	List<Point> list;

	printf("push 1, 1\n");
	auto* node1 = list.push(Point(1, 1));
	list.print();
	list.reversalPrint();

	printf("push 1, 2\n");
	auto* node2 = list.push(Point(1, 2));
	list.print();
	list.reversalPrint();

	printf("push 2, 2\n");
	auto* node3 = list.push(Point(2, 2));
	list.print();
	list.reversalPrint();

	printf("find 1, 2 and change 9, 9\n");
	auto* foundNode = list.find(Point(1, 2));
	foundNode->data.x = 9;
	foundNode->data.y = 9;

	auto* foundNode2 = list.find(Point(9, 9));
	list.print();
	list.reversalPrint();

	printf("insert 4, 1 after 9, 9\n");
	auto* node4 = list.insert(node2, Point(4, 1));
	list.print();
	list.reversalPrint();

	printf("sort\n");
	list.sort();
	list.print();
	list.reversalPrint();

	printf("remove 1, 1\n");
	list.remove(node1);
	list.print();
	list.reversalPrint();

	printf("remove 2, 2\n");
	list.remove(node3);
	list.print();
	list.reversalPrint();

	printf("remove 4, 1\n");
	list.remove(node4);
	list.print();
	list.reversalPrint();

	printf("remove 9, 9\n");
	list.remove(foundNode2);
	list.print();
	list.reversalPrint();

	return 0;
}