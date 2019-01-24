#include <iostream>

#define MAX_HASH_NODE 100007
#define MAX_DATA MAX_HASH_NODE*2
#define KEY_SIZE 5
#define VALUE_SIZE 50

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
  T mempool[MAX_DATA];
};

template <typename T>
struct Node {
  void init() {
    data = NULL;
    next = prev = NULL;
  }
  T* data;
  Node<T> *next, *prev;
};

template <typename T>
struct NodeList {
  void insert(Node<T> *node) {
    if (head == NULL || tail == NULL) {
      head = tail = node;
      return;
    }
    node->prev = tail;
    tail->next = node;
    tail = node;
    return;
  }
  void remove(Node<T> *node) {
    if (node == head) {
      head = node->next;
    }
    if (node == tail) {
      tail = node->prev;
    }
    if (node->next) {
      node->next->prev = node->prev;
    }
    if (node->prev) {
      node->prev->next = node->next;
    }
  }
  Node<T> *head, *tail;
};

template <typename T>
struct HashTable {
  void insert(char* key, T *value) {
    Node<T>* node = allocator.alloc();
    node->data = value;
    unsigned long hashKey = hash(key);
    nodes[hashKey].insert(node);
  }
  void remove(char *key, T *value) {
    unsigned long hashKey = hash(key);
    Node<T> *node = nodes[hashKey].head;
    while(node) {
      if (node->data->is_same(*value)) {
        nodes[hashKey].remove(node);
      }
      node = node->next;
    }
  }
  unsigned long hash(const char *str) {
     unsigned long hash = 5381;
     int c;
     while (c = *str++)
       hash = (((hash << 5) + hash) + c) % MAX_HASH_NODE;
     return hash % MAX_HASH_NODE;
  }
  Node<T>* find(const char* key) {
    return nodes[hash(key)].head;
  }
  NodeList<T> nodes[MAX_HASH_NODE];
  Allocator< Node<T> > allocator;
};

struct DataBase {
  char key[KEY_SIZE + 1];
  char value[VALUE_SIZE + 1];
  bool is_same(const DataBase& target) {
    for (int i=0; i < VALUE_SIZE; i++) {
      if (value[i] != target.value[i]) return false;
      if (value[i] == 0 && target.value[i] == 0) break;
    }
    return true;
  }
};

DataBase db[MAX_DATA];
HashTable<DataBase> hashTable;

int main() {
  int n;
  std::cout << "Input Max Size : ";
  std::cin >> n;

  for(int i=0; i < n; i++) {
    std::cin >> db[i].key >> db[i].value;
    hashTable.insert(db[i].key, &db[i]);
  }
  
  std::cout << "Input Size to remove : ";
  std::cin >> n;

  for(int i=0; i < n; i++) {
    DataBase target;
    std::cin >> target.key >> target.value;
    hashTable.remove(target.key, &target);
  }

  std::cout << "Input Size to find : ";
  std::cin >> n;

  for(int i=0; i < n; i++) {
    char key[KEY_SIZE + 1];
    std::cin >> key;
    Node<DataBase>* node = hashTable.find(key);
    while(node) {
      std::cout << node->data->value << " > ";
      node = node->next;
    }
    std::cout << std::endl;
  }
  return 0;
}
