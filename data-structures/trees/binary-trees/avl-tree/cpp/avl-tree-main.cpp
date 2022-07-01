#include <bits/stdc++.h>
#include "avl-tree.h"
using namespace std;

int main() {
  int option = -1;
  int val;
  AVLTree tree;
  

  while(option != 0) {
    cout << "Which operation you wanna do?" << endl;
    cout << "1. Insert node" << endl;
    cout << "2. Search node" << endl;
    cout << "3. Delete node" << endl;
    cout << "4. Print values in order" << endl;
    cout << "5. Print values pre order" << endl;
    cout << "6. Print values post order" << endl;
    cout << "7. Print tree rotated 90º counterclockwise" << endl;
    cout << "0. Exit" << endl;
    cout << "Select Option number: " << endl;
    cin >> option;

    TreeNode *node = new TreeNode();
    switch (option) {
    case 0:
      cout << "\nExiting...\n" << endl;
      break;
    case 1:
      cout << "Pass an integer value to insert:" << endl;
      cin >> val;
      cout << "\nInserting...\n" << endl;
      node->value = val;
      tree.root = tree.insertRecursive(tree.root, node);
      // code
      break;
    case 2:
      cout << "Pass a node to search:" << endl;
      cin >> val;
      cout << "\nSearching..." << endl;
      if(tree.contains(val))
        cout << "Value found!\n" << endl;
        
      else
        cout << val << "is not present in the tree.\n" << endl;
      // code
      break;
    case 3:
      cout << "Pass a node to delete:" << endl;
      cin >> val;
      if(tree.contains(val)) {
        cout << "\nDeleting...\n" << endl;
        tree.erase(tree.root, val);
      }
      else {
        cout << "\nValue not found\n" << endl;
      }
      break;
    case 4:
      cout << "\n";
      tree.printInOrder();
      cout << "\n";
      break;
    case 5:
      cout << "\n";
      tree.printPreOrder();
      cout << "\n";
      break;
    case 6:
      cout << "\n";
      tree.printPostOrder();
      cout << "\n";
      break;
    case 7:
      cout << "\n";
      tree.printCounterClockwise(tree.root, 5);
      cout << "\n";
      break;
    default:
      cout << "\nEnter proper option number\n" << endl;
      break;
    }
   
  }
  
  return 0;   
}
  