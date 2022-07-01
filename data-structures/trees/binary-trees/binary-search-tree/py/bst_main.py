import bst

def main():
  option = -1
  tree = BST()

  while option != 0:
    print("Which operation you wanna perform?")
    print("1. Insert node")
    print("2. Search node")
    print("3. Delete node")
    print("4. Print values in order")
    print("5. Print values pre order")
    print("6. Print values post order")
    print("7. Print tree rotated 90 degrees counterclockwise")
    print("0. Exit")
    option = int(input("Select Option number: "))

    if option == 0:
      print("\nExiting...\n", end='')
    elif option == 1:
      val = int(input("Pass an integer value to insert: "))
      print("\nInserting...\n", end='')
      tree.insert(val)
      # insert node
    elif option == 2:
      val = int(input("Pass an integer value to search: "))
      print("\nSearching...\n", end='')
      if tree.contains(val, tree.root):
        print("Value found!\n", end='')
      else:
        print("{} is not present in the tree.\n\n".format(val), end='')
    elif option == 3:
      val = int(input("Pass a node to delete:"))
      if tree.contains(val, tree.root):
        print("\nDeleting...\n")
        tree.root = tree.deleteNode(tree.root, val)
      else:
        print("\nValue not found\n")
    elif option == 4:
      print("\n", end='')
      print("In order:")
      tree.printInOrder()
      print("\n", end='')
    elif option == 5:
      print("\n", end='')
      print("Pre order:")
      tree.printPreOrder()
      print("\n", end='')
    elif option == 6:
      print("\n", end='')
      print("Post order:")
      tree.printPostOrder()
      print("\n", end='')
    elif option == 7:
      print("--------------------------------------------------------")
      print("Tree rotated 90 degrees counterclockwise:\n\n", end='')
      tree.printCounterClockwise(tree.root, 5)
      print("\n\n--------------------------------------------------------\n")
    else:
      print("\nEnter proper option number\n", end='')


if __name__ == "__main__":
  main()

