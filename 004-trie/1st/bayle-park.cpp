#include <iostream>
#include <vector>
#include <string>

/************************************************************
 * Please Implement It!
 */

#define ALPHABET_LOWER_SIZE ('z' - 'a' + 1)
#define ALPHABET_UPPER_SIZE ('Z' - 'A' + 1)
#define ALPHABET_SIZE (ALPHABET_LOWER_SIZE + ALPHABET_UPPER_SIZE)
#define MAX_SIZE 50000

namespace algo {
    
    template <typename T>
    struct Allocator {
        T* alloc() {
            T* ret = &mempool[idx++];
            ret->init();
            return ret;
        }
        void init() {
            idx = 0;
        }
        int idx;
        T mempool[MAX_SIZE];
    };
    struct TrieNode {
        TrieNode* alphabet[ALPHABET_SIZE];
        bool is_end;
        
        void init() {
            for (int i = 0; i < ALPHABET_SIZE; i++) alphabet[i] = NULL;
            is_end = false;
        }
    };
    
    TrieNode root;
    Allocator<TrieNode> allocator;
    
    void init() {
        root.init();
        allocator.init();
    }
    
    int toi(const char c) {
        if (c >= 'a' && c <= 'z') return (int)(c - 'a');
        else return (int)(c - 'A');
    }
    
    void insert(const char* str) {
        int idx = 0;
        TrieNode* node = &root;
        while (str[idx]) {
            TrieNode** next = &(node->alphabet[toi(str[idx])]);
            if (*next == NULL) {
                *next = allocator.alloc();
            }
            node = *next;
            idx++;
        }
        node->is_end = true;
    }
    
    bool search(const char* str) {
        bool found = true;
        int idx = 0;
        TrieNode* node = &root;
        while (str[idx]) {
            TrieNode* next = (node->alphabet[toi(str[idx])]);
            if (next == NULL) {
                found = false;
                break;
            }
            node = next;
            idx++;
        }
        if (node->is_end == false) {
            found = false;
        }
        return found;
    }
    
    bool remove(const char* str) {
        int idx = 0;
        TrieNode* node = &root;
        while (str[idx]) {
            TrieNode* next = (node->alphabet[toi(str[idx])]);
            if (next == NULL) return false;
            node = next;
            idx++;
        }
        if (node->is_end) {
            node->is_end = false;
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
    algo::init();
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
