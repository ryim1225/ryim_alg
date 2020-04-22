import unittest
import os
import sys
sys.path.append(os.getcwd())
sys.path.append(os.getcwd() + "/../../")
sys.path.append(os.getcwd() + "/ryimalg_py")
print(sys.path)
import sort.heap_sort as sht
import draw.paint as dp


class TestHeapSort(unittest.TestCase):
    def setUp(self):
        self.ss = sht.HeapSort()
        
    def tearDown(self):
        self.ss = None

    def test_sort_gif(self):
        l = [0,34,21,63,7,12,5,2,44,67,30] # l[0] = 0 isn't used
        output_path = os.getcwd() + "/output/"
        if not os.path.exists(output_path):
            os.mkdir(output_path)
        csv_file = output_path + "heap_sort_info.csv"
        self.ss.sort_bar_git(l, True, csv_file)
        num = dp.make_pictures_of_barchart(csv_file, output_path + "heap_sort_imgs/", "../../draw/seed.png")
        #print(num)
        dp.create_gif([output_path+ 'heap_sort_imgs/'+str(i)+'.png' for i in range(1,num,2)], output_path + "heap_sort.gif", 0.8)


def suite():
    suite = unittest.TestSuite()
    suite.addTest(TestHeapSort("test_sort_gif"))
    return suite


if __name__ == "__main__":
    unittest.main(defaultTest = 'suite')