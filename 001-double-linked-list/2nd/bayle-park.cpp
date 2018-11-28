#include <stdio.h>

const int kMaxSize = 100000;

template <typename T>
struct Allocator
{
    Allocator() {}
    void init()
    {
        index = 0;
    }
    T *alloc()
    {
        T *retval = &mempool[index++];
        retval->init();
        return retval;
    }
    int index;
    T mempool[kMaxSize];
};

template <typename T>
struct Node
{
    T data;
    Node *prev, *next;
    void init()
    {
        prev = next = NULL;
    }
};

template <typename T>
struct List
{
    typedef void (*printfn)(const T &);
    typedef bool (*comparefn)(const T &, const T &);
    List(Allocator<Node<T> > &allocator) : allocator(allocator)
    {
    }
    Node<T> *find(Node<T> *target_node, const T &value)
    {
        Node<T> *node = target_node ? target_node->next : head;
        while (node)
        {
            if (cmpfn(node->data, value))
                break;
            node = node->next;
        }
        return node;
    }
    void remove(Node<T> *node)
    {
        if (node == NULL)
            return;
        if (node == head)
        {
            head = node->next;
        }
        if (node == tail)
        {
            tail = node->prev;
        }
        if (node->next)
        {
            node->next->prev = node->prev;
        }
        if (node->prev)
        {
            node->prev->next = node->next;
        }
        count--;
    }
    Node<T> *insert(Node<T> *target_node, const T &value)
    {
        if (target_node == NULL)
            return NULL;
        Node<T> *node = allocator.alloc();
        node->data = value;
        node->prev = target_node;
        if (target_node->next)
        {
            target_node->next->prev = node;
        }
        target_node->next = node;
        count++;
        return node;
    }
    Node<T> *push(const T &value)
    {
        Node<T> *node = allocator.alloc();
        node->data = value;
        node->prev = tail;
        if (head == NULL)
        {
            head = node;
        }
        if (tail != NULL)
        {
            tail->next = node;
        }
        
        tail = node;
        count++;
        return node;
    }
    int get_count()
    {
        return count;
    }
    void set_comparefn(comparefn cmpfn)
    {
        this->cmpfn = cmpfn;
    }
    void set_printfn(printfn pfn)
    {
        this->pfn = pfn;
    }
    void print()
    {
        Node<T> *node = head;
        while (node)
        {
            pfn(node->data);
            printf(", ");
            node = node->next;
        }
        printf("\n");
    }
    void reversal_print()
    {
        Node<T> *node = tail;
        while (node)
        {
            pfn(node->data);
            printf(", ");
            node = node->prev;
        }
        printf("\n");
    }
    void init()
    {
        count = 0;
        head = tail = NULL;
    }
    
    comparefn cmpfn;
    printfn pfn;
    Allocator<Node<T> > &allocator;
    Node<T> *head, *tail;
    int count;
};

struct Point2D
{
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
List<Point2D> list(allocator);

int main()
{
    allocator.init();
    list.init();
    list.set_comparefn(compare_point2d);
    list.set_printfn(print_point2d);
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
