import csv
import copy


class MergeSort:
    def sort(self, comparable_list):
        length = len(comparable_list)
        sz = 1
        while sz < length:
            for lo in range(0, length - sz, sz+sz):
                self._merge(comparable_list, lo, lo+sz-1, min(lo+sz+sz-1, length-1))
            sz *= 2

    def sort_recursive(self, comparable_list):
        self._sort_recursive(comparable_list, 0, len(comparable_list)-1)

    def _sort_recursive(self, comparable_list, low, high):
        if high <= low:
            return
        mid = low + (high - low)//2
        self._sort_recursive(comparable_list, low, mid)
        self._sort_recursive(comparable_list, mid+1, high)
        self._merge(comparable_list, low, mid, high)

    def _merge(self, comparable_list, low, mid, high):
        i, j = low, mid+1
        list_aux = copy.deepcopy(comparable_list) # need to deep copy, or it will make a mistake
        for k in range(low, high+1):
            if i >  mid:
                comparable_list[k] = list_aux[j]
                j+=1
            elif j > high:
                comparable_list[k] = list_aux[i]
                i+=1
            elif list_aux[j] < list_aux[i]:
                comparable_list[k] = list_aux[j]
                j+=1
            else:
                comparable_list[k] = list_aux[i]
                i+=1

    def sort_gif(self, comparable_list, csv_path="sort_info.csv"):
        length = len(comparable_list)
        sz = 1
        with open(csv_path,'w+', newline='') as file:
            content = csv.writer(file,dialect='excel')
            colors = ["rgb(50,50,50)" for _ in range(length)]
            content.writerow(comparable_list)
            content.writerow(colors)
            while sz < length:
                for lo in range(0, length - sz, sz+sz):
                    self._merge(comparable_list, lo, lo+sz-1, min(lo+sz+sz-1, length-1))
                    content.writerow(comparable_list)
                    colors = ["rgb(50,50,50)" for _ in range(length)]
                    for i in range(lo, min(lo+sz+sz-1, length-1)+1):
                        colors[i]   = "rgb(0,0,0)"
                    content.writerow(colors)
                sz *= 2
