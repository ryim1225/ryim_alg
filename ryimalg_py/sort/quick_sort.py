import csv
import random
import data_structure.r_stack as dss

class QuickSort:
    def sort(self, comparable_list):
        random.shuffle(comparable_list)
        low, high = 0, len(comparable_list)-1
        s = dss.rStack()
        s.push(low)
        s.push(high)
        while not s.isEmpty():
            j = s.top()
            s.pop()
            i = s.top()
            s.pop()
            pivot = self._partition(comparable_list, i, j)
            if (pivot-1) > i:
                s.push(i)
                s.push(pivot-1)
            if (pivot+1) < j:
                s.push(pivot+1)
                s.push(j)

    def sort_recursive(self, comparable_list):
        random.shuffle(comparable_list)
        self._sort_recursive(comparable_list, 0, len(comparable_list)-1)

    def _sort_recursive(self, comparable_list, low, high):
        if high <= low:
            return
        j = self._partition(comparable_list, low, high)
        self._sort_recursive(comparable_list, low, j-1)
        self._sort_recursive(comparable_list, j+1, high)

    def _partition(self, comparable_list, low, high):
        i, j = low+1, high
        v = comparable_list[low]
        while True:
            while comparable_list[j] > v :
                if j == low:
                    break
                else:
                    j -= 1
            while comparable_list[i] < v :
                if i == high:
                    break
                else:
                    i += 1
            if i >= j:
                break
            comparable_list[i], comparable_list[j] = comparable_list[j], comparable_list[i]
        comparable_list[low], comparable_list[j] = comparable_list[j], comparable_list[low]
        return j

    def sort_gif(self, comparable_list, csv_path="sort_info.csv"):
        length = len(comparable_list)
        low, high = 0, length-1
        s = dss.rStack()
        s.push(low)
        s.push(high)
        with open(csv_path,'w+', newline='') as file:
            content = csv.writer(file,dialect='excel')
            colors = ["rgb(50,50,50)" for _ in range(length)]
            content.writerow(comparable_list)
            content.writerow(colors)
            while not s.isEmpty():
                j = s.top()
                s.pop()
                i = s.top()
                s.pop()
                pivot = self._partition(comparable_list, i, j)
                content.writerow(comparable_list)
                colors = ["rgb(50,50,50)" for _ in range(length)]
                for k in range(i, j+1):
                    colors[k]   = "rgb(0,0,0)"
                colors[pivot] = "rgb(250,50,50)"
                content.writerow(colors)
                if (pivot-1) > i:
                    s.push(i)
                    s.push(pivot-1)
                if (pivot+1) < j:
                    s.push(pivot+1)
                    s.push(j)

class QuickSort3way:
    # def sort(self, comparable_list):
    #     random.shuffle(comparable_list)
    #     low, high = 0, len(comparable_list)-1
    #     lt, i, gt = low, low+1, high
    #     s = dss.rStack()
    #     s.push(lt)
    #     s.push(i)
    #     s.push(gt)
    #     while not s.isEmpty():
    #         j = s.top()
    #         s.pop()
    #         i = s.top()
    #         s.pop()
    #         pivot = self._partition(comparable_list, i, j)
    #         if (pivot-1) > i:
    #             s.push(i)
    #             s.push(pivot-1)
    #         if (pivot+1) < j:
    #             s.push(pivot+1)
    #             s.push(j)

    def sort_recursive(self, comparable_list):
        random.shuffle(comparable_list)
        self._sort_recursive(comparable_list, 0, len(comparable_list)-1)

    def _sort_recursive(self, comparable_list, low, high):
        if high <= low:
            return
        lt, gt = self._partition(comparable_list, low, high)
        self._sort_recursive(comparable_list, low, lt-1)
        self._sort_recursive(comparable_list, gt+1, high)

    def _partition(self, comparable_list, low, high):
        lt, i, gt = low, low+1, high
        v = comparable_list[low]
        while i <= gt:
            if comparable_list[i] < v :
                comparable_list[lt], comparable_list[i] = comparable_list[i], comparable_list[lt]
                lt += 1
                i  += 1
            elif comparable_list[i] > v :
                comparable_list[i], comparable_list[gt] = comparable_list[gt], comparable_list[i]
                gt -= 1
            else:
                i += 1
        return lt, gt