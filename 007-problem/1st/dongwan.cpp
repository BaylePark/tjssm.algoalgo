#include <stdio.h>
#include <iostream>
#include <malloc.h>
using namespace std;
#define MAX_RECORD_SIZE 50005
#define MAX_HASH_SIZE 10007

typedef enum
{
	NAME,
	NUMBER,
	BIRTHDAY,
	EMAIL,
	MEMO
} FIELD;

typedef struct
{
	int count;
	char str[20];
} RESULT;

typedef struct tagUser {
	char name[20];
	char number[20];
	char birthday[20];
	char email[20];
	char memo[20];
}User;

typedef struct tagHash {
	User *user;
	tagHash *next = NULL;
}Hash;

Hash* hashTable[MAX_HASH_SIZE];
User* userList[MAX_RECORD_SIZE];
int userDataSize = 0;

////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////
void strcpy_(char*a, char*b) {
	int idx = 0;
	while (a[idx]) {
		b[idx] = a[idx];
		idx++;
	}
	b[idx] = '\0';
}

int strSize(char*a) {
	int idx = 0;
	while (a[idx]) {
		idx++;
	}
	return idx;
}

int strCmp(char *a, char *b) {
	int aSize = strSize(a);
	int bSize = strSize(b);
	if (aSize != bSize)
		return 0;
	int idx = 0;
	while (a[idx]) {
		if (a[idx] != b[idx])
			return 0;
		idx++;
	}
	return 1;
}

unsigned long hashKey(const char *str)
{
	unsigned long hash = 5381;
	int c;

	while (c = *str++)
	{
		hash = (((hash << 5) + hash) + c) % MAX_HASH_SIZE;
	}

	return hash % MAX_HASH_SIZE;
}

User* createUser(char* name, char* number, char* birthday, char* email, char* memo) {
	User* user = (User*)malloc(sizeof(User));
	strcpy_(name, user->name);
	strcpy_(number, user->number);
	strcpy_(birthday, user->birthday);
	strcpy_(email, user->email);
	strcpy_(memo, user->memo);
	return user;
}

Hash* createHash() {
	Hash* hash = (Hash*)malloc(sizeof(Hash));
	hash->next = NULL;
	hash->user = NULL;
	return hash;
}

void insertTable(User* user, int key) {
	if (hashTable[key] == NULL) {
		hashTable[key] = createHash();
		hashTable[key]->user = user;
	}
	else {
		Hash* temp = hashTable[key];
		hashTable[key] = createHash();
		hashTable[key]->next = temp;
	}
}

void InitDB()
{
	if (userDataSize != 0) {
		for (int i = 0; i < userDataSize; i++) {
			User *u = userList[i];
			free(u);
		}
	}
	userDataSize = 0;
	for (int i = 0; i < MAX_HASH_SIZE; i++) {
		if (hashTable != NULL) {
			Hash* temp = hashTable[i];
			Hash* before = NULL;
			while (temp) {
				before = temp;
				temp = temp->next;
				free(before);
			}
			hashTable[i] = NULL;
		}
	}
}

void Add(char* name, char* number, char* birthday, char* email, char* memo)
{
	User*u = createUser(name, number, birthday, email, memo);
	userList[userDataSize++] = u;

	cout << "ADD " << " addr:" << u << " name:" << name << " number:" << number << " birthday:" << birthday << " email:" << email << " memo:" << memo << endl;
	int keyName = hashKey(name);
	int keyNumber = hashKey(number);
	int keyBirthday = hashKey(birthday);
	int keyEmail = hashKey(email);
	int keyMemo = hashKey(memo);
	insertTable(u, keyName);
	insertTable(u, keyNumber);
	insertTable(u, keyBirthday);
	insertTable(u, keyEmail);
	insertTable(u, keyMemo);
}

void deleteHash(Hash *temp, int key) {
	Hash* temp2 = hashTable[key];
	while (temp2) {
		if (temp2->user == temp->user) {
			temp2->user = NULL;
			break;
		}
		temp2 = temp2->next;
	}
}
int Delete(FIELD field, char* str)
{
	int key = hashKey(str);
	cout << "Delete >> field:" << field << " str:" << str << " key:" << key << endl;
	int cnt = 0;
	Hash* temp = hashTable[key];
	Hash* tempNext = NULL;
	while (temp) {
		if (temp->user == NULL) {
			temp = temp->next;
			continue;
		}
		if (field == NAME) {
			if (strCmp(str, temp->user->name)) {
				int keyNumber = hashKey(temp->user->number);
				int keyBirthday = hashKey(temp->user->birthday);
				int keyEmail = hashKey(temp->user->email);
				int keyMemo = hashKey(temp->user->memo);

				deleteHash(temp, keyNumber);
				deleteHash(temp, keyBirthday);
				deleteHash(temp, keyEmail);
				deleteHash(temp, keyMemo);
				temp->user = NULL;
				cnt++;
			}
		}
		else if (field == NUMBER) {
			if (strCmp(str, temp->user->number)) {
				int keyName = hashKey(temp->user->name);
				int keyBirthday = hashKey(temp->user->birthday);
				int keyEmail = hashKey(temp->user->email);
				int keyMemo = hashKey(temp->user->memo);

				deleteHash(temp, keyName);
				deleteHash(temp, keyBirthday);
				deleteHash(temp, keyEmail);
				deleteHash(temp, keyMemo);
				temp->user = NULL;
				cnt++;
			}
		}
		else if (field == BIRTHDAY) {
			if (strCmp(str, temp->user->birthday)) {
				int keyName = hashKey(temp->user->name);
				int keyNumber = hashKey(temp->user->number);
				int keyEmail = hashKey(temp->user->email);
				int keyMemo = hashKey(temp->user->memo);

				deleteHash(temp, keyName);
				deleteHash(temp, keyNumber);
				deleteHash(temp, keyEmail);
				deleteHash(temp, keyMemo);
				temp->user = NULL;
				cnt++;
			}
		}
		else if (field == EMAIL) {
			if (strCmp(str, temp->user->email)) {
				int keyName = hashKey(temp->user->name);
				int keyNumber = hashKey(temp->user->number);
				int keyBirthday = hashKey(temp->user->birthday);
				int keyMemo = hashKey(temp->user->memo);

				deleteHash(temp, keyName);
				deleteHash(temp, keyNumber);
				deleteHash(temp, keyBirthday);
				deleteHash(temp, keyMemo);
				temp->user = NULL;
				cnt++;
			}
		}
		else if (field == MEMO) {
			if (strCmp(str, temp->user->memo)) {
				int keyName = hashKey(temp->user->name);
				int keyNumber = hashKey(temp->user->number);
				int keyBirthday = hashKey(temp->user->birthday);
				int keyEmail = hashKey(temp->user->email);

				deleteHash(temp, keyName);
				deleteHash(temp, keyNumber);
				deleteHash(temp, keyBirthday);
				deleteHash(temp, keyEmail);
				temp->user = NULL;
				cnt++;
			}
		}
		temp = temp->next;
	}
	if (cnt != 0)
		return cnt;
	return -1;
}

void changeHash(Hash* temp, FIELD changefield, char* changestr) {
	if (changefield == NAME) {
		strcpy_(changestr, temp->user->name);
	}
	else if (changefield == NUMBER) {
		strcpy_(changestr, temp->user->number);
	}
	else if (changefield == BIRTHDAY) {
		strcpy_(changestr, temp->user->birthday);
	}
	else if (changefield == EMAIL) {
		strcpy_(changestr, temp->user->email);
	}
	else if (changefield == MEMO) {
		strcpy_(changestr, temp->user->memo);
	}
}
int Change(FIELD field, char* str, FIELD changefield, char* changestr)
{
	int key = hashKey(str);
	cout << "Change >> field:" << field << " str:" << str << " changefield:" << changefield << " changestr:" << changestr << " key:" << key << endl;
	Hash* temp = hashTable[key];
	int cnt = 0;
	while (temp) {
		if (temp->user == NULL) {
			temp = temp->next;
			continue;
		}
		if (field == NAME) {
			if (strCmp(str, temp->user->name)) {
				changeHash(temp, changefield, changestr);
				cnt++;
				break;
			}
		}
		else if (field == NUMBER) {
			if (strCmp(str, temp->user->number)) {
				changeHash(temp, changefield, changestr);
				cnt++;
				break;
			}
		}
		else if (field == BIRTHDAY) {
			if (strCmp(str, temp->user->birthday)) {
				changeHash(temp, changefield, changestr);
				cnt++;
				break;
			}
		}
		else if (field == EMAIL) {
			if (strCmp(str, temp->user->email)) {
				changeHash(temp, changefield, changestr);
				cnt++;
				break;
			}
		}
		else if (field == MEMO) {
			if (strCmp(str, temp->user->memo)) {
				changeHash(temp, changefield, changestr);
				cnt++;
				break;
			}
		}
		temp = temp->next;
	}
	if (cnt != 0) {
		return cnt;
	}
	return -1;
}

RESULT Search(FIELD field, char* str, FIELD ret_field)
{
	RESULT result;
	result.count = -1;

	int key = hashKey(str);
	int cnt = 0;
	Hash* temp = hashTable[key];
	Hash* beforeHash;
	while (temp) {
		if (field == NAME) {
			if (strCmp(str, temp->user->name)) {
				beforeHash = temp;
				cnt++;
			}
		}
		else if (field == NUMBER) {
			if (strCmp(str, temp->user->number)) {
				beforeHash = temp;
				cnt++;
			}
		}
		else if (field == BIRTHDAY) {
			if (strCmp(str, temp->user->birthday)) {
				beforeHash = temp;
				cnt++;
			}
		}
		else if (field == EMAIL) {
			if (strCmp(str, temp->user->email)) {
				beforeHash = temp;
				cnt++;
			}
		}
		else if (field == MEMO) {
			if (strCmp(str, temp->user->memo)) {
				beforeHash = temp;
				cnt++;
			}
		}
		temp = temp->next;
	}
	if (cnt != 0) {
		result.count = cnt;
		if (ret_field == NAME) {
			strcpy_(beforeHash->user->name, result.str);
		}
		else if (ret_field == NUMBER) {
			strcpy_(beforeHash->user->number, result.str);
		}
		else if (ret_field == BIRTHDAY) {
			strcpy_(beforeHash->user->birthday, result.str);
		}
		else if (ret_field == EMAIL) {
			strcpy_(beforeHash->user->email, result.str);
		}
		else if (ret_field == MEMO) {
			strcpy_(beforeHash->user->memo, result.str);
		}
	}
	result.count = cnt;
	return result;
}