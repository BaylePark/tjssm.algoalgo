#include <iostream>
using namespace std;

#define MAX_TABLE 4096
#define MAX_KEY 64
#define MAX_DATA 128

struct Node {
	char key[MAX_KEY];
	char data[MAX_DATA];
	Node* next;
};

Node hashTable[MAX_TABLE];

unsigned long hashFunc(const char *str);
int add(const char* key, char* data);
int deleteNode(const char* key, char* data);
void printNode(const char* key);

int main()
{
	int tc = 0;
	cin >> tc;
	while (tc--) {
		char key[MAX_KEY];
		char data[MAX_DATA];

		cin >> key >> data;
		add(key, data);
	}
	printNode("JAVA");
	deleteNode("JAVA", "OpenJDK");
	printNode("JAVA");
	return 0;
}


unsigned long hashFunc(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

int add(const char* key, char* data)
{
	unsigned long val = hashFunc(key);

	if (hashTable[val].key[0] != 0) {
		if (strcmp(hashTable[val].data, data) == 0) return 0;
		Node* current = &hashTable[val];
		while (current->next) {
			current = current->next;
		}
		Node* newNode = (Node*)malloc(sizeof(Node));
		strcpy(newNode->key, key);
		strcpy(newNode->data, data);
		newNode->next = 0;
		current->next = newNode;
	}
	else {
		strcpy(hashTable[val].key, key);
		strcpy(hashTable[val].data, data);
	}
	return 1;
}

int deleteNode(const char* key, char* data)
{
	unsigned long val = hashFunc(key);
	if (hashTable[val].key[0] != 0) {
		Node* current = &hashTable[val];
		Node* prev = 0;
		while (current) {
			if (strcmp(current->data, data) == 0) {
				if (prev == 0) {
					if (current->next) {
						strcpy(current->data, current->next->data);
						current->next = current->next->next;
					}
					else {
						strcpy(current->data, "");
						strcpy(current->key, "");
						return 1;
					}
				}
				else {
					prev->next = current->next;
					return 1;
				}
			}
			prev = current;
			current = current->next;
		}
	}
	return 0;
}

void printNode(const char* key)
{
	unsigned long val = hashFunc(key);
	Node* current = &hashTable[val];

	while (current) {
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl;
}