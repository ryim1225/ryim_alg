import unittest
import os
import sys
sys.path.append(os.getcwd() + "/../../")
sys.path.append(os.getcwd() + "/ryimalg_py")
print(sys.path)
import sort.insertion_sort as sit
import draw.paint as dp


class TestInsertionSort(unittest.TestCase):
    def setUp(self):
        self.ss = sit.InsertionSort()
        
    def tearDown(self):
        self.ss = None
        
    def test_sort(self):
        l = [3,2,6,7,12,5,0,44,67,30]
        self.ss.sort(l)
        self.assertEqual(l, [0,2,3,5,6,7,12,30,44,67])
        l1 = [26,5,9,12,85,36,1000,77,22,99,103,502,73,88,600,5,1060,2,7,17,90,20,60,41,92,200,302,999,52,78]
        self.ss.sort(l1)
        self.assertEqual(l1, [2, 5, 5, 7, 9, 12, 17, 20, 22, 26, 36, 41, 52, 60, 73, 77, 78, 85, 88, 90, 92, 99, 103, 200, 302, 502, 600, 999, 1000, 1060])

    def test_sort_gif(self):
        l = [34,21,63,7,12,5,2,44,67,30]
        output_path = os.getcwd() + "/output/"
        if not os.path.exists(output_path):
            os.mkdir(output_path)
        csv_file = output_path + "insertion_sort_info.csv"
        self.ss.sort_gif(l, csv_file)
        num = dp.make_pictures_of_barchart(csv_file, output_path + "insertion_sort_imgs/", "../../draw/seed.png")
        #print(num)
        dp.create_gif([output_path+ 'insertion_sort_imgs/'+str(i)+'.png' for i in range(1,num,2)], output_path + "insertion_sort.gif", 0.8)


def suite():
    suite = unittest.TestSuite()
    suite.addTest(TestInsertionSort("test_sort"))
    suite.addTest(TestInsertionSort("test_sort_gif"))
    return suite


if __name__ == "__main__":
    unittest.main(defaultTest = 'suite')