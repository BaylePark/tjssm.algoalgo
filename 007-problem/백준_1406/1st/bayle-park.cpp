#include <iostream>

const int MAX_MEMORY = 600000 * 1.5;

template <typename T>
struct Allocator {
	T mempool_[MAX_MEMORY];
	int index_;
	Allocator() : index_(0) {}
	T* alloc() {
		T* ret = &mempool_[index_++];
		ret->init();
		return ret;
	}
};

template <typename T>
struct Node {
	T data_;
	Node *prev_, *next_;
	void init() {
		prev_ = next_ = NULL;
	}
};

template <typename T>
struct List {
	typedef void(*iterator_fn)(T& data);
	
	Node<T> *head_, *tail_;
	Allocator< Node<T> > allocator_;

	List() : head_(NULL), tail_(NULL) {}

	Node<T>* push(const T val) {
		Node<T> *node = allocator_.alloc();
		node->data_ = val;

		if (head_ == NULL) {
			head_ = tail_ = node;
		}
		else {
			tail_->next_ = node;
			node->prev_ = tail_;
			tail_ = node;
		}

		return node;
	}
	Node<T>* insert(Node<T>* node, T val) {
		Node<T> *newnode = allocator_.alloc();
		newnode->data_ = val;
		if (node == NULL) {
			head_->prev_ = newnode;
			newnode->next_ = head_;
			head_ = newnode;
		}
		else {
			newnode->prev_ = node;
			newnode->next_ = node->next_;
			if (node->next_) {
				node->next_->prev_ = newnode;
			}
			node->next_ = newnode;
		}
		return newnode;
	}
	void remove(Node<T> *node) {
		if (node == NULL) return;
		if (node == head_) {
			head_ = node->next_;
			head_->prev_ = NULL;
		}
		else if (node == tail_) {
			tail_ = node->prev_;
			tail_->next_ = NULL;
		}
		else {
			node->prev_->next_ = node->next_;
			node->next_->prev_ = node->prev_;
		}
	}
	void traversal(iterator_fn fn) {
		Node<T>* node = head_;
		while (node) {
			fn(node->data_);
			node = node->next_;
		}
	}
};

List<char> editor_;
char init_str_[100000 + 1];

static void traversal(char& c) {
	if (c == '$') return;
	std::cout << c;
}

int main() {
	std::cin >> init_str_;
	int len = 0;
	Node<char> *cursor = NULL;
	while (init_str_[len]) {
		editor_.push(init_str_[len]);
		len++;
	}
	cursor = editor_.push('$');
	int cmd_count = 0;
	std::cin >> cmd_count;
	for (int i = 0; i < cmd_count; i++) {
		char cmd;
		std::cin >> cmd;
		switch (cmd)
		{
		case 'L': // left
			cursor = cursor->prev_ ? cursor->prev_ : cursor;
			break;
		case 'D': // right
			if (cursor->data_ != '$')
				cursor = cursor->next_ ? cursor->next_ : cursor;
			break;
		case 'B': // remove left
			editor_.remove(cursor->prev_);
			break;
		case 'P': // insert left
			char c;
			std::cin >> c;
			editor_.insert(cursor->prev_, c);
			break;
		}
	}
	editor_.traversal(traversal);

	return 0;
}