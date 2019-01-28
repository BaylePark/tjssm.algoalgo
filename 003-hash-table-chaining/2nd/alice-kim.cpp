#include <iostream>
using namespace std;

#define MAX_NODE 100000
#define MAX_TABLE 4096
#define MAX_KEY 64
#define MAX_DATA 128

struct Node {
	char data[MAX_DATA];
	Node* next;
};
unsigned long myHash(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

Node* hashTable[MAX_TABLE]; 
Node hashNode[MAX_NODE];
int hashIdx;

void add(char* key, char* data);
void deleteValue(char* key, char* data);
void printValue(char* key);


int main() {
	int tc = 0;
	cin >> tc;

	while (tc--) {
		char key[MAX_KEY];
		char data[MAX_DATA];

		cin >> key >> data;
		add(key, data);
	}
	printValue("JAVA");
	deleteValue("JAVA", "OpenJDK");
	printValue("JAVA");
	return 0;

}

void add(char* key, char* data) {
	unsigned long val = myHash(key);

	Node* newNode = &hashNode[hashIdx++];
	strcpy(newNode->data, data);
	newNode->next = 0;

	if (hashTable[val] == 0) {
		hashTable[val] = newNode;
	}
	else {
		newNode->next = hashTable[val];
		hashTable[val] = newNode;
	}
}

void deleteValue(char* key, char* data) {
	unsigned long val = myHash(key);

	Node** node = &hashTable[val];
	while (node) {
		if (strcmp((*node)->data, data) == 0) {
			*node = (*node)->next;
			break;
		}
		node = &(*node)->next;
	}
}
void printValue(char* key) {
	unsigned long val = myHash(key);
	Node* current = hashTable[val];
	while (current) {
		cout << current->data << " ";
		current = current->next;
	}
	cout << endl;
}
