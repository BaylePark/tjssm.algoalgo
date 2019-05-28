#include <iostream>
using namespace std;
typedef struct tagTrie {
	int isEnd = 0;
	tagTrie* next[26];
}Trie;

Trie mDB[10000];
int mDBcnt = 0;
Trie* Head;
int main() {
	Head = &mDB[mDBcnt++];

	//add
	for (int i = 0; i < 3; i++) {
		char str[100];
		cin >> str;
		int idx = 0;
		Trie* cur = Head;
		while (str[idx]) {
			int ch = str[idx]-'a';
			if (cur->next[ch] == NULL) {
				cur->next[ch] = &mDB[mDBcnt++];
			}
			cur = cur->next[ch];
			idx++;
		}
		cur->isEnd = 1;
	}
	
	//search
	for (int i = 0; i < 2; i++) {
		char str[100];
		cin >> str;

		int isCmp = 0;
		int idx = 0;
		Trie* cur = Head;
		while (str[idx]) {
			int ch = str[idx] - 'a';
			if (cur->next[ch] == NULL) {
				isCmp = -1;
				break;
			}
			cur = cur->next[ch];
			idx++;
		}
		if (cur->isEnd == 1 && isCmp == 0) {
			isCmp = 1;
		}
		if (isCmp == 1) {
			cout << "true" << endl;
		}
		else {
			cout << "false" << endl;
		}
	}


	//del
	for (int i = 0; i < 2; i++) {
		char str[100];
		cin >> str;

		int isCmp = 0;
		int idx = 0;
		Trie* cur = Head;
		while (str[idx]) {
			int ch = str[idx] - 'a';
			if (cur->next[ch] == NULL) {
				isCmp = -1;
				break;
			}
			cur = cur->next[ch];
			idx++;
		}
		if (cur->isEnd == 1 && isCmp == 0) {
			cur->isEnd = 0;
			isCmp = 1;
		}
		if (isCmp == 1) {
			cout << "true" << endl;
		}
		else {
			cout << "false" << endl;
		}
	}
	return 0;
}