#include <iostream>
using namespace std;

#define MAX_TABLE 5000
#define MAX_DATA_SIZE 100

typedef struct tagNode {
	char value[MAX_DATA_SIZE];
	tagNode* nextNode;
}Node;

void nodePrint(Node *node);

Node* hashTable[MAX_TABLE];

unsigned long hash_key(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_TABLE;
	}

	return hash % MAX_TABLE;
}

Node *createNode(char *value) {
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->nextNode = NULL;
	
	int index = 0;
	while (value[index]) {
		newNode->value[index] = value[index];
		index++;
	}
	newNode->value[index] = '\0';
	return newNode;
}

void insertHash(char *key, char *value) {
	long tableKey = hash_key(key);
	Node* newNode = createNode(value);
	if (hashTable[tableKey] == NULL) {
		hashTable[tableKey] = newNode;
	}
	else {
		newNode->nextNode = hashTable[tableKey];
		hashTable[tableKey] = newNode;
	}
}

void printHash(char* key) {
	long tableKey = hash_key(key);
	if (hashTable[tableKey] == NULL)
		return;
	nodePrint(hashTable[tableKey]);
	cout << endl;
}

void nodePrint(Node *node) {
	if (node == NULL) {
		return;
	}
	nodePrint(node->nextNode);
	cout << node->value << " ";
}

int strLen_(char *a) {
	int index = 0;
	while (a[index]) {
		index++;
	}
	return index;
}
bool strCmp_(char *a, char *b) {
	int aSize = strLen_(a);
	int bSize = strLen_(b);
	if (aSize != bSize)
		return false;

	for (int i = 0; i < aSize; i++) {
		if (a[i] != b[i])
			return false;
	}
	return true;
}

void deleteHash(char *key, char *value) {
	long tableKey = hash_key(key);
	Node* cur = hashTable[tableKey];
	Node* delNode = NULL;
	if (strCmp_(cur->value, value)) {
		delNode = cur;
		hashTable[tableKey] = hashTable[tableKey]->nextNode;
	}
	else {
		while (cur->nextNode) {
			if (strCmp_(cur->nextNode->value, value)) {
				delNode = cur->nextNode;
				cur->nextNode = cur->nextNode->nextNode;
				break;
			}
			cur = cur->nextNode;
		}
	}
	free(delNode);
}


int main() {
	insertHash("MSFT", "MicrosoftCorporation");
	insertHash("JAVA", "SunMicrosystems");
	insertHash("REDH", "RedHatLinux");
	insertHash("APAC", "ApacheOrg");
	insertHash("ZYMZZ", "UnisysOpsCheck");
	insertHash("IBM", "IBMLtd.");
	insertHash("ORCL", "OracleCorporation");
	insertHash("CSCO", "CiscoSystems,Inc.");
	insertHash("GOOG", "GoogleInc.");
	insertHash("YHOO", "Yahoo!Inc.");
	insertHash("NOVL", "Novell,Inc.");
	insertHash("JAVA", "Oracle");
	insertHash("JAVA", "OpenJDK");

	//deleteHash("JAVA", "SunMicrosystems");
	//deleteHash("JAVA", "OpenJDK");
	deleteHash("JAVA", "Oracle");

	printHash("MSFT");
	printHash("JAVA");
	printHash("REDH");
	printHash("APAC");
	printHash("ZYMZZ");
	printHash("IBM");
	printHash("ORCL");
	printHash("CSCO");
	printHash("GOOG");
	printHash("YHOO");
	printHash("GOOG");
	printHash("NOVL");

	return 0;
}