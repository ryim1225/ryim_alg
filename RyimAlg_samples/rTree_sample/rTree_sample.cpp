#include "rTree_sample.h"
#include "ryimTestUtility.h"
#include <string>

testTree::testTree() {}
testTree::~testTree() {}

void testTree::test()
{
	std::cout << "rTree_sample.cpp" << std::endl;
	testBST();
	testRBT();
}

void testTree::testBST()
{
	std::cout << "BST" << std::endl;
	ProjectPath ppath;
	ppath.getProjectPath("\\output\\tree\\");
	std::string   path = ppath.getPath();
	std::wstring wpath = ppath.getWPath();

	Ryim::BinarySearchTree<char> testInsert1;
	//testInsert1 = { 'S', 'E', 'X', 'A', 'R', 'C', 'H', 'M', 'L', 'P' };
	testInsert1 = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'L' };
	Ryim::TreeTools::generatetxt<typename Ryim::BinarySearchTree<char>::const_reference> gt;
	Ryim::TreeTools::DealWithNodeBase<typename Ryim::BinarySearchTree<char>::const_reference> dwnb;

	{
		ryimTestTimer timer("search 1");
		const Ryim::__BinaryTreeNode<char>* re = testInsert1.search('L');

		std::cout << re->element << std::endl;
		testInsert1.preorder_traverse(&dwnb);
		testInsert1.inorder_traverse(&dwnb);
		testInsert1.postorder_traverse(&dwnb);
	}

	{
		gt.setName(path + "testInsert1_search");
		ryimTestTimer timer("search 2");
		const Ryim::__BinaryTreeNode<char>* re = testInsert1.search('T');
		if (re)
			std::cout << re->element << std::endl;
		else
		{
			std::cout << "can't find" << std::endl;
		}
		testInsert1.inorder_traverse(&gt);
	}

	{
		ryimTestTimer timer("search 3");
		Ryim::arraylist<char> result;
		testInsert1.search(testInsert1.getRoot(), result, 'F', 'T');
		std::cout << "the BST: ";
		testInsert1.inorder_traverse(&dwnb);
		std::cout << "the elements between F and T: ";
		for each (auto element in result)
		{
			std::cout << element << ", ";
		}
		std::cout << std::endl;
	}

	{
		gt.setName(path + "testInsert1_insert");
		ryimTestTimer timer("insert");
		testInsert1.insert('T');
		testInsert1.inorder_traverse(&gt);
		testInsert1.setBoundary(3);
		testInsert1.preorder_traverse(&dwnb);
		testInsert1.inorder_traverse(&dwnb);
		testInsert1.postorder_traverse(&dwnb);
	}

	{
		ryimTestTimer timer("getMin");
		const Ryim::__BinaryTreeNode<char>* re = testInsert1.getMin();
		if (re)
			std::cout << re->element << std::endl;
		else
		{
			std::cout << "can't find" << std::endl;
		}
		testInsert1.inorder_traverse(&dwnb);
	}

	{
		ryimTestTimer timer("getMax");
		const Ryim::__BinaryTreeNode<char>* re = testInsert1.getMax();
		if (re)
			std::cout << re->element << std::endl;
		else
		{
			std::cout << "can't find" << std::endl;
		}
		testInsert1.inorder_traverse(&dwnb);
		std::cout << std::endl;
		testInsert1.makeDot(path + "testInsert1_getMax");
		graphvizHelper::command(wpath, L"testInsert1_getMax");
	}

	{
		ryimTestTimer timer("eraseMin");
		testInsert1.eraseMin();
		testInsert1.inorder_traverse(&dwnb);
	}

	{
		ryimTestTimer timer("eraseMax");
		testInsert1.eraseMax();
		testInsert1.inorder_traverse(&dwnb);
	}

	{
		ryimTestTimer timer("erase");
		testInsert1.erase('E');
		testInsert1.inorder_traverse(&dwnb);
		testInsert1.makeDot(path + "testinsert1_erase");
		graphvizHelper::command(wpath, L"testInsert1_erase");
	}


}

void testTree::testRBT()
{
	std::cout << "Red Black Tree" << std::endl;
	ProjectPath ppath;
	ppath.getProjectPath("\\output\\tree\\");
	std::string   path = ppath.getPath();
	std::wstring wpath = ppath.getWPath();

	Ryim::RedBlackTree<char> testInsert2;
	testInsert2.setRecurrenceSentry(1);
	//testInsert2 = { 'S', 'E', 'X', 'A', 'R', 'C', 'H', 'M', 'L', 'P' };
	testInsert2 = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'L' };
	Ryim::TreeTools::generatetxt<typename Ryim::RedBlackTree<char>::const_reference> gt;
	Ryim::TreeTools::DealWithNodeBase<typename Ryim::RedBlackTree<char>::const_reference> dwnb;

	{
		ryimTestTimer timer("rbt search 1");
		const Ryim::__RedBlackTreeNode<char>* re = testInsert2.search('L');
		std::cout << re->element << std::endl;
		testInsert2.preorder_traverse(&dwnb);
		testInsert2.inorder_traverse(&dwnb);
		testInsert2.postorder_traverse(&dwnb);
	}

	{
		gt.setName(path + "testInsert2_search");
		ryimTestTimer timer("rbt search 2");
		const Ryim::__RedBlackTreeNode<char>* re = testInsert2.search('T');
		if (re)
			std::cout << re->element << std::endl;
		else
		{
			std::cout << "can't find" << std::endl;
		}
		testInsert2.inorder_traverse(&gt);
	}

	{
		ryimTestTimer timer("rbt search 3");
		Ryim::arraylist<char> result;
		testInsert2.search(testInsert2.getRoot(), result, 'F', 'T');
		std::cout << "the RBT: ";
		testInsert2.inorder_traverse(&dwnb);
		std::cout << "the elements between F and T: ";
		for each (auto element in result)
		{
			std::cout << element << ", ";
		}
		std::cout << std::endl;
	}

	{
		gt.setName(path + "testInsert2_insert");
		ryimTestTimer timer("rbt insert");
		testInsert2.insert('T');
		testInsert2.inorder_traverse(&gt);
		testInsert2.setBoundary(3);
		testInsert2.preorder_traverse(&dwnb);
		testInsert2.inorder_traverse(&dwnb);
		testInsert2.postorder_traverse(&dwnb);
	}

	{
		ryimTestTimer timer("rbt getMin");
		const Ryim::__RedBlackTreeNode<char>* re = testInsert2.getMin();
		if (re)
			std::cout << re->element << std::endl;
		else
		{
			std::cout << "can't find" << std::endl;
		}
		testInsert2.inorder_traverse(&dwnb);
	}

	{
		ryimTestTimer timer("rbt getMax");
		const Ryim::__RedBlackTreeNode<char>* re = testInsert2.getMax();
		if (re)
			std::cout << re->element << std::endl;
		else
		{
			std::cout << "can't find" << std::endl;
		}
		testInsert2.inorder_traverse(&dwnb);
		std::cout << std::endl;
		testInsert2.makeDot(path + "testInsert2_getMax");
		graphvizHelper::command(wpath, L"testInsert2_getMax");
	}

	{
		ryimTestTimer timer("rbt eraseMin");
		testInsert2.eraseMin();
		testInsert2.inorder_traverse(&dwnb);
	}

	{
		ryimTestTimer timer("rbt eraseMax");
		testInsert2.eraseMax();
		testInsert2.inorder_traverse(&dwnb);
	}

	{
		ryimTestTimer timer("rbt erase1");
		testInsert2.erase('B');
		testInsert2.inorder_traverse(&dwnb);
		std::cout << std::endl;
		testInsert2.makeDot(path + "testInsert2_erase1");
		graphvizHelper::command(wpath, L"testInsert2_erase1");
	}
}