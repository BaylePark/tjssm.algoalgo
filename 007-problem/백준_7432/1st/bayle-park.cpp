#include <cstdio>
#include <cstring>

using namespace std;

const unsigned int MAX_DIR_LEN = 8;
const unsigned int MAX_PATH_LEN = 80;

template <typename T>
struct BinarySearchTree {
	struct Node {
		T data;
		Node *left, *right;
		void init() {
			left = right = NULL;
		}
	};

	typedef int(*cmpfn)(T& v1, T& v2);

	Node *root;
	cmpfn cmpfn_ptr;

	BinarySearchTree(cmpfn cmpfn_ptr) : root(NULL), cmpfn_ptr(cmpfn_ptr) { }

	Node* find(T& data) {
		Node *target = root;
		while (target) {
			int val = cmpfn_ptr(data, target->data);
			if (val == 0) break;
			else if (val < 0) target = target->left;
			else target = target->right;
		}
		return target;
	}

	Node* insert(T& data) {
		Node* newNode = new Node();
		newNode->data = data;

		Node **target = &root;
		while (*target) {
			int cmp = cmpfn_ptr(newNode->data, (*target)->data);
			if (cmp < 0) {
				target = &((*target)->left);
			}
			else if (cmp > 0) {
				target = &((*target)->right);
			}
			else {
				//cout << "STRANGE" << endl;
			}
		}
		*target = newNode;
		return newNode;
	}
};

struct Path {
	BinarySearchTree<Path> children;
	char name[MAX_DIR_LEN + 1];

	static int compare(Path& v1, Path& v2) {
		return std::strcmp(v1.name, v2.name);
	}

	Path() : children(compare) {
	}
	Path(const char* dirname) : children(compare) {
		std::strcpy(name, dirname);
	}
	Path(const Path &path) : children(compare) {
		std::strcpy(name, path.name);
	}
	void recursive_bst(BinarySearchTree<Path>::Node* node, const int depth) {
		if (node == NULL) return;
		recursive_bst(node->left, depth);
		for (int i = 0; i < depth; i++) {
			putchar(0x20);
		}
		printf("%s\n", node->data.name);
		if (node->data.children.root) {
			node->data.print(depth + 1);
		}
		recursive_bst(node->right, depth);
	}

	void print(int depth) {
		recursive_bst(children.root, depth);
	}
};

Path root;

int main() {
	int N;
	scanf("%d", &N);
	while (N--) {
		char path[MAX_PATH_LEN + 1];
		scanf("%s", path);
		char *c = path;
		int pathNameSize = 0;
		char pathNameBuf[MAX_DIR_LEN + 1] = { 0 };
		Path *currentPath = &root;
		while (1) {
			if (*c == '\\' || *c == 0) {
				pathNameBuf[pathNameSize++] = 0;
				Path p(pathNameBuf);
				BinarySearchTree<Path>::Node *node = currentPath->children.find(p);
				if (node == NULL) {
					//cout << "Insert : " << pathNameBuf << endl;
					BinarySearchTree<Path>::Node *newNode = currentPath->children.insert(p);
					currentPath = &(newNode->data);
				}
				else {
					//cout << "Exist : " << pathNameBuf << endl;
					currentPath = &(node->data);
				}
				if (*c == 0) break;
				pathNameSize = 0;
				c++;
				continue;
			}
			pathNameBuf[pathNameSize++] = *c;
			c++;
		}
	}

	root.print(0);

	return 0;
}