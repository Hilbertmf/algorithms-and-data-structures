#include <stdio.h>
#include <stdlib.h>

struct ListNode {
  int val;
  struct ListNode *next;
};

int listSize(struct ListNode* node) {
  int count = 0;
  while(node != NULL) {
    count++;
    node = node->next;
  }
  return count;
}
struct ListNode* middleNode(struct ListNode* node){
  
  int size = listSize(node);
  int mid = size / 2 + 1;
  
  for (int i = 0; i < mid-1; i++) {
    node = node->next;
  }
  
  return node;
}