#include <stdio.h>

#define MAX_POOL_SIZE 1000000

template <typename T>
struct Allocator {
    T mempool[MAX_POOL_SIZE];
    int index;
    void init() {
        index = 0;
    }
    T* alloc() {
        T* retval = &mempool[index++];
        retval->init();
        return retval;
    }
};

template <typename T>
struct Node {
    T data;
    Node<T> *prev, *next;
};

template <typename T>
struct List {
    typedef Node<T> Node;
    typedef bool(*compare_fn)(const T&, const T&);
    typedef void(*print_fn)(const T&);
    Node *head, *tail;
    Allocator<Node>& allocator;
    compare_fn cmp_fn;
    print_fn prt_fn;
    
    List(Allocator<Node>& allocator, compare_fn cmp_fn, print_fn prt_fn) : allocator(allocator), cmp_fn(cmp_fn), prt_fn(prt_fn) { }

    void init() {
        head = tail = NULL;
    }

    Node* find(Node *target, const T& data) {
        Node *node = target == NULL ? head : target->next;
        while(node) {
            if (cmp_fn(node->data, data)) {
                break;
            }
            node = node->next;
        }
        return node;
    }
    
    void remove(Node* node) {
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
    Node* insert(Node* node, const T& data) {
        Node* new_node = allocator.alloc();
        new_node->data = data;
        new_node->prev = node;
        new_node->next = node->next;
        if (node->next) {
            node->next->prev = new_node;
        }
        node->next = new_node;
    }
    Node* push(const T& data) {
        Node *new_node = allocator.alloc();
        new_node->data = data;
        new_node->prev = tail;
        if (tail) {
            tail->next = new_node;
        }
        tail = new_node;
    }
    void print() {
        Node *node = head;
        while(node) {
            prt_fn(node->data);
            printf(" > ");
            node = node->next;
        }
    }
    void reversal_print() {
        while *node = tail;
        while(node) {
            prt_fn(node->data);
            printf(" > ");
            node = node->prev;
        }
    }
};

struct Point2D {
    int x, y;
};

void print_point2d(const Point2D &p)
{
    printf("(%d, %d)", p.x, p.y);
}

bool compare_point2d(const Point2D &p1, const Point2D &p2)
{
    return p1.x == p2.x && p1.y == p2.y;
}

typedef Node<Point2D> Point2DNode;

Allocator<Point2DNode> allocator;
List<Point2D> list(allocator, compare_point2d, print_point2d);


int main()
{
    allocator.init();
    list.init();
    Point2DNode *node1, *node2, *node3, *node4, *found_node2;
    
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
        print_point2d(found_node2->data);
        printf("\n");
        found_node2->data.x = 9;
        found_node2->data.y = 9;
    }
    
    {
        Point2D p;
        p.x = 9, p.y = 9;
        Point2DNode *node = list.find(NULL, p);
        print_point2d(node->data);
        printf("\n");
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
