#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
using namespace std;

#define MAX_SIZE 10000
#define TRUE 1
#define FALSE 0

typedef struct tagPoint {
   int y;
   int x;
}Point;

typedef struct tagNode {
   Point p;
   tagNode* prev;
   tagNode* next;
}Node;
Node mDB[MAX_SIZE];
int mDBcur = 0;

Node* head = NULL;
Node* tail = NULL;

Node* createNode(Point p) {
   Node* newNode = &mDB[mDBcur++];
   newNode->p = p;
   newNode->next = NULL;
   return newNode;
}

void insertNode(int y, int x) {
   Point p;
   p.x = x;
   p.y = y;
   Node* newNode = createNode(p);
   if (head == NULL) {
      tail = head = newNode;
   }
   else {
      if (tail == head) {
         tail = newNode;
         head->next = tail;
         tail->prev = head;
      }
      else {
         tail->next = newNode;
         newNode->prev = tail;
         tail = newNode;
      }
   }
}

void printAll() {
   Node* cur = head;
   while (cur) {
      cout << "(" << cur->p.y << "," << cur->p.x << ")";
      if (cur->next)
         cout << ",";
      cur = cur->next;
   }
   cout << endl;
}

void ReversalPrint() {
   Node* cur = tail;
   while (cur) {
      cout << "(" << cur->p.y << "," << cur->p.x << ")";
      if (cur->prev)
         cout << ",";
      cur = cur->prev;
   }
   cout << endl;
}

Node* find(int y, int x) {
   Point p;
   p.y = y;
   p.x = x;
   Node* cur = head;
   while (cur) {
      if (p.x == cur->p.x && p.y == cur->p.y) {
         return cur;
      }
      cur = cur->next;
   }
   return NULL;
}

void remove(Node* d) {
   Node* temp = d;
   if (temp->prev)
      temp->prev->next = d->next;
   if (temp->next)
      temp->next->prev = d->prev;
   d->next = NULL;
   d->prev = NULL;
}

void insert(Node* i, int y, int x) {
   Point p;
   p.y = y;
   p.x = x;
   Node* newNode = createNode(p);
   if (i->next)
      i->next->prev = newNode;
   newNode->next = i->next;
   newNode->prev = i;
   i->next = newNode;
}

void printNode(Node* n) {
   cout << "(" << n->p.y << "," << n->p.x << ")" << endl;
}


int isInsert(int y, int x, int newY, int newX) {
   if (y > newY)
      return TRUE;
   if (y < newY)
      return FALSE;

   if (x > newX)
      return TRUE;
   if (x < newX)
      return FALSE;
   return FALSE;
}

void sortInsert(Node *nNode) {
   if (head == NULL) {
      tail = head = nNode;
      return;
   }
   Node* before = NULL;
   for (Node* cur = head; cur; cur = cur->next) {
      if (isInsert(cur->p.y, cur->p.x, nNode->p.y, nNode->p.x) == TRUE) {
         if (cur->prev) {
            cur->prev->next = nNode;
         }
         nNode->prev = cur->prev;
         
         nNode->next = cur;
         cur->prev = nNode;
         if (cur == tail)
            tail = nNode;
         return;
      }
      before = cur;
   }
   before->next = nNode;
   nNode->prev = before;
   tail = nNode;
}

void sortNode() {
   int size = 0;
   Node* arr[MAX_SIZE];
   Node* cur = head;
   while (cur) {
      arr[size++] = cur;
      cur = cur->next;
   }

   tail = head = NULL;
   for (int i = 0; i < size; i++) {
      Node* temp = arr[i];
      temp->prev = NULL;
      temp->next = NULL;
      sortInsert(temp);
   }
}




int main() {
   insertNode(1, 1);
   printAll();
   ReversalPrint();
   insertNode(1, 2);
   printAll();
   ReversalPrint();
   insertNode(2, 2);
   printAll();
   ReversalPrint();
   Node* fNode = find(1, 2);
   printNode(fNode);
   fNode->p.x = 9;
   fNode->p.y = 9;
   printNode(fNode);
   ReversalPrint();
   insert(fNode, 4, 1);
   printAll();
   ReversalPrint();
   remove(fNode);
   printAll();
   ReversalPrint();
   insertNode(5, 8);
   insertNode(5, 7);
   insertNode(5, 9);
   sortNode();
   printAll();
   ReversalPrint();
   return 0;
}