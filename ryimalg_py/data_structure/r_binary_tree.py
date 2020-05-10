#import abc # for @abc.abstractclassmethod
import data_structure.r_stack as dss
from queue import Queue

# The defination of binary tree node
class BinaryTreeNode:
    def __init__(self, data):
        self.data  = data
        self.left  = None
        self.right = None

# The defination of binary tree
class BinaryTree:
    def __init__(self):
        self._root = None
        self.__size = 0
        self.__threshold = 15
        self.__func = self.__defaultProc

    @property
    def size(self):
        return self.__size

    @property
    def threshold(self):
        return self.__threshold

    @threshold.setter
    def threshold(self, value):
        self.__threshold = value

    def __defaultProc(self, node_):
        print(node_.data)

    def setProc(self, func_):
        self.__func = func_

    def insert(self, value):
        q = Queue()
        q.put(self._root)
        while not q.empty():
            cur_node = q.get()
            self.__func(cur_node)
            if cur_node.left is not None:
                q.put(cur_node.left)
            else:
                cur_node.left = BinaryTreeNode(value)
                break
            if cur_node.right is not None:
                q.put(cur_node.right)
            else:
                cur_node.right = BinaryTreeNode(value)
                break

    def doPreOrderTraversal(self):
        if self.__size > self.__threshold:
            self._doPreOrderTraversal_recursion(self._root)
        else:
            self._doPreOrderTraversal_stack()
    
    def _doPreOrderTraversal_recursion(self, node_):
        if node_ is None:
            return
        self.__func(node_)
        self._doPreOrderTraversal_recursion(node_.left)
        self._doPreOrderTraversal_recursion(node_.right)

    def _doPreOrderTraversal_stack(self):
        s = dss.rStack()
        node = self._root
        while node is not None or not s.isEmpty():
            while node is not None:
                self.__func(node)
                s.push(node)
                node = node.left
            if not s.isEmpty():
                node = s.pop().right

    def doInOrderTraversal(self):
        if self.__size > self.__threshold:
            self._doInOrderTraversal_recursion(self._root)
        else:
            self._doInOrderTraversal_stack()
    
    def _doInOrderTraversal_recursion(self, node_):
        if node_ is None:
            return
        self._doInOrderTraversal_recursion(node_.left)
        self.__func(node_)
        self._doInOrderTraversal_recursion(node_.right)

    def _doInOrderTraversal_stack(self):
        s = dss.rStack()
        node = self._root
        while node is not None or not s.isEmpty():
            while node is not None:
                s.push(node)
                node = node.left
            if not s.isEmpty():
                self.__func(node)
                node = s.pop().right

    def doPostOrderTraversal(self):
        if self.__size > self.__threshold:
            self._doPostOrderTraversal_recursion(self._root)
        else:
            self._doPostOrderTraversal_stack()
    
    def _doPostOrderTraversal_recursion(self, node_):
        if node_ is None:
            return
        self._doPostOrderTraversal_recursion(node_.left)
        self._doPostOrderTraversal_recursion(node_.right)
        self.__func(node_)

    def _doPostOrderTraversal_stack(self):
        s = dss.rStack()
        cur_node = self._root
        s.push(cur_node)
        while not s.isEmpty():
            cur_node = s.top()
            if prev_node is not None and (cur_node.left == prev_node or cur_node.right == prev_node) or (cur_node.left is None and cur_node.left is None):
                self.__func(cur_node)
                s.pop()
                prev_node = cur_node
            else:
                if cur_node.right is not None:
                    s.push(cur_node.right)
                if cur_node.left is not None:
                    s.push(cur_node.left)

    def doLevelOrderTraversal(self):
        q = Queue()
        q.put(self._root)
        while not q.empty():
            cur_node = q.get()
            self.__func(cur_node)
            if cur_node.left is not None:
                q.put(cur_node.left)
            if cur_node.right is not None:
                q.put(cur_node.right)
