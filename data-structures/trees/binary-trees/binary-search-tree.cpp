#include <iostream>
#include <algorithm>
#include <vector>

class BinarySearchTree {
public:
  // Definition for a binary tree node.
  struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int _val) : val(_val), left(nullptr), right(nullptr) {}
    TreeNode(int _val, TreeNode *left, TreeNode *right) : val(_val), left(left), right(right) {}
  };
  
  TreeNode* root;
 
  BinarySearchTree() {
    root = nullptr;
  }

  BinarySearchTree(int _val) {
    struct TreeNode* node = new TreeNode(_val);
    root = node;
  }

  BinarySearchTree(int _val, TreeNode* _left, TreeNode* _right) {
    struct TreeNode* node = new TreeNode(_val, _left, _right);
    root = node;
  }

  void inOrderTraversal() { 
    std::cout << "in order:" << std::endl;
    std::cout << "[ ";
    inOrderTraversal(this->root);
    std::cout << "]" << std::endl;
  }

  void inOrderTraversal(TreeNode* root) {
    if(root == nullptr) return;

    inOrderTraversal(root->left);
    std::cout << root->val << " ";
    inOrderTraversal(root->right);
  }

  void preOrderTraversal() { 
    std::cout << "pre order:" << std::endl;
    std::cout << "[ ";
    preOrderTraversal(this->root);
    std::cout << "]" << std::endl;
  }

  void preOrderTraversal(TreeNode* root) {
    if(root == nullptr) return;

    std::cout << root->val << " ";
    preOrderTraversal(root->left);
    preOrderTraversal(root->right);
  }

  void postOrderTraversal() { 
    std::cout << "post order:" << std::endl;
    std::cout << "[ ";
    postOrderTraversal(this->root);
    std::cout << "]" << std::endl;
  }

  void postOrderTraversal(TreeNode* root) {
    if(root == nullptr) return;

    postOrderTraversal(root->left);
    postOrderTraversal(root->right);
    std::cout << root->val << " ";
  }

  void levelOrderTraversal(std::vector<std::vector<int>>& nodes) { 
    std::cout << "by level:" << std::endl;
    levelOrderTraversal(this->root, 0, nodes); 
  }

  void levelOrderTraversal(TreeNode* root, int level, std::vector<std::vector<int>>& nodes) {
    if(root == nullptr) return;
    
    level++;
    if(nodes.size() < level) {
      std::vector<int> vec;
      nodes.push_back(vec);
    }
    nodes[level-1].push_back(root->val);
    levelOrderTraversal(root->left, level, nodes);
    levelOrderTraversal(root->right, level, nodes);
  }
  
  bool contains(int val) { return contains(this->root, val); }

  bool contains(TreeNode* root, int val) {
    if(root == nullptr) return false;
    
    if(val == root->val)
      return true;
    else if(val > root->val)
      contains(root->right, val);
    else
      contains(root->left, val);
  }
  
  void traverseBST(TreeNode* root, TreeNode* node, int val) {
    if(val > root->val) {
      if(root->right != nullptr)
        traverseBST(root->right, node, val);
      else {
        root->right = node;
        return;
      }
    }
    else {
      if(root->left != nullptr) 
        traverseBST(root->left, node, val);
      else {
        root->left = node;
        return;
      }
    }
  }

  void insert(int _val) {
    std::cout << "inserting " << _val << "..." << std::endl;
    struct TreeNode* node = new TreeNode(_val);
    if(this->root == nullptr)
      root = node;
    else
      traverseBST(this->root, node, _val);
  }

  void printByLevel() {
    std::vector<std::vector<int>> levels;
    this->levelOrderTraversal(this->root, 0, levels);
    for(int i = 0; i < levels.size(); i++) {
      std::cout << "nodes in lv " << i << ": ";
      for(int j = 0; j < levels[i].size(); j++) {
        std::cout << levels[i][j] << " ";
      }
      std::cout << std::endl;
    }
  }
};

int main() {
  int n;
  int option = 1;
  BinarySearchTree tree;
  while (option != 0) {
    std::cout << "options: insert: 1 | insert multiple: 2 | traversals: in order: 3 | pre order: 4 | post order: 5 | print by level: 6" << std::endl;
    std::cout << "exit: 0" << std::endl;
    std::cin >> option;
    if(option == 1) {
      std::cout << "input number to insert:" << std::endl;
      std::cin >> n;
      tree.insert(n);
    }
    else if(option == 2) {
      std::cout << "num of elements to insert:" << std::endl;
      std::cin >> n;
      std::cout << "elements to insert:" << std::endl;
      while (n--) {
        int elem;
        std::cin >> elem;
        tree.insert(elem);
      }
    }
    else if(option == 3) {
      tree.inOrderTraversal();
    }
    else if(option == 4) {
      tree.preOrderTraversal();
    }
    else if(option == 5) {
      tree.postOrderTraversal();
    }
    else if(option == 6) {
      tree.printByLevel();
    }
  }
  
  return 0;
}