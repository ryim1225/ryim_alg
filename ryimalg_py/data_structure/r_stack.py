class rStack:
    def __init__(self):
        self._elems = []

    def isEmpty(self):
        return len(self._elems) == 0

    def push(self, elem):
        self._elems.append(elem)

    def size(self):
        return len(self._elems)

    def pop(self):
        if self.isEmpty():
            raise Exception("Empty in rStack.pop()")
        return self._elems.pop()

    def top(self):
        if self.isEmpty():
            raise Exception("Empty in rStack.top()")
        return self._elems[-1]