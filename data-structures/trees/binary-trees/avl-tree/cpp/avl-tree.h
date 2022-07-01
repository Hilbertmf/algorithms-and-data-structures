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

class AVLTree {
  public:
    TreeNode *root;

    AVLTree() {
      root = nullptr;
    }
    
    bool isEmpty() {
      return root == nullptr;
    }

    bool contains(int val) {
      return contains(this->root, val);
    }

    bool contains(TreeNode* root, int val) {
      if(root == nullptr) return false;
      if(val == root->value) return true;

      if(val > root->value)
        contains(root->right, val);
      else
        contains(root->left, val);
    }    
// print methods
    void printCounterClockwise(TreeNode *r, int space) {
      if(r == nullptr) return;

      space += SPACE;
      printCounterClockwise(r->right, space);
      cout << endl;
      for(int i = SPACE; i < space; i++) {
        cout << " ";
      }
      cout << r->value << endl;
      printCounterClockwise(r->left, space);
    }

    void printInOrder() { 
      std::cout << "In order:" << std::endl;
      std::cout << "[ ";
      printInOrder(this->root);
      std::cout << "]" << std::endl;
    }
    
    void printInOrder(TreeNode* root) {
      if(root == nullptr) return;

      printInOrder(root->left);
      std::cout << root->value << " ";
      printInOrder(root->right);
    }
    
    void printPreOrder() { 
      std::cout << "Pre order:" << std::endl;
      std::cout << "[ ";
      printPreOrder(this->root);
      std::cout << "]" << std::endl;
    }

    void printPreOrder(TreeNode* root) {
      if(root == nullptr) return;

      std::cout << root->value << " ";
      printPreOrder(root->left);
      printPreOrder(root->right);
    }

    void printPostOrder() { 
      std::cout << "Post order:" << std::endl;
      std::cout << "[ ";
      printPostOrder(this->root);
      std::cout << "]" << std::endl;
    }

    void printPostOrder(TreeNode* root) {
      if(root == nullptr) return;

      printPostOrder(root->left);
      printPostOrder(root->right);
      std::cout << root->value << " ";
    }
// -----------------------------------------------------

    int height(TreeNode *node) {
      if(node == nullptr) return -1;

      int leftHeight = height(node->left);
      int rightHeight = height(node->right);
      if(leftHeight > rightHeight)
        return leftHeight + 1;
      else
        return rightHeight + 1;
    }
    
    int getBalanceFactor(TreeNode *node) {
      if(node == nullptr) return -1;
      return height(node->left) - height(node->right);
    }

    TreeNode* rightRotate(TreeNode *x) {
      TreeNode *y = x->left;
      TreeNode *subtree = y->right;
      // perform rotation
      y->right = x;
      x->left = subtree;
      return y;
    }
    
    TreeNode* leftRotate(TreeNode *x) {
      TreeNode *y = x->right;
      TreeNode *subtree = y->left;
      // perform rotation
      y->left = x;
      x->right = subtree;
      return y;
    }
    
    void insert(int val) {
      std::cout << "inserting " << val << "..." << std::endl;
      TreeNode* node = new TreeNode(val);
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
                std::cout << "inserted " << val << " as left child of " << curr->value << " node" << std::endl;
                return;
              }
            }
            else { // right
              if(curr->right != nullptr) {
                curr = curr->right;
              }
              else {
                curr->right = node;
                std::cout << "inserted " << val << " as right child of " << curr->value << " node" << std::endl;
                return;
              }
            }
          }
        }
      }
    }

    TreeNode* insertRecursive(TreeNode *curr, TreeNode *newNode) {
      if(curr == nullptr) {
        curr = newNode;
        std::cout << curr->value << " inserted sucessfully" << std::endl;
        return curr;
      }
      if(newNode->value < curr->value) {
        curr->left = insertRecursive(curr->left, newNode);
      }
      else if(newNode->value > curr->value) {
        curr->right = insertRecursive(curr->right, newNode);
      }
      else {
        cout << "No duplicates allowed, insert another value" << endl;
        return curr;
      }
      int bf = getBalanceFactor(curr);
      if(bf > 1 && newNode->value < curr->left->value) { // left left
        return rightRotate(curr);
      }
      else if(bf < -1 && newNode->value > curr->right->value) { // right right
        return leftRotate(curr);
      }
      else if(bf > 1 && newNode->value > curr->left->value) { // left right
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
      }
      else if(bf < -1 && newNode->value < curr->right->value) { // right left
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
      }
      
      return curr;
    }

    TreeNode* nextSucessor(TreeNode* root) {
      if(root == nullptr) return root;
      // smallest value in right
      TreeNode* curr = root;
      curr = curr->right;
      while(curr != nullptr && curr->left != nullptr) {
        curr = curr->left;
      }
      return curr;
    }
    
    TreeNode* lastPredecessor(TreeNode* root) {
      if(root == nullptr) return root;
      // greatest value in left
      TreeNode* curr = root;
      curr = curr->left;
      while(curr != nullptr && curr->right != nullptr) {
        curr = curr->right;
      }
      return curr;
    }
    
    TreeNode* erase(TreeNode *curr, int val) {
      if(curr == nullptr) return curr;

      else if(val < curr->value) {
        curr->left = erase(curr->left, val);
      }
      else if(val > curr->value) {
        curr->right = erase(curr->right, val);
      }
      else { // val == curr->value
        if(curr->left == nullptr) { // only right child
          TreeNode *tmp = curr->right; // or no child
          delete curr;
          return tmp;
        }
        else if(curr->right == nullptr) { // left child
          TreeNode *tmp = curr->left;
          delete curr;
          return tmp;
        }
        else { // 2 children
          // replace w/ next sucessor or last pre
          TreeNode *tmp;
          if(nextSucessor(curr) != nullptr) {
            tmp = nextSucessor(curr);
            curr->value = tmp->value;
            curr->right = erase(curr->right, tmp->value);
          }
          else {
            tmp = lastPredecessor(curr);
            curr->value = tmp->value;
            curr->left = erase(curr->left, tmp->value);
          }
        }
      }

      int bf = getBalanceFactor(curr);

      if(bf >= 2 && getBalanceFactor(curr->left) >= 0) { // left left
        return rightRotate(curr);
      }
      else if(bf >= 2 && getBalanceFactor(curr->left) == -1) { // left right
        curr->left = leftRotate(curr->left);
        return rightRotate(curr);
      }
      else if(bf <= -2 && getBalanceFactor(curr->right) <= 0) { // right right
        return leftRotate(curr);
      }
      else if(bf <= -2 && getBalanceFactor(curr->right) == 1) { // right left
        curr->right = rightRotate(curr->right);
        return leftRotate(curr);
      }
      return curr;
    }

};

/*
  
 7  
2  15
  
bf=2
bf-left = 1

x=15
y=7
sub=null
TreeNode* rightRotate(TreeNode *x) {
      TreeNode *y = x->left;
      TreeNode *subtree = y->right;
      // perform rotation
      y->right = x;
      x->left = subtree;
      return y;
    }
*/