#include <iostream>
#include <vector>
#include <string>

#define MAX_ALPHA 58
#define MAX_NODE 1000
// A 65, Z 90 // a 97, z 122
/************************************************************
* Please Implement It!
*/

namespace algo {
	struct Node {
		Node* children[MAX_ALPHA];
		bool isEnd;
	};

	Node node[MAX_NODE];
	int nodeIdx;

	Node* getNode() {
		node[nodeIdx].isEnd = false;
		for (int i = 0; i < MAX_ALPHA; i++) {
			node[nodeIdx].children[i] = NULL;
		}
		return &node[nodeIdx++];
	}

	Node* root = getNode();

	void insert(const char* str) {
		Node* tmp = root;
		for (int i = 0; i < strlen(str); i++) {
			int idx = str[i] - 'A';
			if (!tmp->children[idx]) {
				tmp->children[idx] = getNode();
			}
			tmp = tmp->children[idx];
		}
		tmp->isEnd = true;
	}

	bool search(const char* str) {
		Node* tmp = root;
		for (int i = 0; i < strlen(str); i++) {
			int idx = str[i] - 'A';
			if (!tmp->children[idx]) return false;
			tmp = tmp->children[idx];
		}
		return (tmp && tmp->isEnd);
	}

	bool remove(const char* str) {
		Node* tmp = root;
		for (int i = 0; i < strlen(str); i++) {
			int idx = str[i] - 'A';
			if (!tmp->children[idx]) return false;
			tmp = tmp->children[idx];
		}
		if (tmp && tmp->isEnd) {
			tmp->isEnd = false;
			return true;
		}
		return false;
	}



} // namespace algo

  /*************************************************************
  * Test Cases
  */
namespace {
	const std::vector<std::string> kPositiveTC = {
		"the",
		"THE",
		"a",
		"answer",
		"any",
		"by",
		"bye",
		"their",
		"hero",
		"heroplane",
	};
	const std::vector<std::string> kRemoving = {
		"the",
		"a",
		"by",
		"heroplane",
	};
	const std::vector<std::string> kNegativeTC = {
		"TH",
		"ther",
		"A",
		"ANSWER",
		"ani",
		"bYE",
		"HEROPLANES",
		"heroplaness",
	};
}  // namespace

int main() {
	int score = 100;
	for (const std::string& str : kPositiveTC) {
		algo::insert(str.c_str());
	}
	for (const std::string& str : kPositiveTC) {
		if (algo::search(str.c_str()) == false) {
			score -= 5;
		}
	}
	for (const std::string& str : kNegativeTC) {
		if (algo::search(str.c_str()) == true) {
			score -= 5;
		}
	}
	for (const std::string& str : kNegativeTC) {
		if (algo::remove(str.c_str()) == true) {
			score -= 5;
		}
	}
	for (const std::string& str : kRemoving) {
		if (algo::remove(str.c_str()) == false) {
			score -= 5;
		}
	}
	for (const std::string& str : kRemoving) {
		algo::insert(str.c_str());
	}
	for (const std::string& str : kPositiveTC) {
		if (algo::search(str.c_str()) == false) {
			score -= 5;
		}
	}
	for (const std::string& str : kRemoving) {
		if (algo::search(str.c_str()) == false) {
			score -= 5;
		}
	}
	std::cout << "SCORE : " << score << "/100" << std::endl;
}