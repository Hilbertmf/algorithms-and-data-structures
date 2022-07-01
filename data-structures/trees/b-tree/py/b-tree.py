
 
# A BTree node
class BTreeNode:
  def __init__(self, t1, leaf1):
    self.t = t1 # Minimum degree
    self.leaf = leaf1
    self.keys = [None] * (2*self.t - 1)
    self.C = [None] * (2*self.t)
    self.n = 0 # num of keys
    
  def findKey(self, k):
    idx = 0
    while idx < self.n and self.keys[idx] < k:
      idx += 1
    return idx


  def insertNonFull(self, k):
    # Initialize index as index of rightmost element
    i = self.n - 1
 
    # If this is a leaf node
    if self.leaf == True:
      # The following loop does two things
      # a) Finds the location of new key to be inserted
      # b) Moves all greater keys to one place ahead
      while i >= 0 and self.keys[i] > k:
        self.keys[i+1] = self.keys[i]
        i -= 1
      # Insert the new key at found location
      self.keys[i+1] = k
      self.n += 1
    
    else: # If this node is not leaf
      # Find the child which is going to have the new key
      while i >= 0 and self.keys[i] > k:
        i -=  1

      # See if the found child is full
      if self.C[i+1].n == 2*(self.t)-1:
          # If the child is full, then split it
          self.splitChild(i+1, self.C[i+1])

          # After split, the middle key of C[i] goes up and
          # C[i] is splitted defo two.  See which of the two
          # is going to have the new key
          if self.keys[i+1] < k:
              i += 1
      
      self.C[i+1].insertNonFull(k)

  def splitChild(self, i, y):
    # Create a new node which is going to store (t-1) keys
    # of y
    z = BTreeNode(y.t, y.leaf)
    z.n = self.t - 1
 
    # Copy the last (t-1) keys of y to z
    for j in range(self.t-1):
      z.keys[j] = y.keys[j+self.t]
        
 
    # Copy the last t children of y to z
    if y.leaf == False:
      for j in range(self.t):
        z.C[j] = y.C[j+self.t]
            
    # Reduce the number of keys in y
    y.n = self.t - 1
 

    # Since this node is going to have a new child, create space of new child
    for j in range(self.n, i, -1):
      self.C[j+1] = self.C[j]
        
    # Link the new child to this node
    self.C[i+1] = z
 
    # A key of y will move to this node. Find the location of
    # new key and move all greater keys one space ahead
    for j in range(self.n-1, i-1, -1):
      self.keys[j+1] = self.keys[j]
        
    # Copy the middle key of y to this node
    self.keys[i] = y.keys[self.t-1]
 
    # Increment count of keys in this node
    self.n += 1

  def traverse(self):
    # There are n keys and n+1 children, traverse through n keys
    # and first n children
    i = 0
    while i < self.n:
      if self.leaf == False:
        self.C[i].traverse()
      print(" {}".format(self.keys[i]), end='')
      i += 1
        
    if self.leaf == False:
      self.C[i].traverse()    

  def contains(self, k):
    # Find the first key greater than or equal to k
    i = 0
    while i < self.n and k > self.keys[i]:
      i += 1
 
    # If the found key is equal to k, return this node
    if self.keys[i] == k:
      return True
 
    # If key is not found here and this is a leaf node
    if self.leaf == True:
      return False
 
    # Go to the appropriate child
    return self.C[i].contains(k)

  
  def search(self, k):
  # Find the first key greater than or equal to k
    i = 0
    while i < self.n and k > self.keys[i]:
      i += 1
 
    # If the found key is equal to k, return this node
    if self.keys[i] == k:
      return self
 
    # If key is not found here and this is a leaf node
    if self.leaf == True:
      return None
 
    # Go to the appropriate child
    return self.C[i].search(k)

  
  def remove(self, k):
    idx = self.findKey(k)

    # The key to be removed is present in this node
    if idx < self.n and self.keys[idx] == k:

      # If the node is a leaf node - removeFromLeaf is called
      # Otherwise, removeFromNonLeaf function is called
      if self.leaf:
        self.removeFromLeaf(idx)
      else:
        self.removeFromNonLeaf(idx)
    
    else:
        # If this node is a leaf node, then the key is not present in tree
        if self.leaf:
          print("The key {} does not exist in the tree".format(k))
          return
        
        # The key to be removed is present in the sub-tree rooted with this node
        # The flag indicates whether the key is present in the sub-tree rooted
        # with the last child of this node
        flag = False
        if idx == self.n:
          flag = True

        # If the child where the key is supposed to exist has less that t keys,
        # we fill that child
        if self.C[idx].n < self.t:
          self.fill(idx)

        # If the last child has been merged, it must have merged with the previous
        # child and so we recurse on the (idx-1)th child. Else, we recurse on the
        # (idx)th child which now has atleast t keys
        if flag and idx > self.n:
          self.C[idx-1].remove(k)
        else:
          self.C[idx].remove(k)
    
    return

  def removeFromLeaf(self, idx):
    # Move all the keys after the idx-th pos one place backward
    for i in range(idx+1, self.n, 1):
      self.keys[i-1] = self.keys[i]

    # Reduce the count of keys
    self.n -= 1
    return

  def removeFromNonLeaf(self, idx):
    k = self.keys[idx]

    # If the child that precedes k (C[idx]) has atleast t keys,
    # find the predecessor 'pred' of k in the subtree rooted at
    # C[idx]. Replace k by pred. Recursively delete pred
    # in C[idx]
    if self.C[idx].n >= self.t:
      pred = self.getPred(idx)
      self.keys[idx] = pred
      self.C[idx].remove(pred)

    # If the child C[idx] has less that t keys, examine C[idx+1].
    # If C[idx+1] has atleast t keys, find the successor 'succ' of k in
    # the subtree rooted at C[idx+1]
    # Replace k by succ
    # Recursively delete succ in C[idx+1]
    elif self.C[idx+1].n >= self.t:
      succ = self.getSucc(idx)
      self.keys[idx] = succ
      self.C[idx+1].remove(succ)
    

    # If both C[idx] and C[idx+1] has less that t keys,merge k and all of C[idx+1]
    # defo C[idx]
    # Now C[idx] contains 2t-1 keys
    # Free C[idx+1] and recursively delete k from C[idx]
    else:
      self.merge(idx)
      self.C[idx].remove(k)
    
    return

  def getPred(self, idx):
    # Keep moving to the right most node until we reach a leaf
    curr = self.C[idx]
    while curr.leaf == False:
      curr = curr.C[curr.n]

    # Return the last key of the leaf
    return curr.keys[curr.n-1] # POSSIBLE ERROR

  def getSucc(self, idx):
    # Keep moving the left most node starting from C[idx+1] until we reach a leaf
    curr = self.C[idx+1]
    while curr.leaf == False:
      curr = curr.C[0]

    # Return the first key of the leaf
    return curr.keys[0]

  def fill(self, idx):
    # If the previous child(C[idx-1]) has more than t-1 keys, borrow a key
    # from that child
    if idx != 0 and self.C[idx-1].n >= self.t:
      self.borrowFromPrev(idx)

    # If the next child(C[idx+1]) has more than t-1 keys, borrow a key
    # from that child
    elif idx != self.n and self.C[idx+1].n >= self.t:
      self.borrowFromNext(idx)

    # Merge C[idx] with its sibling
    # If C[idx] is the last child, merge it with its previous sibling
    # Otherwise merge it with its next sibling
    else:
      if idx != self.n:
        self.merge(idx)
      else:
        self.merge(idx-1)
    
    return

  def borrowFromPrev(self, idx):
    child = self.C[idx]
    sibling = self.C[idx-1]

    # The last key from C[idx-1] goes up to the parent and key[idx-1]
    # from parent is inserted as the first key in C[idx]. Thus, the  loses
    # sibling one key and child gains one key

    # Moving all key in C[idx] one step ahead
    for i in range(child.n-1, -1, -1):
      child.keys[i+1] = child.keys[i]

    # If C[idx] is not a leaf, move all its child podefers one step ahead
    if not child.leaf:
      for i in range(child.n, -1, -1):
        child.C[i+1] = child.C[i]
    

    # Setting child's first key equal to keys[idx-1] from the current node
    child.keys[0] = self.keys[idx-1]

    # Moving sibling's last child as C[idx]'s first child
    if not child.leaf:
      child.C[0] = sibling.C[sibling.n]

    # Moving the key from the sibling to the parent
    # This reduces the number of keys in the sibling
    self.keys[idx-1] = sibling.keys[sibling.n-1]

    child.n += 1
    sibling.n -= 1

    return

  def borrowFromNext(self, idx):
    child = self.C[idx]
    sibling = self.C[idx+1]

    # keys[idx] is inserted as the last key in C[idx]
    child.keys[(child.n)] = self.keys[idx]

    # Sibling's first child is inserted as the last child
    # defo C[idx]
    if not child.leaf:
      child.C[(child.n)+1] = sibling.C[0]

    #The first key from sibling is inserted defo keys[idx]
    self.keys[idx] = sibling.keys[0]

    # Moving all keys in sibling one step behind
    for i in range(1, sibling.n):
      sibling.keys[i-1] = sibling.keys[i]

    # Moving the child podefers one step behind
    if not sibling.leaf:
      for i in range(1, sibling.n + 1):
        sibling.C[i-1] = sibling.C[i]


    # Increasing and decreasing the key count of C[idx] and C[idx+1]
    # respectively
    child.n += 1
    sibling.n -= 1

    return

  def merge(self, idx):
    child = self.C[idx]
    sibling = self.C[idx+1]

    # Pulling a key from the current node and inserting it defo (t-1)th
    # position of C[idx]
    child.keys[self.t-1] = self.keys[idx]

    # Copying the keys from C[idx+1] to C[idx] at the end
    for i in range(0, sibling.n):
      child.keys[i+self.t] = sibling.keys[i]

    # Copying the child podefers from C[idx+1] to C[idx]
    if not child.leaf:
      for i in range(0, sibling.n + 1):
        child.C[i+self.t] = sibling.C[i]
    

    # Moving all keys after idx in the current node one step before -
    # to fill the gap created by moving keys[idx] to C[idx]
    for i in range(idx+1, self.n):
      self.keys[i-1] = self.keys[i]

    # Moving the child podefers after (idx+1) in the current node one
    # step before
    for i in range(idx+2, self.n+1):
      self.C[i-1] = self.C[i]

    # Updating the key count of child and the current node
    child.n += sibling.n+1
    self.n -= 1

    # Freeing the memory occupied by sibling
    sibling = None
    return


 
# A BTree
class BTree:

  def __init__(self, _t):
    self.t = _t
    self.root = None
 
  # function to traverse the tree
  def traverse(self):
    if self.root != None:
      self.root.traverse() 

  def contains(self, k):
    return self.root.contains(k)
  
  
  # function to search a key in this tree
  def search(self, k):
    if self.root == None:
      return None
    return self.root.search(k) 

  # The main function that inserts a new key in this B-Tree
  def insert(self, k):
    # If tree is empty
    if self.root == None:
      # Allocate memory for root
      self.root = BTreeNode(self.t, True)
      self.root.keys[0] = k  # Insert key
      self.root.n = 1  # Update number of keys in root
    
    else: # If tree is not empty
      # If root is full, then tree grows in height
      if self.root.n == 2*(self.t) - 1:
        s = BTreeNode(self.t, False)

        # Make old root as child of new root
        s.C[0] = self.root

        # Split the old root and move 1 key to the new root
        s.splitChild(0, self.root)

        # New root has two children now.  Decide which of the
        # two children is going to have new key
        i = 0
        if s.keys[0] < k:
          i += 1
        s.C[i].insertNonFull(k)

        # Change root
        self.root = s
    
      else: # If root is not full, call insertNonFull for root
        self.root.insertNonFull(k)
  
  # The main function that removes a new key in thie B-Tree
  def remove(self, k):
    if not self.root:
      print("Empty tree\n")
      return

    # Call the remove function for root
    self.root.remove(k)

    # If the root node has 0 keys, make its first child as the new root
    #  if it has a child, otherwise set root as NULL
    if self.root.n == 0:
      tmp = self.root
      if self.root.leaf:
        self.root = None
      else:
        self.root = self.root.C[0]

      # Free the old root
      tmp = None

    return

class NodeInfo:
  
  def __init__(self):
    self.text = ""
    self.text_pos = None
    self.text_end = None

class BTreePrinter:

  def __init__(self):
    self.levels = [[]]

  def node_text(self, keys, key_count):
    sep = " "
    os = "["
    for i in range(key_count):
      os += str(sep) + str(keys[i])
    os += "]"
    
    return os

  def before_traversal(self):
    self.levels = [[]]
    # self.levels = [[]] * 10   # far beyond anything that could usefully be printed


  def visit(self, node, level = 0, child_index = 0):
    while level >= len(self.levels):
      self.levels.append([])
    
    # if level >= len(self.levels):
      
    #   resize = level + 1
    #   self.levels = [[] * resize]
      # self.levels.resize(level + 1)

    level_info = self.levels[level]
    info = NodeInfo()

    info.text_pos = 0
    if not len(level_info) == 0: # one blank between nodes, one extra blank if left-most child
      if child_index == 0:
        info.text_pos = level_info[len(level_info) - 1].text_end + 2
      else:
        info.text_pos = level_info[len(level_info) - 1].text_end + 1

    info.text = self.node_text(node.keys, node.n)

    if node.leaf:
      info.text_end = info.text_pos + len(info.text)
    
    else: # non-leaf -> do all children so that .text_end for the right-most child becomes known
      e = node.n
      for i in range(0, e+1):
        self.visit(node.C[i], level + 1, i)

      info.text_end = self.levels[level + 1][len(self.levels[level + 1]) - 1].text_end
    

    self.levels[level].append(info)

  def print_blanks(self, n):

    while n:
      print(" ", end = '')
      n -= 1

  
  def after_traversal(self):
    l = 0
    level_count = len(self.levels)
    while(True):
      level = self.levels[l]
      prev_end = 0

      for node in level:
        total = node.text_end - node.text_pos
        slack = total - len(node.text)
        blanks_before = node.text_pos - prev_end
      
        self.print_blanks(blanks_before + slack / 2)
        print(node.text, end='')

        if node == level[len(level) - 1]:
          break

        self.print_blanks(slack - slack / 2)

        prev_end += blanks_before + total
    
      l += 1
      if l == level_count:
        break

      print("\n")
    

    print("\n", end = '')

  def printTree(self, tree):
    self.before_traversal()
    self.visit(tree.root)
    self.after_traversal()
   
# Driver program to test above functions
def main():
  option = -1
  printer = BTreePrinter()

  degree = int(input("Enter the degree of the tree:"))
  while degree < 2:
    degree = int(input("Value too small. Enter another value:"))
      
  tree = BTree(degree)
  print("Creating tree of degree {}".format(degree))
  print("{0} <= number of children < {1}".format(degree, 2*degree))
  print("{0} <= number of keys < {1}".format(degree - 1, 2*degree - 1))
  
  while option != 0:
    print("Which operation you wanna perform?")
    print("1. Insert node")
    print("2. Search node")
    print("3. Delete node")
    print("4. Print values in order")
    print("5. Print tree")
    print("0. Exit")
    option = int(input("Select Option number: "))

    if option == 0:
      print("\nExiting...\n", end='')
    elif option == 1:
      val = int(input("Pass an integer value to insert: "))
      print("\nInserting {}...".format(val))
      tree.insert(val)
    elif option == 2:
      val = int(input("Pass an integer value to search: "))
      print("\nSearching...\n", end='')
      if tree.contains(val):
        print("Value found!\n", end='')
      else:
        print("{} is not present in the tree.\n\n".format(val), end='')
    elif option == 3:
      val = int(input("Pass a node to delete:"))
      if tree.contains(val):
        print("\nDeleting...\n")
        tree.remove(val)
      else:
        print("\nValue not found\n")
    elif option == 4:
      print("\n", end='')
      print("In order:")
      tree.traverse()
      print("\n", end='')
      # print values
    elif option == 5:
      print("--------------------------------------------------------")
      print("Tree printed:\n\n", end='')
      printer.printTree(tree)
      print("\n\n--------------------------------------------------------\n")
    else:
      print("\nEnter proper option number\n", end='')
      
if __name__ == "__main__":
  main()


