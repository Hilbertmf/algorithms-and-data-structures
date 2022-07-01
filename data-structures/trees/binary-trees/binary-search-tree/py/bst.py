SPACE = 10
class TreeNode:

  def __init__(self, val=0, left=None, right=None):
    self.value = val
    self.left = left
    self.right = right
  
class BST:

  def __init__(self, root=None):
    self.root = root
  
  def isEmpty(self):
    return self.root == None
  
  def contains(self, val, root):
    if root == None:
      return False
    if val == self.root.value:
      return True

    if val > self.root.value:
      self.contains(val, root.right)
    else:
      self.contains(val, root.left)

# print methods
  def printCounterClockwise(self, root, space):
    if root == None:
      return

    space += SPACE
    self.printCounterClockwise(root.right, space)
    print("\n", end='')
    for i in range((space - SPACE)):
      print(" ", end='')
    
    print(root.value, end='')
    self.printCounterClockwise(root.left, space)
  
  def traverseInOrder(self, root):
    if root == None:
      return
    self.traverseInOrder(root.left)
    print("{} ".format(root.value), end='')
    self.traverseInOrder(root.right)

  def printInOrder(self):
    print("[ ", end='')
    self.traverseInOrder(self.root)
    print("]\n", end='')
  
  def traversePreOrder(self, root):
    if root == None:
      return
    print("{} ".format(root.value), end='')
    self.traversePreOrder(root.left)
    self.traversePreOrder(root.right)
  
  def printPreOrder(self):
    print("[ ", end='')
    self.traversePreOrder(self.root)
    print("]\n", end='')
  
  def traversePostOrder(self, root):
    if root == None:
      return
    self.traversePostOrder(root.left)
    self.traversePostOrder(root.right)
    print("{} ".format(root.value), end='')
  
  def printPostOrder(self):
    print("[ ", end='')
    self.traversePostOrder(self.root)
    print("]\n", end='')
# -----------------------------------------
# insert
  def insert(self, val):
    print("inserting {}...\n".format(val), end='')
    node = TreeNode(val)

    if self.root == None:
      self.root = node
      print("Value inserted as root node!", end='')
    
    else:
      curr = self.root
      
      while curr != None:
        if curr.value == val:
          print("No duplicates allowed, insert another value", end='')
          return
        
        else:
          if val < curr.value: # left
            if curr.left != None:
              curr = curr.left
            
            else:
              curr.left = node
              print("inserted {0} as left child of {1} node".format(val, curr.value), end='')
              return
          
          else: # right
            if curr.right != None:
              curr = curr.right
            
            else:
              curr.right = node
              print("inserted {0} as right child of {1} node".format(val, curr.value), end='')
              return
            
  # delete:
  def nextSucessor(self, root):
    if root == None:
      return root
    # smallest value in right
    curr = root
    curr = curr.right
    while(curr != None and curr.left != None):
      curr = curr.left
    return curr
  
  def lastPredecessor(self, root):
    if root == None:
      return root
    # greatest value in left
    curr = root
    curr = curr.left
    while(curr != None and curr.right != None):
      curr = curr.right
    return curr
  
  def deleteNode(self, root, val):
    if root == None:
      return root

    elif val < root.value:
      root.left = self.deleteNode(root.left, val)
    elif val > root.value:
      root.right = self.deleteNode(root.right, val)
    else: # val == root.value
      if root.left == None: # only right child
        tmp = root.right # or no child
        root = None
        return tmp
      elif root.right == None: # left child
        tmp = root.left
        root = None
        return tmp
      else: # 2 children
        # replace w/ next sucessor or last predecessor
        if self.nextSucessor(root) != None:
          tmp = self.nextSucessor(root)
          root.value = tmp.value
          root.right = self.deleteNode(root.right, tmp.value)
        else:
          tmp = self.lastPredecessor(root)
          root.value = tmp.value
          root.left = self.deleteNode(root.left, tmp.value)

    return root
