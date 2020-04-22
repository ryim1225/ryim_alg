import data_structure.r_heap as dsh

class HeapSort:
    def sort_bar_git(self, xlist, isMaxHeap = True, csv_path="sort_info.csv"):
        heap = dsh.rHeap()
        heap.sort_bar_gif(xlist, isMaxHeap, csv_path)