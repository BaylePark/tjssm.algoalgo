#include <iostream>
#include <vector>
#include <string>

#define START_CH 65
// A 65, Z 90 // a 97, z 122

/************************************************************
* Please Implement It!
*/
typedef struct tagWord {
   bool isUsed = false;
   bool isEnd = false;
}Word;

typedef struct tagTrie {
   // 122 - 65 = 57
   Word word[57];
   tagTrie * nextNode;
}Trie;

Trie *Head = NULL;

Trie *createNode() {
   Trie* newNode = (Trie*)malloc(sizeof(Trie));
   newNode->nextNode = NULL;
   return newNode;
}

int getFakeCh(char ch) {
   int temp = ch - START_CH;
   return temp;
}

namespace algo {
   void insert(const char* str) {
      int strSize = strlen(str);
      Trie** cur = &Head;
      for (int i = 0; i < strSize; i++) {
         if (*cur == NULL) {
            *cur = createNode();
         }
         int ch = getFakeCh(str[i]);
         (*cur)->word[ch].isUsed = true;
         if (i + 1 == strSize) {
            (*cur)->word[ch].isEnd = true;
         }
         else {
            cur = &((*cur)->nextNode);
         }
      }
   }

   bool search(const char* str) {
      int strSize = strlen(str);
      Trie** cur = &Head;
      for (int i = 0; i < strSize; i++) {
         if (*cur == NULL) {
            return false;
         }
         int ch = getFakeCh(str[i]);
         
         if (i + 1 == strSize && (*cur)->word[ch].isEnd == true) {
            return true;
         }

         if ((*cur)->word[ch].isUsed == true) {
            cur = &((*cur)->nextNode);
         }
         else {
            return false;
         }

      }
      return false;
   }

   bool remove(const char* str) {
      int strSize = strlen(str);
      Trie** cur = &Head;
      for (int i = 0; i < strSize; i++) {
         if (*cur == NULL) {
            return false;
         }
         int ch = getFakeCh(str[i]);
         if (i + 1 == strSize &&  (*cur)->word[ch].isEnd == true) {
            (*cur)->word[ch].isEnd = false;
            return true;
         }

         if ((*cur)->word[ch].isUsed == true) {
            cur = &(*cur)->nextNode;
         }
         else {
            return false;
         }
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
   //Head = createNode();
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