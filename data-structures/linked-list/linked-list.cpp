#include <iostream>
using namespace std;

struct Node {
  int val;
  struct Node* next;
};


int listSize(struct Node* node) {
  int count = 0;
  while(node != NULL) {
    count++;
    node = node->next;
  }
  return count;
}

Node* middleList(struct Node* head) {
  int size = listSize(head);
  int mid = size / 2 + 1;
  struct Node* node = head;
  for (int i = 0; i < mid-1; i++) {
    node = node->next;
  }
  
  return node;
}

void printList(struct Node* node) {
 	while(node != NULL) {
 		printf("current node: %d\n", node->val);
 		node = node->next;
 	}
}
 
int main() {
	int i;
	struct Node* head = NULL;
	struct Node* second = NULL;
	struct Node* third = NULL;
	struct Node* fourth = NULL;
	struct Node* fifth = NULL;
	
	head = (struct Node*)malloc(sizeof(struct Node));
	second = (struct Node*)malloc(sizeof(struct Node));
	third = (struct Node*)malloc(sizeof(struct Node));
	fourth = (struct Node*)malloc(sizeof(struct Node));
	fifth = (struct Node*)malloc(sizeof(struct Node));
	
	head->val = 1;
	second->val = 2;
	third->val = 3;
	fourth->val = 4;
	fifth->val = 5;
	
	head->next = second;
	second->next = third;
	third->next = fourth;
	fourth->next = fifth;
	fifth->next = NULL;
	
	
	printList(head);
	printf("size of list: %d\n", listSize(head));
  printf("printing middle of list onwards:\n");
  printList(middleList(head));
	return 0;
}