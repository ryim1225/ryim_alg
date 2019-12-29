import unittest
import os
import sys
sys.path.append(os.getcwd())
sys.path.append(os.getcwd() + "/../../")
sys.path.append(os.getcwd() + "/ryimalg_py")
print(sys.path)
import data_structure.r_heap as heap


class TestHeap(unittest.TestCase):
    def setUp(self):
        self.ss = None
        
    def tearDown(self):
        self.ss = None
        
    def test_max_heap(self):
        l1 = [26,5,9,12,85,36,1000,77,22,99,103,502,73,88,600,5,1060,2,7,17,90,20,60,41,92,200,302,999,52,78]
        lret = sorted(l1,reverse=True)
        # print(l1)
        # print(lret)
        self.ss = heap.rHeap()
        for elem in l1:
            self.ss.insert(elem)
        lc = []
        while not self.ss.isEmpty():
            lc.append(self.ss.top())
            self.ss.pop()
        # print(lc)
        self.assertEqual(lc, lret)

    def test_min_heap(self):
        l1 = [26,5,9,12,85,36,1000,77,22,99,103,502,73,88,600,5,1060,2,7,17,90,20,60,41,92,200,302,999,52,78]
        lret = sorted(l1)
        # print(l1)
        # print(lret)
        self.ss = heap.rHeap(isMaxHeap=False)
        for elem in l1:
            self.ss.insert(elem)
        lc = []
        while not self.ss.isEmpty():
            lc.append(self.ss.top())
            self.ss.pop()
        # print(lc)
        self.assertEqual(lc, lret)


def suite():
    suite = unittest.TestSuite()
    suite.addTest(TestHeap("test_max_heap"))
    suite.addTest(TestHeap("test_min_heap"))
    return suite


if __name__ == "__main__":
    unittest.main(defaultTest = 'suite')