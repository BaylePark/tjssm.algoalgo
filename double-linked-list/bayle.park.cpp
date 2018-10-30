#include <stdio.h>

#define MAX_SIZE 1000000

template <typename T>
struct Allocator
{
    T *alloc()
    {
        T *retval = &mempool[index++];
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
        prev = next = NULL;
    }
    T data;
    Node *prev, *next;
};

template <typename T>
struct List
{
    typedef bool (*compare_fn)(const T &data1, const T &data2);
    typedef void (*print_fn)(const T &data);
    List(Allocator< Node<T> > &allocator, compare_fn cmp_fn, print_fn pnt_fn)
    : allocator(allocator), cmp_fn(cmp_fn), pnt_fn(pnt_fn)
    {
    }
    Node<T> *find(const Node<T> *target_node, const T &data)
    {
        if (target_node == NULL)
        {
            target_node = head;
        }
        else
        {
            target_node = target_node->next;
        }
        Node<T> *retval = NULL;
        while (target_node)
        {
            if (cmp_fn(target_node->data, data))
            {
                retval = (Node<T> *)target_node;
                break;
            }
            target_node = target_node->next;
        }
        return retval;
    }
    void remove(Node<T> *node)
    {
        if (node == head)
        {
            head = node->next;
        }
        if (node == tail)
        {
            tail = node->prev;
        }
        if (node->next)
            node->next->prev = node->prev;
        if (node->prev)
            node->prev->next = node->next;
    }
    Node<T>* insert(Node<T> *target_node, const T &data)
    {
        Node<T> *node = allocator.alloc();
        node->data = data;
        node->next = target_node->next;
        if (target_node->next) {
            target_node->next->prev = node;
        }
        target_node->next = node;
        node->prev = target_node;
        return node;
    }
    Node<T>* push(const T &data)
    {
        Node<T> *node = allocator.alloc();
        node->data = data;
        node->prev = tail;
        if (head == NULL)
            head = node;
        if (tail == NULL)
            tail = node;
        else
        {
            tail->next = node;
            tail = node;
        }
        return node;
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
    Allocator< Node<T> > &allocator;
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
    printf("(%d, %d)", data.x, data.y);
}

Allocator< Node<Point2D> > point2d_allocator;
List<Point2D> point2d_list(point2d_allocator, compare_point2d, print_point2d);

int main()
{
    printf("push p1 node\n");
    Point2D p1;
    p1.x = 1;
    p1.y = 1;
    Node<Point2D>* p1_node = point2d_list.push(p1);
    point2d_list.print();
    
    printf("push p2 node\n");
    Point2D p2;
    p2.x = 1;
    p2.y = 2;
    Node<Point2D>* p2_node = point2d_list.push(p2);
    point2d_list.print();
    
    printf("push p3 node\n");
    Point2D p3;
    p3.x = 2;
    p3.y = 2;
    Node<Point2D>* p3_node = point2d_list.push(p3);
    point2d_list.print();
    
    printf("find p2 node\n");
    Point2D to_find_p2;
    to_find_p2.x = 1;
    to_find_p2.y = 2;
    Node<Point2D> *target_p2 = point2d_list.find(NULL, to_find_p2);
    print_point2d(target_p2->data);
    printf("\n");
    
    printf("insert p4 node after p2 node\n");
    Point2D p4;
    p4.x = 4;
    p4.y = 1;
    Node<Point2D>* p4_node = point2d_list.insert(target_p2, p4);
    point2d_list.print();
    
    printf("remove p1 node\n");
    point2d_list.remove(p1_node);
    point2d_list.print();
    
    printf("remove p3 node\n");
    point2d_list.remove(p3_node);
    point2d_list.print();
    
    printf("remove p4 node\n");
    point2d_list.remove(p4_node);
    point2d_list.print();
}
