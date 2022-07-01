SPACE = 10
class TreeNode:

  def __init__(self, val=0, left=None, right=None):
    self.value = val
    self.left = left
    self.right = right
  
class AVLTree:

  def __init__(self, root=None):
    self.root = root
  
  def isEmpty(self):
    return self.root == None
  
  def contains(self, val, curr):
    if curr == None:
      return False
    if val == curr.value:
      return True

    if val > curr.value:
      return self.contains(val, curr.right)
    else:
      return self.contains(val, curr.left)

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
  def height(self, node):
    if node == None:
      return -1

    left_height = self.height(node.left)
    right_height = self.height(node.right)
    if left_height > right_height:
      return left_height + 1
    else:
      return right_height + 1
  
  
  def getBalanceFactor(self, node):
    if node == None:
      return -1
    return self.height(node.left) - self.height(node.right)
  

  def rightRotate(self, x):
    y = x.left
    subtree = y.right
    # perform rotation
    y.right = x
    x.left = subtree
    return y
  
  
  def leftRotate(self, x):
    y = x.right
    subtree = y.left
    # perform rotation
    y.left = x
    x.right = subtree
    return y
  
  def insert(self, curr, newNode):
    if curr == None:
      curr = newNode
      print("{0} inserted sucessfully".format(curr.value))
      return curr
  
    if newNode.value < curr.value:
      curr.left = self.insert(curr.left, newNode)
  
    elif newNode.value > curr.value:
      curr.right = self.insert(curr.right, newNode)
  
    else:
      print("No duplicates allowed, insert another value")
      return curr
  
    bf = self.getBalanceFactor(curr)
    if bf > 1 and newNode.value < curr.left.value: # left left
      return self.rightRotate(curr)
  
    elif bf < -1 and newNode.value > curr.right.value: # right right
      return self.leftRotate(curr)
  
    elif bf > 1 and newNode.value > curr.left.value: # left right
      curr.left = self.leftRotate(curr.left)
      return self.rightRotate(curr)
  
    elif bf < -1 and newNode.value < curr.right.value: # right left
      curr.right = self.rightRotate(curr.right)
      return self.leftRotate(curr)
  
    
    return curr
    
  
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
  
  def deleteNode(self, curr, val):
    if curr == None:
      return curr

    elif val < curr.value:
      curr.left = self.deleteNode(curr.left, val)
    elif val > curr.value:
      curr.right = self.deleteNode(curr.right, val)
    else: # val == curr.value
      if curr.left == None: # only right child
        tmp = curr.right # or no child
        curr = None
        return tmp
      elif curr.right == None: # left child
        tmp = curr.left
        curr = None
        return tmp
      else: # 2 children
        # replace w/ next sucessor or last pre
        if self.nextSucessor(curr) != None:
          next = self.nextSucessor(curr)
          curr.value = next.value
          curr.right = self.deleteNode(curr.right, next.value)
        else:
          last = self.lastPredecessor(curr)
          curr.value = last.value
          curr.left = self.deleteNode(curr.left, last.value)

    bf = self.getBalanceFactor(curr)

    if bf >= 2 and self.getBalanceFactor(curr.left) >= 0: # left left
      return self.rightRotate(curr)
    
    elif bf >= 2 and self.getBalanceFactor(curr.left) == -1: # left right
      curr.left = self.leftRotate(curr.left)
      return self.rightRotate(curr)
    
    elif bf <= -2 and self.getBalanceFactor(curr.right) <= 0: # right right
      return self.leftRotate(curr)
    
    elif bf <= -2 and self.getBalanceFactor(curr.right) == 1: # right left
      curr.right = self.rightRotate(curr.right)
      return self.leftRotate(curr)
    return curr
