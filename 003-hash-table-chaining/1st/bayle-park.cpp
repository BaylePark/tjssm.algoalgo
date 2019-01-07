#include <iostream>

#define MAX_TABLE 1000007
#define MAX_ALLOC MAX_TABLE * 2

template <typename T>
struct Allocator
{
    T *alloc()
    {
        T *ret = &pool_[idx_];
        idx_++;
        ret->init();
        return ret;
    }
    void init()
    {
        idx_ = 0;
    }
    T pool_[MAX_ALLOC];
    int idx_;
};

template <typename TValue>
struct Node
{
    TValue *data_;
    Node *next_, *prev_;
    void init()
    {
        data_ = NULL;
        next_ = prev_ = NULL;
    }
};

template <typename TValue>
struct List
{
    int count_;
    Node<TValue> *head_, *tail_;
    void init()
    {
        head_ = tail_ = NULL;
        count_ = 0;
    }
    void push_back(Node<TValue> *node)
    {
        if (head_ == NULL /* || tail_ == NULL */)
        {
            head_ = tail_ = node;
        }
        else
        {
            node->prev_ = tail_;
            tail_->next_ = node;
            tail_ = node;
        }
        count_++;
    }
    void remove(Node<TValue> *node)
    {
        if (node == head_)
            head_ = node->next_;
        if (node == tail_)
            tail_ = node->prev_;
        if (node->next_)
            node->next_->prev_ = node->prev_;
        if (node->prev_)
            node->prev_->next_ = node->next_;
        count_--;
    }
    int get_count()
    {
        return count_;
    }
};

template <typename TValue>
struct HashTable
{
    typedef unsigned long KeyType;
    List<TValue> table_[MAX_TABLE];
    Allocator< Node<TValue> > allocator_;
    
    void add(const char *key, TValue *value)
    {
        KeyType key_value = hash(key);
        Node<TValue> *new_node = allocator_.alloc();
        new_node->data_ = value;
        table_[key_value].push_back(new_node);
    }
    void remove(const char *key, TValue *value)
    {
        KeyType key_value = hash(key);
        if (table_[key_value].get_count() == 0)
            return;
        Node<TValue> *node = table_[key_value].head_;
        while (node)
        {
            if (node->data_->is_same(*value))
            {
                table_[key_value].remove(node);
            }
            node = node->next_;
        }
    }
    void print(const char *key)
    {
        KeyType key_value = hash(key);
        if (table_[key_value].get_count() == 0) {
            std::cout << "empty" << std::endl;
            return;
        }
        Node<TValue> *node = table_[key_value].head_;
        while (node)
        {
            std::cout << *node->data_ << " > ";
            node = node->next_;
        }
        std::cout << std::endl;
    }
    KeyType hash(const char *str)
    {
        KeyType hash = 5381;
        int c;
        
        while (c = *str++)
        {
            hash = (((hash << 5) + hash) + c) % MAX_TABLE;
        }
        
        return hash % MAX_TABLE;
    }
};

struct DataBase
{
    char key_[6];
    char value_[50];
    bool is_same(const DataBase &db) const
    {
        for (int i = 0; i < 50; i++)
        {
            if (value_[i] != db.value_[i])
                return false;
            if (value_[i] == 0 && db.value_[i] == 0) break;
        }
        return true;
    }
    friend std::ostream& operator << (std::ostream& os, const DataBase& node) {
        os << "(" << node.value_ << ")";
        return os;
    }
};

DataBase db[MAX_ALLOC];
HashTable<DataBase> hash_table;

int main()
{
    int N;
    std::cout << "HashTable Record Number: ";
    std::cin >> N;
    for (int i = 0; i < N; i++)
    {
        std::cin >> db[i].key_ >> db[i].value_;
        hash_table.add(db[i].key_, &db[i]);
    }
    
    int M;
    std::cout << "Number of Removing: ";
    std::cin >> M;
    while(M--)
    {
        DataBase temp;
        std::cin >> temp.key_ >> temp.value_;
        hash_table.remove(temp.key_, &temp);
    }
    
    int O;
    std::cout << "Number of Printing: ";
    std::cin >> O;
    while(O--)
    {
        char key[6];
        std::cin >> key;
        hash_table.print(key);
    }
    return 0;
}
