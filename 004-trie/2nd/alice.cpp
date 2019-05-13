#include <iostream>
#include <vector>
#include <string>

/************************************************************
* Please Implement It!
*/
// A 65, Z 90 // a 97, z 122
#define ALPHACOUNT 26*2
#define MAXNODE 100000

namespace algo {
	struct Node {
		Node* children[ALPHACOUNT];
		bool isEnd;
	};
	int idx = 0;
	Node node[MAXNODE];

	Node* getNode() {
		Node* tmp = &node[idx++];
		for (int i = 0; i < ALPHACOUNT; i++) {
			tmp->children[i] = NULL;
		}
		tmp->isEnd = false;
		return tmp;
	}
	Node* root = getNode();

	int atoi(char str) {
		if (str - 'a' < 0) {
			return (int) (str - 'A' + 27);
		}
		else {
			return (int)(str - 'a');
		}
	}

	void insert(const char* str) {
		Node* tmp = root;
		for (int i = 0; i < strlen(str); i++) {
			if (tmp->children[atoi(str[i])] == NULL) {
				tmp->children[atoi(str[i])] = getNode();
			}
			tmp = tmp->children[atoi(str[i])];
		}
		tmp->isEnd = true;
	}

	bool search(const char* str) {
		Node* tmp = root;
		for (int i = 0; i < strlen(str); i++) {
			if (tmp->children[atoi(str[i])] == NULL) {
				return false;
			}
			tmp = tmp->children[atoi(str[i])];
		}
		return tmp->isEnd;
	}

	bool remove(const char* str) {
		Node* tmp = root;
		for (int i = 0; i < strlen(str); i++) {
			if (tmp->children[atoi(str[i])] == NULL) {
				return false;
			}
			tmp = tmp->children[atoi(str[i])];
		}
		bool result = tmp->isEnd;
		tmp->isEnd = false;
		return result;
	}
} // namespace algo

  /*************************************************************
  * Test Cases
  */
namespace {
	const std::vector<std::string> kPositiveTC = {
		"zZed",
		"ZZezd",
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
		"ZZezd",
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