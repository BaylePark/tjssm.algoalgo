# TRIE 구현하기
## 기본내용
40분 내에 해결하기

## 필수 구현 내용
1. insert
2. search // 검색이 되면 true, 아니면 false
3. delete // 잘 삭제되었다면 true, 아니면 false 

## 아래 코드를 복사해서 구현하세요 :)
```cpp
#include <iostream>
#include <vector>
#include <string>

/************************************************************
 * Please Implement It!
 */

namespace algo {
void insert(const char* str) {
}

bool search(const char* str) {
  return false;
}

bool remove(const char* str) {
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
    if (algo::search(str.c_str()) == true) {
      score -= 5;
    }
  }
  std::cout << "SCORE : " << score << "/100" << std::endl;
}

```

### Test Cases
```cpp
the 
a 
there
answer
any
by
bye
their
hero
heroplane


// search 
the // return true
t // return false

// delete
answer // true
answer // false
```
