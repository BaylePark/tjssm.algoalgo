#include <iostream>

#define MAX_SIZE 1000000

template <typename T>
struct Allocator
{
    T *alloc()
    {
        T *retval = mempool[index++];
        retval->init();
        return retval;
    }
    T mempool[MAX_SIZE];
    int index;
};

template <typename T>
struct Node
{
    void init()
    {
        prev = next = nullptr;
    }
    T data;
    Node *prev, *next;
};

template <typename T>
struct List
{
    typedef bool (*compare_fn)(const T &data1, const T &data2);
    typedef void (*print_fn)(const T &data);
    List(Allocator<Node<T>> &allocator, compare_fn cmp_fn, print_fn pnt_fn)
        : allocator(allocator), cmp_fn(cmp_fn), pnt_fn(pnt_fn)
    {
    }
    Node<T> *find(const Node<T> *target_node, const T &data)
    {
        if (target_node == nullptr)
        {
            target_node = head;
        }
        else
        {
            target_node = target_node->next;
        }
        Node<T> *retval = nullptr;
        while (target_node)
        {
            if (cmp_fn(target_node->data, data))
            {
                retval = target_node;
                break;
            }
            target_node = target_node->next;
        }
        return retval;
    }
    void remove(Node<T> *node)
    {
        if (node == head)
            head = node->next;
        if (node == tail)
            tail = node->prev;
        if (node->next)
            node->next->prev = node->prev;
        if (node->prev)
            node->prev->next = node->next;
    }
    void insert(Node<T> *target_node, const T &data)
    {
        Node<T> *node = allocator.alloc();
        node->data = data;
        target_node->next = node;
        node->prev = target_node;
    }
    void push(const T &data)
    {
        Node<T> *node = allocator.alloc();
        node->data = data;
        node->prev = tail;
        if (head == nullptr)
            head = node;
        if (tail == nullptr)
            tail = node;
        else
        {
            tail->next = node;
            tail = node;
        }
    }
    void print()
    {
        const Node<T> *target_node = head;
        while (target_node)
        {
            pnt_fn(target_node->data);
            printf(" -> ");
            target_node = target_node->next;
        }
        printf("\n");
    }

    Node<T> *head, *tail;
    Allocator<Node<T>> &allocator;
    compare_fn cmp_fn;
    print_fn pnt_fn;
};

struct Point2D
{
    int x, y;
};

static bool compare_point2d(const Point2D &data1, const Point2D &data2)
{
    if (data1.x == data2.x && data1.y == data2.y)
        return true;
    return false;
}
static void print_point2d(const Point2D &data)
{
    printf("%d %d", data.x, data.y);
}

Allocator<Node<Point2D>> point2d_allocator;
List<Point2D> point2d_list(point2d_allocator, compare_point2d, print_point2d);

int main()
{
    Point2D p1;
    p1.x = 1;
    p1.y = 1;
    point2d_list.push(p1);
    point2d_list.print();

    Point2D p2;
    p2.x = 1;
    p2.y = 2;
    point2d_list.push(p2);
    point2d_list.print();

    Point2D p3;
    p3.x = 2;
    p3.y = 2;
    point2d_list.push(p3);
    point2d_list.print();

    Point2D to_find_p1;
    to_find_p1.x = 1;
    to_find_p1.y = 2;
    Node<Point2D>* target_p1 = point2d_list.find(nullptr, to_find_p1);
    print_point2d(target_p1->data);
    
}