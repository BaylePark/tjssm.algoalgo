#include <iostream>

#define MAX_DATA 1000000
#ifndef NULL
#define NULL 0
#endif

template <typename T>
struct Allocator {
    void init() {
        idx = 0;
    }
    T* alloc() {
        T* ret = &mempool[idx++];
        ret->init();
        return ret;
    }
    int idx;
    T mempool[MAX_DATA];
};

template <typename T>
struct Node {
    Node<T> *prev, *next;
    T data;
    void init() {
        prev = next = NULL;
    }
    friend std::ostream& operator<< (std::ostream& os, const Node<T>* node) {
        if (node == NULL) os << "(invalid)";
        else os << node->data;
        return os;
    }
};

template <typename T, typename Allocator = Allocator< Node<T> > >
struct List {
    void init() {
        allocator.init();
    }
    Node<T>* find(Node<T>* target, const T& val) {
        if (target == NULL) target = head;
        else target = target->next;
        while (target) {
            if (target->data == val) break;
            target = target->next;
        }
        return target;
    }
    void remove(Node<T>* target) {
        if (target->prev) target->prev->next = target->next;
        if (target->next) target->next->prev = target->prev;
        if (target == head) head = target->next;
        if (target == tail) tail = target->prev;
    }
    Node<T>* insert(Node<T>* target, const T& val) {
        Node<T>* newnode = allocator.alloc();
        newnode->data = val;
        newnode->prev = target;
        newnode->next = target->next;
        if (target->next) target->next->prev = newnode;
        target->next = newnode;
        return newnode;
    }
    Node<T>* push(const T& val) {
        Node<T>* newnode = allocator.alloc();
        newnode->data = val;
        newnode->prev = tail;
        if (head == NULL || tail == NULL) {
            head = tail = newnode;
            return newnode;
        }
        tail->next = newnode;
        tail = newnode;
        return newnode;
    }
    void print() {
        Node<T>* target = head;
        while(target) {
            std::cout << target << " > ";
            target = target->next;
        }
        std::cout << std::endl;
    }
    void reversal_print() {
        Node<T>* target = tail;
        while(target) {
            std::cout << target << " > ";
            target = target->prev;
        }
        std::cout << std::endl;
    }
    Node<T> *head, *tail;
    Allocator allocator;
};

struct Point2D {
    int x, y;
    bool operator== (const Point2D& p1) const {
        return p1.x == x && p1.y == y;
    }
    friend std::ostream& operator<< (std::ostream& os, const Point2D& pt) {
        os << '(' << pt.x << ", " << pt.y << ')';
        return os;
    }
};

List<Point2D> list;

int main() {
    list.init();
    Node<Point2D> *node1, *node2, *node3, *node4, *found_node2;
    
    {
        Point2D p;
        p.x = 1, p.y = 1;
        node1 = list.push(p);
        list.print();
        list.reversal_print();
    }
    
    {
        Point2D p;
        p.x = 1, p.y = 2;
        node2 = list.push(p);
        list.print();
        list.reversal_print();
    }
    
    {
        Point2D p;
        p.x = 2, p.y = 2;
        node3 = list.push(p);
        list.print();
        list.reversal_print();
    }
    
    {
        Point2D p;
        p.x = 1, p.y = 2;
        found_node2 = list.find(NULL, p);
        std::cout << found_node2 << std::endl;
        found_node2->data.x = 9;
        found_node2->data.y = 9;
    }
    
    {
        Point2D p;
        p.x = 9, p.y = 9;
        Node<Point2D> *node = list.find(NULL, p);
        std::cout << node << std::endl;
        list.print();
        list.reversal_print();
    }
    
    {
        Point2D p;
        p.x = 4, p.y = 1;
        node4 = list.insert(node2, p);
        list.print();
        list.reversal_print();
    }
    
    {
        list.remove(node1);
        list.print();
        list.reversal_print();
    }
    
    {
        list.remove(node3);
        list.print();
        list.reversal_print();
    }
    
    {
        list.remove(node4);
        list.print();
        list.reversal_print();
    }
    
    {
        list.remove(found_node2);
        list.print();
        list.reversal_print();
    }
}
