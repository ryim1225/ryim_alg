import data_structure.r_binary_tree as dbt

class BinarySearchTree(dbt.BinaryTree):
    def __init__(self):
        super().__init__()

    def insert(self, value):
        if self._root is None:
            self._root = dbt.BinaryTreeNode(value)
            return
        node = self._root
        isGreat = True
        while True:
            if node.data < value:
                isGreat = True
            else:
                isGreat = False
            if isGreat:
                if node.right is not None:
                    node = node.right
                else:
                    node.right = dbt.BinaryTreeNode(value)
                    return
            else:
                if node.left is not None:
                    node = node.left
                else:
                    node.left = dbt.BinaryTreeNode(value)
                    return

    def search(self, value):
        node = self._root
        while node is not None:
            if node.data < value:
                node = node.right
            elif node.data > value:
                node = node.left
            else:
                return node
        return None