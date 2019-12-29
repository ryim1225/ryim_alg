import unittest
import os
import sys
sys.path.append(os.getcwd())
sys.path.append(os.getcwd() + "/../../")
sys.path.append(os.getcwd() + "/ryimalg_py")
print(sys.path)
import sort.quick_sort as sqt
import draw.dynamicBarChart as ddbc


class TestQuickSort(unittest.TestCase):
    def setUp(self):
        self.ss = sqt.QuickSort()
        
    def tearDown(self):
        self.ss = None
        
    def test_sort(self):
        l = [3,2,6,7,12,5,0,44,67,30]
        self.ss.sort(l)
        self.assertEqual(l, [0,2,3,5,6,7,12,30,44,67])
        l1 = [26,5,9,12,85,36,1000,77,22,99,103,502,73,88,600,5,1060,2,7,17,90,20,60,41,92,200,302,999,52,78]
        self.ss.sort(l1)
        self.assertEqual(l1, [2, 5, 5, 7, 9, 12, 17, 20, 22, 26, 36, 41, 52, 60, 73, 77, 78, 85, 88, 90, 92, 99, 103, 200, 302, 502, 600, 999, 1000, 1060])

    def test_sort_r(self):
        l = [3,2,6,7,12,5,0,44,67,30]
        self.ss.sort_recursive(l)
        self.assertEqual(l, [0,2,3,5,6,7,12,30,44,67])
        l1 = [26,5,9,12,85,36,1000,77,22,99,103,502,73,88,600,5,1060,2,7,17,90,20,60,41,92,200,302,999,52,78]
        self.ss.sort_recursive(l1)
        self.assertEqual(l1, [2, 5, 5, 7, 9, 12, 17, 20, 22, 26, 36, 41, 52, 60, 73, 77, 78, 85, 88, 90, 92, 99, 103, 200, 302, 502, 600, 999, 1000, 1060])

    def test_sort_gif(self):
        l = [26,5,9,12,85,36,1000,77,22,99,103,502,73,88,600,5,1060,2,7,17,90,20,60,41,92,200,302,999,52,78]
        output_path = os.getcwd() + "/output/"
        if not os.path.exists(output_path):
            os.mkdir(output_path)
        csv_file = output_path + "quick_sort_info.csv"
        self.ss.sort_gif(l, csv_file)
        num = ddbc.make_pictures(csv_file, output_path + "quick_sort_imgs/", "../../draw/seed.png")
        #print(num)
        ddbc.create_gif([output_path+ 'quick_sort_imgs/'+str(i)+'.png' for i in range(1,num,2)], output_path + "quick_sort.gif", 0.8)

class TestQuickSort3way(unittest.TestCase):
    def setUp(self):
        self.ss = sqt.QuickSort3way()
        
    def tearDown(self):
        self.ss = None
        
    def test_sort(self):
        l = [3,2,6,7,12,5,0,44,67,30]
        self.ss.sort(l)
        self.assertEqual(l, [0,2,3,5,6,7,12,30,44,67])
        l1 = [26,5,9,12,85,36,1000,77,22,99,103,502,73,88,600,5,1060,2,7,17,90,20,60,41,92,200,302,999,52,78]
        self.ss.sort(l1)
        self.assertEqual(l1, [2, 5, 5, 7, 9, 12, 17, 20, 22, 26, 36, 41, 52, 60, 73, 77, 78, 85, 88, 90, 92, 99, 103, 200, 302, 502, 600, 999, 1000, 1060])

    def test_sort_r(self):
        l = [3,2,6,7,12,5,0,44,67,30]
        self.ss.sort_recursive(l)
        self.assertEqual(l, [0,2,3,5,6,7,12,30,44,67])
        l1 = [26,5,9,12,85,36,1000,77,22,99,103,502,73,88,600,5,1060,2,7,17,90,20,60,41,92,200,302,999,52,78]
        self.ss.sort_recursive(l1)
        self.assertEqual(l1, [2, 5, 5, 7, 9, 12, 17, 20, 22, 26, 36, 41, 52, 60, 73, 77, 78, 85, 88, 90, 92, 99, 103, 200, 302, 502, 600, 999, 1000, 1060])

def suite():
    suite = unittest.TestSuite()
    # suite.addTest(TestQuickSort("test_sort"))
    # suite.addTest(TestQuickSort("test_sort_r"))
    # suite.addTest(TestQuickSort("test_sort_gif"))
    # suite.addTest(TestQuickSort3way("test_sort"))
    suite.addTest(TestQuickSort3way("test_sort_r"))
    # suite.addTest(TestQuickSort3way("test_sort_gif"))
    return suite


if __name__ == "__main__":
    unittest.main(defaultTest = 'suite')