import csv


class rHeap:
    def __init__(self, isMaxHeap = True):
        self._elems = [None]
        self._length = 0
        self._isMaxHeap = isMaxHeap

    # make sure xlist[0] = None because we can't use it.
    def makeHeap(self, xlist, isMaxHeap = True):
        self._elems.clear()
        self._elems = xlist
        self._length = len(xlist) - 1
        self._isMaxHeap = isMaxHeap
        for k in range(self._length//2, 0, -1):
            self._sink(k)

    def sort(self):
        while self._length > 1:
            self._elems[1], self._elems[self._length] = self._elems[self._length], self._elems[1]
            self._length -= 1
            self._sink(1)

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

###########################[API for paint]#########################################

    # make sure comparable_list[0] = None because we can't use it.
    def sort_bar_gif(self, comparable_list, isMaxHeap = True, csv_path="sort_info.csv"):
        # make heap
        with open(csv_path,'w+', newline='') as file:
            length_ca = len(comparable_list)
            length = length_ca - 1
            content = csv.writer(file,dialect='excel')
            colors = ["rgb(50,50,50)" for _ in range(length_ca)]
            content.writerow(comparable_list)
            content.writerow(colors)
            for k in range(length//2, 0, -1):
                content.writerow(comparable_list)
                colors = ["rgb(50,50,50)" for _ in range(length_ca)]
                colors[k] = "rgb(250,50,50)"
                content.writerow(colors)
                while 2*k <= length:
                    j = 2*k
                    if j < length and not self._compare(comparable_list[j], comparable_list[j+1]):
                        j += 1
                    if self._compare(comparable_list[k], comparable_list[j]):
                        break
                    comparable_list[j], comparable_list[k] = comparable_list[k], comparable_list[j]
                    content.writerow(comparable_list)
                    colors = ["rgb(50,50,50)" for _ in range(length_ca)]
                    colors[k] = "rgb(250,50,50)"
                    colors[j] = "rgb(0,0,0)"
                    content.writerow(colors)
                    k = j
        # sort
            colors = ["rgb(50,50,50)" for _ in range(length_ca)]
            content.writerow(comparable_list)
            content.writerow(colors)
            length_temp = length
            while length_temp > 1:
                comparable_list[1], comparable_list[length_temp] = comparable_list[length_temp], comparable_list[1]
                colors = ["rgb(50,50,50)" for _ in range(length_ca)]
                colors[1] = "rgb(0,0,0)"
                colors[length_temp] = "rgb(0,0,0)"
                content.writerow(comparable_list)
                content.writerow(colors)
                length_temp -= 1
                k = 1
                content.writerow(comparable_list)
                colors = ["rgb(50,50,50)" for _ in range(length_ca)]
                colors[k] = "rgb(250,50,50)"
                content.writerow(colors)
                while 2*k <= length_temp:
                    j = 2*k
                    if j < length_temp and not self._compare(comparable_list[j], comparable_list[j+1]):
                        j += 1
                    if self._compare(comparable_list[k], comparable_list[j]):
                        break
                    comparable_list[j], comparable_list[k] = comparable_list[k], comparable_list[j]
                    content.writerow(comparable_list)
                    colors = ["rgb(50,50,50)" for _ in range(length_ca)]
                    colors[k] = "rgb(250,50,50)"
                    colors[j] = "rgb(0,0,0)"
                    content.writerow(colors)
                    k = j