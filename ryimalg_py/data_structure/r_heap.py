class rHeap:
    def __init__(self, isMaxHeap = True):
        self._elems = [None]
        self._length = 0
        self._isMaxHeap = isMaxHeap

    def isEmpty(self):
        return self._length == 0

    def insert(self, elem):
        self._elems.insert(self._length+1, elem)
        self._length += 1
        self._swim(self._length)

    def size(self):
        return self._length

    def pop(self):
        if self.isEmpty():
            raise Exception("Empty in rHeap.pop()")
        self._elems[1], self._elems[self._length] = self._elems[self._length], self._elems[1]
        self._length -= 1
        self._sink(1)

    def top(self):
        if self.isEmpty():
            raise Exception("Empty in rHeap.top()")
        return self._elems[1]

    def _sink(self, k):
        while 2*k <= self._length:
            j = 2*k
            if j < self._length and not self._compare(self._elems[j], self._elems[j+1]):
                j += 1
            if self._compare(self._elems[k], self._elems[j]):
                break
            self._elems[j], self._elems[k] = self._elems[k], self._elems[j]
            k = j

    def _swim(self, k):
        while k >1 and not self._compare(self._elems[k//2], self._elems[k]):
            self._elems[k//2], self._elems[k] = self._elems[k], self._elems[k//2]
            k = k//2

    def _compare(self, a, b):
        if self._isMaxHeap:
            return a >= b
        else:
            return a <= b