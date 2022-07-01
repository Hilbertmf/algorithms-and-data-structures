#include <iostream>
#include <algorithm>
#include <vector>


struct TreeNode {
    int val;
    TreeNode *children;
    TreeNode() : val(0), children(nullptr) {}
    TreeNode(int _val) : val(_val), children(nullptr) {}
    TreeNode(int _val, TreeNode *children) : val(_val), children(children) {}
  };
class NAryTree {
public:
  // Definition for a binary tree node.
  
  
  TreeNode* root;
 
  NAryTree() {
    root = nullptr;
  }

  NAryTree(int _val) {
    struct TreeNode* node = new TreeNode(_val);
    root = node;
  }

  NAryTree(int _val, TreeNode* _children, TreeNode* _right) {
    struct TreeNode* node = new TreeNode(_val, _children);
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

    std::cout << root->val << " ";
    inOrderTraversal(root->children);
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
    // levelOrderTraversal(root->left, level, nodes);
    // levelOrderTraversal(root->right, level, nodes);
  }
  
  bool contains(int val) { return contains(this->root, val); }

  bool contains(TreeNode* root, int val) {
    if(root == nullptr) return false;
    
    if(val == root->val)
      return true;
    // else if(val > root->val)
      // contains(root->right, val);
    // else
      // contains(root->left, val);
  }

  void insert(int _val, TreeNode* parent) {
    struct TreeNode* node = new TreeNode(_val);
    parent->children = node;
    std::cout << "inserting " << _val << "..." << std::endl;
    
    if(this->root == nullptr)
      root = node;
    else
      
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
  int n, parent;
  int option = 1;
  NAryTree tree;
  while (option != 0) {
    std::cout << "options: insert: 1 | insert multiple: 2 | traversals: in order: 3 | pre order: 4 | post order: 5 | print by level: 6" << std::endl;
    std::cout << "exit: 0" << std::endl;
    std::cin >> option;
    if(option == 1) {
      std::cout << "input number to insert and its parent:" << std::endl;
      std::cin >> n >> parent;
      struct TreeNode* parentNode = new TreeNode(parent);
      tree.insert(n, parentNode);
    }
    else if(option == 2) {
      std::cout << "num of elements to insert:" << std::endl;
      std::cin >> n;
      std::cout << "elements to insert and their parent:" << std::endl;
      while (n--) {
        int elem;
        std::cin >> elem >> parent;
        struct TreeNode* parentNode = new TreeNode(parent);
        tree.insert(elem, parentNode);
      }
    }
    else if(option == 3) {
      tree.inOrderTraversal();
    }
    
    else if(option == 6) {
      tree.printByLevel();
    }
  }
  
  return 0;
}