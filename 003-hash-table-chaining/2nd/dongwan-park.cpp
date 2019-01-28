#include <iostream>
#define MAX_TABLE 1007
using namespace std;

typedef struct tagHash {
   char str[100];
   tagHash *next = NULL;
}Node;

Node* Head[MAX_TABLE];

void print_(Node* cur);

unsigned long hashKey(const char *str)
{
   unsigned long hash = 5381;
   int c;
   while (c = *str++)
   {
      hash = (((hash << 5) + hash) + c) % MAX_TABLE;
   }
   return hash % MAX_TABLE;
}

Node* createNode(char *str) {
   Node* newNode = (Node*)malloc(sizeof(Node));
   newNode->next = NULL;
   strcpy(newNode->str, str);
   return newNode;
}

void insertHash(char *str, char *data) {
   int key = hashKey(str);
   Node* newNode = createNode(data);

   if (Head[key] == NULL) {
      Head[key] = newNode;
   }
   else {
      newNode->next = Head[key];
      Head[key] = newNode;
   }
}

void printHash(char *str) {
   int key = hashKey(str);
   if (Head[key] == NULL) {
      cout << "EMPTY HASH TABLE - printHash" << endl;
   }
   else {
      Node* cur = Head[key];
      print_(cur);
      cout << endl;
   }
}

void print_(Node* cur) {
   if (cur == NULL) {
      return;
   }
   print_(cur->next);
   cout << cur->str<<" ";
}

void deleteHash(char *str, char *data) {
   int key = hashKey(str);
   Node* delNode = NULL;
   if (Head[key] == NULL) {
      cout << "EMPTY HASH TABLE - deleteHash" << endl;
   }
   else if(strcmp(Head[key]->str, data) == 0){
      delNode = Head[key];
      Head[key] = Head[key]->next;
   }
   else {
      Node* cur = Head[key];
      while (cur->next) {
         if (strcmp(cur->next->str, data) == 0) {
            delNode = cur->next;
            cur->next = cur->next->next;
            break;
         }
      }
   }
   free(delNode);
}

int main() {
   insertHash("MSFT", "MicrosoftCorporation");
   insertHash("JAVA", "SunMicrosystems");
   insertHash("REDH", "RedHatLinux");
   insertHash("APAC", "ApacheOrg");
   insertHash("ZYMZZ", "UnisysOpsCheck");
   insertHash("IBM", "IBMLtd.");
   insertHash("ORCL", "OracleCorporation");
   insertHash("CSCO", "CiscoSystems,Inc.");
   insertHash("GOOG", "GoogleInc.");
   insertHash("YHOO", "Yahoo!Inc.");
   insertHash("NOVL", "Novell,Inc.");
   insertHash("JAVA", "Oracle");
   insertHash("JAVA", "OpenJDK");

   printHash("MSFT");
   printHash("JAVA");
   printHash("REDH");
   printHash("APAC");
   printHash("ZYMZZ");
   printHash("IBM");
   printHash("ORCL");
   printHash("CSCO");
   printHash("GOOG");
   printHash("YHOO");
   printHash("NOVL");

   cout << endl;
   cout << "DELETE ORACLE" << endl;
   cout << endl;
   deleteHash("JAVA", "Oracle");

   printHash("MSFT");
   printHash("JAVA");
   printHash("REDH");
   printHash("APAC");
   printHash("ZYMZZ");
   printHash("IBM");
   printHash("ORCL");
   printHash("CSCO");
   printHash("GOOG");
   printHash("YHOO");
   printHash("NOVL");
   return 0;
}