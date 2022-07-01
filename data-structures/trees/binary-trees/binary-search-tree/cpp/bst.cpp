#include <bits/stdc++.h>
using namespace std;
#define SPACE 10

class TreeNode {
  public:
    int value;
    TreeNode *left, *right;

    TreeNode() {
      value = 0;
      left = nullptr;
      right = nullptr;
    }

    TreeNode(int val) {
      value = val;
      left = nullptr;
      right = nullptr;
    }
};

class BST {
  public:
    TreeNode *root;

    BST() {
      root = nullptr;
    }
    
    bool isEmpty() {
      return root == nullptr;
    }

    void print2D(TreeNode *r, int space) {
      if(r == nullptr) return;

      space += SPACE;
      print2D(r->right, space);
      cout << endl;
      for(int i = SPACE; i < space; i++) {
        cout << " ";
      }
      cout << r->value << endl;
      print2D(r->left, space);
    }

    void insert(int val) {
      std::cout << "inserting " << val << "..." << std::endl;
      struct TreeNode* node = new TreeNode(val);
      if(this->root == nullptr) {
        root = node;
        std::cout << "Value inserted as root node!" << std::endl;
      }
      else {
        TreeNode* curr = root;
        
        while (curr != nullptr) {
          if(curr->value == val) {
            std::cout << "No duplicates allowed, insert another value" << std::endl;
            return;
          }
          else {
            if(val < curr->value) { // left
              if(curr->left != nullptr) {
                curr = curr->left;
              }
              else {
                curr->left = node;
                std::cout << "inserted " << val << " as left child of " << node->value << " node" << std::endl;
                return;
              }
            }
            else { // right
              if(curr->right != nullptr) {
                curr = curr->right;
              }
              else {
                curr->right = node;
                std::cout << "inserted " << val << " as right child of " << node->value << " node" << std::endl;
                return;
              }
            }
          }
        }
      }
    }
    
    void insertNode(TreeNode *new_node) {

    }

    void printPreOrder(TreeNode *r) {
      
    }

    void printPreOrder(TreeNode *r) {
      
    }

    void printPreOrder(TreeNode *r) {
      
    }

    TreeNode* search(TreeNode *r, int v) {

    }

    TreeNode* erase(TreeNode *r, int v) {

    }
};