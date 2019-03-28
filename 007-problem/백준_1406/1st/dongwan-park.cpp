#include <iostream>
using namespace std;
#define MAX_SIZE 600000
#define MAX_INPUT 100000
// L 커서 왼쪽 ( 맨앞 무시 )
// D 커서 오른쪽 ( 맨뒤 무시 )
// B 커서 왼쪽 문자 삭제
// P $ $를 왼쪽에 추가함

typedef struct tagNode {
   char ch;
   tagNode* prev;
   tagNode* next;
}Node;
int dbCur;
Node mDB[MAX_SIZE];
Node *mNode;
Node *mHead;

int main() {
   mHead = &mDB[dbCur++];
   mNode = mHead;
   //mRear = mNode = mHead = mNode;
   int inputIdx = 0;
   char input[MAX_INPUT];
   scanf("%s", input);
   while (input[inputIdx]) {
      Node *temp = &mDB[dbCur++];
      temp->next = NULL;
      temp->ch = input[inputIdx++];
      temp->prev = mNode;
      mNode->next = temp;
      mNode = mNode->next;
   }

   int N;
   scanf("%d", &N);
   for (int n = 0; n < N; n++) {
      getchar();
      char ch = getchar();
      if (ch == 'L') {
         if (mNode->prev) {
            mNode = mNode->prev;
         }
      }
      else if (ch == 'D') {
         if (mNode->next) {
            mNode = mNode->next;
         }
      }
      else if (ch == 'B') {
         Node* beforeNode = mNode->prev;
         Node* nextNode = mNode->next;
         if (nextNode != NULL || beforeNode != NULL) {
            if (mNode == mHead) {
               //
            }
            else if (nextNode == NULL) {
               beforeNode->next = NULL;
               mNode = beforeNode;
            }
            else {
               beforeNode->next = nextNode;
               nextNode->prev = beforeNode;
               mNode = beforeNode;
            }
         }
      }
      else {
         char ch2 = getchar();
         char ch3 = getchar();
         Node*temp = &mDB[dbCur++];
         temp->ch = ch3;
         temp->next = mNode->next;
         temp->prev = mNode;
         if (mNode->next != NULL) {
            mNode->next->prev = temp;
         }
         mNode->next = temp;
         mNode = temp;
      }
   }
   while (mHead->next) {
      printf("%c", mHead->next->ch);
      mHead = mHead->next;
   }
   printf("\n");
   return 0;
}