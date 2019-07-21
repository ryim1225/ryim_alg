#ifndef _R_TREE_H_
#define _R_TREE_H_
#include "rIterator.h"
#include "rUtility.h"
#include "rArrayList.h"
#include "rStack.h"
#include "rQueue.h"
#include <tuple>
#include <fstream>
#include <string>

#include <deque>
#include <stack>
#include <vector>

#define  PARENT_NODE   0
#define  LEFT_OR_RIGHT 1


namespace Ryim
{
    namespace TreeTools
    {
        static const bool RED = true;
        static const bool BLACK = false;

        template <typename T>
        class DealWithNodeBase
        {
        public:
            virtual void init()
            {
            }

            virtual void process(T e)
            {
                std::cout << e << ' ';
            }

            virtual void end()
            {
                std::cout << std::endl;
            }
        };

        template <typename T>
        class generatetxt : public DealWithNodeBase<T>
        {
        public:
            generatetxt():
                m_pathname("graphgv_default")
            {
            }

            ~generatetxt()
            {
                if (fs.is_open())
                    fs.close();
            }

            void setName(std::string pathname)
            {
                m_pathname = pathname;
            }

            virtual void init()
            {
                m_pathname += std::string(".txt");
                fs.open(m_pathname, std::ios::trunc);
            }

            virtual void process(T e)
            {
                fs << e << '\n';
            }

            virtual void end()
            {
                fs.close();
            }

        private:
            std::ofstream fs;
            std::string m_pathname;
        };
    }

    template <typename Elem>
    struct __BinaryTreeNode
    {
        Elem element;
        __BinaryTreeNode * left_child;
        __BinaryTreeNode * right_child;
        __BinaryTreeNode * parent;
    };

    template <typename Elem>
    struct __RedBlackTreeNode
    {
        Elem element;
        __RedBlackTreeNode * left_child;
        __RedBlackTreeNode * right_child;
        __RedBlackTreeNode * parent;
        bool color;
    };
    ///////////////////////////////////////////
    //
    // commonly binary tree
    //
    ///////////////////////////////////////////
    template <typename Elem, typename NodeType = __BinaryTreeNode<Elem>, typename Alloc = std::allocator<NodeType> >
    class BinaryTree
    {
    public:
        typedef BinaryTree<Elem, Alloc> _Myt;
        typedef typename NodeType* nodeptr;
        typedef typename const NodeType* const_nodeptr;

        typedef typename Elem value_type;
        typedef typename std::size_t size_type;
        typedef typename std::ptrdiff_t difference_type;
        typedef typename Elem* pointer;
        typedef typename const Elem* const_pointer;
        typedef typename Elem& reference;
        typedef typename const Elem& const_reference;

    public:
        BinaryTree() :
            m_root(new NodeType()),
            m_size(0),
            m_nBoundary(100)
        {
            m_nil = m_root;
        }

        virtual ~BinaryTree()
        {
            removeall();
        }

        virtual void insert(const_reference value) = 0;
        virtual void erase(const_reference value)  = 0;
        virtual void eraseMin() = 0;
        virtual void eraseMax() = 0;

        void removeall()
        {
            std::deque<nodeptr> nodeQueue;
             nodeQueue.push_back(m_root);

            while (!nodeQueue.empty())
            {
                nodeptr currentNode = nodeQueue.front();
                nodeQueue.pop_front();
                if (!isNIL(currentNode->left_child)) { nodeQueue.push_back(currentNode->left_child); }
                if (!isNIL(currentNode->right_child)) { nodeQueue.push_back(currentNode->right_child); }
                freeNode(currentNode);
            }
            freeNode(m_nil);
            return;
        }

        const_nodeptr getRoot()const
        {
            return m_root;
        }

        size_type getSize()const
        {
            return m_size;
        }

        bool isEmpty()const
        {
            return (m_root == m_nil);
        }

        void setBoundary(size_type boundary)
        {
            m_nBoundary = boundary;
        }

        void preorder_traverse(TreeTools::DealWithNodeBase<const_reference>*  pProcessNode)
        {
            pProcessNode->init();
            if (m_size < m_nBoundary)
                preorder_traverse_recurrence(m_root, pProcessNode);
            else if ((m_size <= m_nBoundary + 50) && (m_size > m_nBoundary))
                preorder_traverse_stack(pProcessNode);
            else
                preorder_traverse_loop(pProcessNode);
            pProcessNode->end();
        }

        void inorder_traverse(TreeTools::DealWithNodeBase<const_reference>*  pProcessNode)
        {
            pProcessNode->init();
            if (m_size < m_nBoundary)
                inorder_traverse_recurrence(m_root, pProcessNode);
            else if ((m_size <= m_nBoundary + 50) && (m_size > m_nBoundary))
                inorder_traverse_stack(pProcessNode);
            else
                inorder_traverse_loop(pProcessNode);
            pProcessNode->end();
        }

        void postorder_traverse(TreeTools::DealWithNodeBase<const_reference>*  pProcessNode)
        {
            pProcessNode->init();
            if (m_size <= m_nBoundary)
                postorder_traverse_recurrence(m_root, pProcessNode);
            else if ((m_size <= m_nBoundary + 50) && (m_size > m_nBoundary))
                postorder_traverse_stack(pProcessNode);
            else
                postorder_traverse_loop(pProcessNode);
            pProcessNode->end();
        }

        void layer_traverse(TreeTools::DealWithNodeBase<const_reference>*  pProcessNode)
        {
            std::deque<nodeptr> nodeQueue;
             nodeQueue.push_back(m_root);

            pProcessNode->init();
            while (!nodeQueue.empty())
            {
                nodeptr currentNode = nodeQueue.front();
                nodeQueue.pop_front();
                pProcessNode->process(currentNode->element);
                if (!isNIL(currentNode->left_child)) { nodeQueue.push_back(currentNode->left_child); }
                if (!isNIL(currentNode->right_child)) { nodeQueue.push_back(currentNode->right_child); }
            }
            pProcessNode->end();
            return;
        }

        virtual void makeDot(std::string fullpath)
        {
            int nodeId = 0;
            std::deque<std::pair<int, nodeptr> > nodeQueue;
            nodeQueue.push_back(std::pair<int, nodeptr>(nodeId, m_root));

            Ryim::arraylist<std::tuple<int, int, int> > relation;
            relation.reserve(m_size + 1);

            // open file and write dot head
            std::ofstream fs;
            fs.open(fullpath + ".gv", std::ios::trunc);
            fs << "digraph btree{\n";
            fs << " node [shape = record,height=.1];\n";
            
            // write node label
            while (!nodeQueue.empty())
            {
                std::pair<int, nodeptr> currentNode = nodeQueue.front();
                nodeQueue.pop_front();
                fs << " node"<< currentNode.first << "[label = \"<f0> | <f1>" << (currentNode.second)->element << " | <f2>\"];\n";

                nodeptr left_child = (currentNode.second)->left_child;
                nodeptr right_child = (currentNode.second)->right_child;
                std::tuple<int, int, int> tupleRelation(-1, -1, -1);
                std::get<0>(tupleRelation) = currentNode.first;

                if (!isNIL(left_child))
                {
                    nodeQueue.push_back(std::pair<int, nodeptr>(++nodeId, left_child));
                    std::get<1>(tupleRelation) = nodeId;
                }
                if (!isNIL(right_child))
                {
                    nodeQueue.push_back(std::pair<int, nodeptr>(++nodeId, right_child));
                    std::get<2>(tupleRelation) = nodeId;
                }
                relation.push_back(tupleRelation);
            }

            // write the relation, which node to node
            for (auto currentTuple = relation.begin(); currentTuple != relation.end(); ++currentTuple)
            {
                int fatherNodeId     = std::get<0>(*currentTuple);
                int leftchildNodeId  = std::get<1>(*currentTuple);
                int rightchildNodeId = std::get<2>(*currentTuple);

                if (leftchildNodeId > 0)
                {
                    fs << " \"node" << fatherNodeId << "\":f0 -> \"node" << leftchildNodeId << "\":f1;\n";
                }
                if (rightchildNodeId > 0)
                {
                    fs << " \"node" << fatherNodeId << "\":f2 -> \"node" << rightchildNodeId << "\":f1;\n";
                }
            }

            // write dot tail
            fs << "}";
            return;
        }

        inline bool isNIL(const_nodeptr node) const
        {
            return (m_nil == node);
        }

    protected:
        void freeNode(nodeptr node)
        {
            m_alloc.destroy(node);
            m_alloc.deallocate(node, 1);
        }

    private:
        void preorder_traverse_recurrence(nodeptr pNode, TreeTools::DealWithNodeBase<const_reference>*  pProcessNode)
        {
            if (!isNIL(pNode))
            {
                pProcessNode->process(pNode->element);
                if (!isNIL(pNode->left_child))
                    preorder_traverse_recurrence(pNode->left_child, pProcessNode);
                if (!isNIL(pNode->right_child))
                    preorder_traverse_recurrence(pNode->right_child, pProcessNode);
            }
            return;
        }

        void inorder_traverse_recurrence(nodeptr pNode, TreeTools::DealWithNodeBase<const_reference>*  pProcessNode)
        {
            if (!isNIL(pNode))
            {
                if (!isNIL(pNode->left_child))
                    inorder_traverse_recurrence(pNode->left_child, pProcessNode);

                pProcessNode->process(pNode->element);

                if (!isNIL(pNode->right_child))
                    inorder_traverse_recurrence(pNode->right_child, pProcessNode);
            }
            return;
        }

        void postorder_traverse_recurrence(nodeptr pNode, TreeTools::DealWithNodeBase<const_reference>*  pProcessNode)
        {
            if (!isNIL(pNode))
            {
                if (!isNIL(pNode->left_child))
                    postorder_traverse_recurrence(pNode->left_child, pProcessNode);
                if (!isNIL(pNode->right_child))
                    postorder_traverse_recurrence(pNode->right_child, pProcessNode);
                pProcessNode->process(pNode->element);
            }
            return;
        }

        void preorder_traverse_stack(TreeTools::DealWithNodeBase<const_reference>*  pProcessNode)
        {
            std::stack<nodeptr>* nodeStack = new std::stack<nodeptr>();
            nodeptr currentNode = m_root;

            while ((!nodeStack->empty()) || !isNIL(currentNode))
            {
                while (!isNIL(currentNode))  //  push all left child nodes into stack
                {
                    pProcessNode->process(currentNode->element);
                    nodeStack->push(currentNode);
                    currentNode = currentNode->left_child;
                }
                currentNode = nodeStack->top();
                nodeStack->pop();
                currentNode = currentNode->right_child; // shift to right child node
            }
            delete nodeStack;
            return;
        }

        void inorder_traverse_stack(TreeTools::DealWithNodeBase<const_reference>*  pProcessNode)
        {
            std::stack<nodeptr>* nodeStack = new std::stack<nodeptr>();
            nodeptr currentNode = m_root;

            while ((!nodeStack->empty()) || !isNIL(currentNode))
            {
                while (!isNIL(currentNode))  //  push all left child nodes into stack
                {
                    nodeStack->push(currentNode);
                    currentNode = currentNode->left_child;
                }
                currentNode = nodeStack->top();
                nodeStack->pop();
                pProcessNode->process(currentNode->element);
                currentNode = currentNode->right_child; // shift to right child node
            }
            delete nodeStack;
            return;
        }

        void postorder_traverse_stack(TreeTools::DealWithNodeBase<const_reference>*  pProcessNode)
        {
            if (isNIL(m_root)) return;
            std::stack<nodeptr>* nodeStack = new std::stack<nodeptr>();
            nodeStack->push(m_root);
            nodeptr currentNode = m_nil;
            nodeptr prevNode = m_nil;

            while (!nodeStack->empty())
            {
                currentNode = nodeStack->top();
                if (
                    ( !isNIL(prevNode) && ( (currentNode->left_child == prevNode) || (currentNode->right_child == prevNode) ) ) ||
                    (isNIL(currentNode->left_child) && isNIL(currentNode->right_child))
                    )
                {
                    pProcessNode->process(currentNode->element);
                    nodeStack->pop();
                    prevNode = currentNode;
                }
                else
                {
                    if (!isNIL(currentNode->right_child))
                    {
                        nodeStack->push(currentNode->right_child);
                    }
                    if (!isNIL(currentNode->left_child))
                    {
                        nodeStack->push(currentNode->left_child);
                    }
                }
            }
            delete nodeStack;
            return;
        }

        void preorder_traverse_loop(TreeTools::DealWithNodeBase<const_reference>*  pProcessNode)
        {
            nodeptr currentNode = m_root;
            nodeptr prevNode = m_nil;
            while (!isNIL(currentNode))
            {
                if (isNIL(currentNode->left_child))
                {
                    pProcessNode->process(currentNode->element);
                    currentNode = currentNode->right_child;
                }
                else
                {
                    prevNode = currentNode->left_child;
                    while (!isNIL(prevNode->right_child) && prevNode->right_child != currentNode)
                    {
                        prevNode = prevNode->right_child;
                    }
                    if (isNIL(prevNode->right_child))
                    {
                        prevNode->right_child = currentNode;
                        pProcessNode->process(currentNode->element);
                        currentNode = currentNode->left_child;
                    }
                    else
                    {
                        prevNode->right_child = m_nil;
                        currentNode = currentNode->right_child;
                    }
                }
            }
        }
        void inorder_traverse_loop(TreeTools::DealWithNodeBase<const_reference>*  pProcessNode)
        {			
            nodeptr pCurrentNode = m_root;
            nodeptr pPrevNode = m_nil;
            while (!isNIL(pCurrentNode))
            {
                if (isNIL(pCurrentNode->left_child))
                {
                    pProcessNode->process(pCurrentNode->element);
                    pCurrentNode = pCurrentNode->right_child;
                }
                else
                {
                    pPrevNode = pCurrentNode->left_child;
                    while (!isNIL(pPrevNode->right_child) && pPrevNode->right_child != pCurrentNode)
                    { 
                        pPrevNode = pPrevNode->right_child;
                    }
                    if (isNIL(pPrevNode->right_child))
                    {  
                        pPrevNode->right_child = pCurrentNode;
                        pCurrentNode = pCurrentNode->left_child;
                    }
                    else
                    {
                        pPrevNode->right_child = m_nil;  
                        pProcessNode->process(pCurrentNode->element);
                        pCurrentNode = pCurrentNode->right_child;
                    }
                }
            }
        }

        // TO DO...
        void postorder_traverse_loop(TreeTools::DealWithNodeBase<const_reference>*  pProcessNode)
        {
        
        }

    protected:
        nodeptr   m_root;
        nodeptr   m_nil;
        size_type m_size;
        Alloc	  m_alloc;

    private:
        size_type m_nBoundary;
    };

    ////////////////////////////////////////////////////
    //Definition: A binary search tree (BST) is a binary tree where each node has a Comparable key
    //  (and an associated value) and satisfies the restriction that the key in any node is larger than 
    //   the keys in all nodes in that node's left subtree and 
    //   smaller than the keys in all nodes in that node's right subtree.
    //
    //Analysis: The running times of algorithms on binary search trees depend on the shapes of the trees,
    //   which, in turn, depends on the order in which keys are inserted.
    //   It is reasonable, for many applications, to use the following simple model : 
    //   We assume that the keys are(uniformly) random, or , equivalently, that they are inserted in random order.
    //Proposition: Search hits in a BST built from N random keys requires ~2 ln N(about 1.39 lg N) compares on the average.
    //Proposition: Insertion and search misses in a BST built from N random keys requires 
    //   ~2 ln N(about 1.39 lg N) compares on the average.
    //
    // Bibliography:
    //https://algs4.cs.princeton.edu/32bst/
    //<<Introduction to Algorithms>>
    ///////////////////////////////////////////////////
    template <typename Elem, typename NodeType = __BinaryTreeNode<Elem>, typename Alloc = std::allocator<NodeType> >
    class BinarySearchTree : public BinaryTree<Elem, NodeType, Alloc>
    {
    public:
        typedef BinarySearchTree<Elem, NodeType, Alloc> _Myt;
        typedef typename NodeType* nodeptr;
        typedef typename const NodeType* const_nodeptr;

        typedef typename Elem value_type;
        typedef typename std::size_t size_type;
        typedef typename std::ptrdiff_t difference_type;
        typedef typename Elem* pointer;
        typedef typename const Elem* const_pointer;
        typedef typename Elem& reference;
        typedef typename const Elem& const_reference;

    public:
        BinarySearchTree()
        {
        }

        ~BinarySearchTree()
        {
        }

#if _MSC_VER  < 1800
#else
        BinarySearchTree(std::initializer_list<value_type> initList)
        {
            for (auto i = initList.begin(); i != initList.end(); ++i)
            {
                _insert(m_root, *i);
            }
        }

        _Myt& operator=(std::initializer_list<value_type> initList)
        {
            for (auto i = initList.begin(); i != initList.end(); ++i)
            {
                _insert(m_root, *i);
            }
            return (*this);
        }
#endif

        virtual void insert(const_reference value)
        {
            _insert(m_root, value);
            return;
        }
        
        // this has a bit tricky in BST
        virtual void erase(const_reference value)
        {
            nodeptr node_find = _search(m_root, value);
            if (isNIL(node_find)) return;

            nodeptr x = nullptr;
            // case 1: a node have no child.
            if (isNIL(node_find->right_child) && isNIL(node_find->left_child))
            {
                // deal with the node that we want to erase is root node. 
                if (m_root == node_find)
                    m_root = m_nil;
            }
            // case 2: a node have two childs.
            else if (!isNIL(node_find->right_child) && !isNIL(node_find->left_child))
            {
                x = getSuccessor(node_find);
                if (x->parent->left_child == x)
                    x->parent->left_child = x->right_child;
                else
                    x->parent->right_child = x->right_child;

                x->left_child = node_find->left_child;
                x->right_child = node_find->right_child;

                transplant(node_find, x);
            }
            // case3: a node have only one child.
            else
            {
                if (!isNIL(node_find->left_child))
                    x = node_find->left_child;
                else
                    x = node_find->right_child;

                transplant(node_find, x);
            }

            freeNode(node_find);
            --m_size;
        }

        virtual void eraseMin()
        {
            nodeptr pMinNode = removeMin(m_root);
            freeNode(pMinNode);
            --m_size;

        }

        virtual void eraseMax()
        {
            nodeptr pMaxNode = removeMax(m_root);
            freeNode(pMaxNode);
            --m_size;

        }

        const_nodeptr getMin()
        {
            const_nodeptr mini = getMin(m_root);
            if (isNIL(mini)) return nullptr;
            return mini;
        }

        const_nodeptr getMax()
        {
            const_nodeptr maxi = getMax(m_root);
            if (isNIL(maxi)) return nullptr;
            return maxi;
        }

        const_nodeptr floor(const_reference value)
        {
            nodeptr floor_value = floor(m_root, value);
            if (isNIL(floor_value))
                return nullptr;
            return floor_value;
        }

        const_nodeptr ceiling(const_reference value)
        {
            nodeptr ceiling_value = ceiling(m_root, value);
            if (isNIL(ceiling_value))
                return nullptr;
            return ceiling_value;
        }

        const_nodeptr search(const_reference value)
        {
            const_nodeptr find = _search(m_root,  value);
            if (isNIL(find)) return nullptr;
            return find;
        }

        void search(const_nodeptr root, Ryim::arraylist<value_type>& elements, const_reference low, const_reference high)
        {
            if (isNIL(root)) return;
            int cmplow  = Ryim::AlgTools::compare<value_type>()(low,  root->element);
            int cmphigh = Ryim::AlgTools::compare<value_type>()(high, root->element);

            if (cmplow < 0)
                search(root->left_child, elements, low, high);
            if (cmplow <= 0 && cmphigh >= 0)
                elements.push_back(root->element);
            if (cmphigh > 0)
                search(root->right_child, elements, low, high);
            return;
        }

    protected:
        nodeptr getMin(nodeptr root)
        {
            if (isNIL(root)) return m_nil;
            while (!isNIL(root->left_child))
            {
                root = root->left_child;
            }
            return root;
        }

        nodeptr getMax(nodeptr root)
        {
            if (isNIL(root)) return m_nil;
            while (!isNIL(root->right_child))
            {
                root = root->right_child;
            }
            return root;
        }

        const_nodeptr floor(nodeptr root, const_reference value)
        {
            nodeptr floor_value = m_nil;
            if (isNIL(root)) { return m_nil; }
            int cmp = AlgTools::compare<Elem>()(value, root->element);

            if (cmp < 0)
                return floor(root->left_child, value);
            else if (0 == cmp)
                return root;
            else
                floor_value = floor(root->right_child, value);
            if (!isNIL(floor_value))
                return floor_value;
            else
                return root;
        }

        const_nodeptr ceiling(nodeptr root, const_reference value)
        {
            nodeptr ceiling_value = m_nil;
            if (isNIL(root)) { return m_nil; }
            int cmp = AlgTools::compare<Elem>()(value, root->element);

            if (cmp < 0)
                return ceiling(root->right_child, value);
            else if (0 == cmp)
                return root;
            else
                ceiling_value = ceiling(root->left_child, value);

            if (!isNIL(ceiling_value))
                return ceiling_value;
            else
                return root;
        }

        nodeptr getSuccessor(nodeptr root)
        {
            if (!isNIL(root->right_child))
                return getMin(root->right_child);

            nodeptr y = root->parent;
            while (!isNIL(y) && root == y->right_child)
            {
                root = y;
                y = y->parent;
            }
            return y;
        }

        nodeptr getPredecessor(nodeptr root)
        {
            if (!isNIL(root->left_child))
                return getMax(root->left_child);

            nodeptr y = root->parent;
            while (!isNIL(y) && root == y->left_child)
            {
                root = y;
                y = y->parent;
            }
            return y;
        }

        //In order to move subtrees around within the binary search tree, we define a
        //subroutine TRANSPLANT, which replaces one subtree as a child of its parent with
        //another subtree.When TRANSPLANT replaces the subtree rooted at node u with
        //the subtree rooted at node v, node u's parent becomes node v's parent, and u's
        //parent ends up having v as its appropriate child.
        void transplant(nodeptr u, nodeptr v)
        {
            if (isNIL(u->parent))
            {
                // deal with the node that we want to erase is root node.
                m_root = v;
            }
            else if (u == u->parent->left_child)
            {
                u->parent->left_child = v;
            }
            else
            {
                u->parent->right_child = v;
            }
            v->parent = u->parent;
        }

        nodeptr removeMin(nodeptr root)
        {
            nodeptr currentNode = root;
            nodeptr currentNode_prev = currentNode;
            if (isNIL(currentNode)) return nullptr;
            while (!isNIL(currentNode->left_child))
            {
                currentNode_prev = currentNode;
                currentNode = currentNode->left_child;
            }
            
            if (currentNode_prev == currentNode)
            {
                m_root = currentNode->right_child;
                currentNode->right_child->parent = m_nil;
            }
            else
            {
                currentNode_prev->left_child = currentNode->right_child;
                if (!isNIL(currentNode->right_child))
                    currentNode->right_child->parent = currentNode_prev;
            }
            return currentNode;
        }

        nodeptr removeMax(nodeptr root)
        {
            nodeptr currentNode = root;
            nodeptr currentNode_prev = currentNode;
            if (isNIL(currentNode)) return nullptr;
            while (!isNIL(currentNode->right_child))
            {
                currentNode_prev = currentNode;
                currentNode = currentNode->right_child;
            }

            if (currentNode_prev == currentNode)
            {
                m_root = currentNode->left_child;
                currentNode->left_child->parent = m_nil;
            }
            else
            {
                currentNode_prev->right_child = currentNode->left_child;
                if (!isNIL(currentNode->left_child))
                    currentNode->left_child->parent = currentNode_prev;
            }
            return currentNode;
        }

        nodeptr _search(nodeptr root, const_reference value)
        {
            while (!isNIL(root) && (value != root->element))
            {
                if (value < root->element)
                    root = root->left_child;
                else if (value > root->element)
                    root = root->right_child;
            }
            return root;
        }

        nodeptr _insert(nodeptr root, const_reference value)
        {
            nodeptr prevNode = m_nil;
            while (!isNIL(root))
            {
                prevNode = root;
                if (value < root->element)
                    root = root->left_child;
                else 
                    root = root->right_child;
            }

            nodeptr newNode = m_alloc.allocate(1);
            newNode->element = value;
            newNode->left_child = newNode->right_child = m_nil;
            newNode->parent = prevNode;

            if (isNIL(prevNode))
                m_root = newNode;
            else
            {
                if (value < prevNode->element)
                    prevNode->left_child = newNode;
                else
                    prevNode->right_child = newNode;
            }

            ++m_size;
            return newNode;
        }
    };

    ////////////////////////////////////////////////////
    //Definition: Red-black BSTs. The insertion algorithm for 2-3 trees just described is not difficult to understand.
    //            We consider a simple representation known as a red-black BST that leads to a natural implementation.
    //
    //Proposition: The height of a red-blackBST with N nodes is no more than 2 lg N.
    //Proposition:n a red-black BST, the following operations take logarithmic time in the worst case: search, insertion, 
    //            finding the minimum, finding the maximum, floor, ceiling, rank, select,
    //            delete the minimum, delete the maximum, delete, and range count.
    //Property. The average length of a path from the root to a node in a red-black BST with N nodes is ~1.00 lg N.
    // Bibliography:
    //https://algs4.cs.princeton.edu/33balanced/
    //<<Introduction to Algorithms>>
    ///////////////////////////////////////////////////
    template <typename Elem, typename NodeType = __RedBlackTreeNode<Elem>, typename Alloc = std::allocator<NodeType> >
    class RedBlackTree : public BinarySearchTree<Elem, NodeType, Alloc>
    {
    public:
        typedef RedBlackTree<Elem, NodeType, Alloc> _Myt;
        typedef typename NodeType* nodeptr;
        typedef typename const NodeType* const_nodeptr;

        typedef typename Elem value_type;
        typedef typename std::size_t size_type;
        typedef typename std::ptrdiff_t difference_type;
        typedef typename Elem* pointer;
        typedef typename const Elem* const_pointer;
        typedef typename Elem& reference;
        typedef typename const Elem& const_reference;
    public:
        RedBlackTree():m_unRecurrenceSentry(1){}
#if _MSC_VER  < 1800
#else
        RedBlackTree(std::initializer_list<value_type> initList)
        {
            m_unRecurrenceSentry = 1;
            for (auto i = initList.begin(); i != initList.end(); ++i)
            {
                insert_rbt(*i);
            }
        }

        _Myt& operator=(std::initializer_list<value_type> initList) 
        {
            for (auto i = initList.begin(); i != initList.end(); ++i)
            {
                insert_rbt(*i);
            }
            return (*this);
        }
#endif
        virtual void insert(const_reference value) 
        {
            insert_rbt(value);
        }

        virtual void erase(const_reference value)
        {
            switch (m_unRecurrenceSentry)
            {
            case 1:
                delete_none_recurrence_rbt(value);
                break;
            case 2:
                delete_recurrence_rbt(value);
                break;
            default:
                delete_none_recurrence_rbt(value);
                break;
            }
        }

        virtual void eraseMin()
        {
            switch (m_unRecurrenceSentry)
            {
            case 1:
            {
                const_nodeptr min_find = getMin();
                delete_none_recurrence_rbt(min_find->element);
                break;
            }
            case 2:
                deleteMin_recurrence_rbt();
                break;
            default:
            {
                const_nodeptr min_find = getMin();
                delete_none_recurrence_rbt(min_find->element);
                break;
            }
            }
        }

        virtual void eraseMax()
        {
            switch (m_unRecurrenceSentry)
            {
            case 1:
            {
                const_nodeptr min_find = getMax();
                delete_none_recurrence_rbt(min_find->element);
                break;
            }
            case 2:
                deleteMax_recurrence_rbt();
                break;
            default:
            {
                const_nodeptr min_find = getMax();
                delete_none_recurrence_rbt(min_find->element);
                break;
            }
            }
        }

        void setRecurrenceSentry(unsigned int sentry)
        {
            m_unRecurrenceSentry = sentry;
        }

        unsigned int getRecurrenceSentry(unsigned int sentry) const
        {
            return this->m_unRecurrenceSentry;
        }

        virtual void makeDot(std::string fullpatth)
        {
            int nodeId = 0;
            std::deque<std::pair<int, nodeptr> > nodeQueue;
            nodeQueue.push_back(std::pair<int, nodeptr>(nodeId, m_root));

            Ryim::arraylist<std::tuple<int, int, int> > relation;
            relation.reserve(m_size + 1);

            // open file and write dot head
            std::ofstream fs;
            fs.open(fullpatth + ".gv", std::ios::trunc);
            fs << "digraph rbtree{\n";
            fs << " node [shape = record,height=.1];\n";

            // write node label
            while (!nodeQueue.empty())
            {
                std::pair<int, nodeptr> currentNode = nodeQueue.front();
                nodeQueue.pop_front();
                std::string rb("gray");
                if (currentNode.second->color)
                    rb = "red";
                    
                fs << " node" << currentNode.first << "[label = \"<f0> | <f1>" << 
                    (currentNode.second)->element << " | <f2>\", style=filled, color=" << rb << "];\n";

                nodeptr left_child = (currentNode.second)->left_child;
                nodeptr right_child = (currentNode.second)->right_child;
                std::tuple<int, int, int> tupleRelation(-1, -1, -1);
                std::get<0>(tupleRelation) = currentNode.first;

                if (!isNIL(left_child))
                {
                    nodeQueue.push_back(std::pair<int, nodeptr>(++nodeId, left_child));
                    std::get<1>(tupleRelation) = nodeId;
                }
                if (!isNIL(right_child))
                {
                    nodeQueue.push_back(std::pair<int, nodeptr>(++nodeId, right_child));
                    std::get<2>(tupleRelation) = nodeId;
                }
                relation.push_back(tupleRelation);
            }

            // write the relation, which node to node
            for (auto currentTuple = relation.begin(); currentTuple != relation.end(); ++currentTuple)
            {
                int fatherNodeId = std::get<0>(*currentTuple);
                int leftchildNodeId = std::get<1>(*currentTuple);
                int rightchildNodeId = std::get<2>(*currentTuple);

                if (leftchildNodeId > 0)
                {
                    fs << " \"node" << fatherNodeId << "\":f0 -> \"node" << leftchildNodeId << "\":f1;\n";
                }
                if (rightchildNodeId > 0)
                {
                    fs << " \"node" << fatherNodeId << "\":f2 -> \"node" << rightchildNodeId << "\":f1;\n";
                }
            }

            // write dot tail
            fs << "}";
            return;
        }

    private:
        void insert_rbt(const_reference value)
        {
            switch(m_unRecurrenceSentry)
            { 
            case 1:
                insert_none_recurrence_rbt(value);
                break;
            case 2:
                insert_recurrence_rbt(value);
                break;
            default:
                insert_none_recurrence_rbt(value);
                break;
            }
        }

        ///////////////////////////////////////////////////////////////////////
        //              the rbt recurrence methods 
        //////////////////////////////////////////////////////////////////////
        void insert_recurrence_rbt(const_reference value)
        {
            m_root = insert_recurrence_rbt(m_root, value);
            m_root->color = TreeTools::BLACK;
        }

        nodeptr insert_recurrence_rbt(nodeptr node, const_reference value)
        {
            if (isNIL(node))
            {
                nodeptr newNode = m_alloc.allocate(1);
                newNode->element = value;
                newNode->left_child = newNode->right_child = newNode->parent = m_nil;
                newNode->color = TreeTools::RED;
                ++m_size;
                return newNode;
            }

            int cmp = AlgTools::compare<value_type>()(value, node->element);

            if (cmp < 0)
                node->left_child = insert_recurrence_rbt(node->left_child, value);
            else if (cmp > 0)
                node->right_child = insert_recurrence_rbt(node->right_child, value);
            else
                node->element = value;

             //fix-up any right-leaning links
            if (isRed(node->right_child) && !isRed(node->left_child))
                node = rotateLeft(node);
            if (isRed(node->left_child) && isRed(node->left_child->left_child))
                node = rotateRight(node);
            if (isRed(node->right_child) && isRed(node->left_child))
                flipColors(node);

            return node;
        }

        void deleteMin_recurrence_rbt()
        {
            if (isEmpty()) return;
            if (!isRed(m_root->left_child) && !isRed(m_root->right_child))
                m_root->color = TreeTools::RED;
            m_root = deleteMin_recurrence_rbt(m_root);
            if (!isEmpty()) m_root->color = TreeTools::BLACK;
            --m_size;
        }

        nodeptr deleteMin_recurrence_rbt(nodeptr node)
        {
            if (isNIL(node->left_child)) return m_nil;
            if (!isRed(node->left_child) && !isRed(node->left_child->left_child))
                node = moveRedLeft(node);
            node->left_child = deleteMin_recurrence_rbt(node->left_child);
            return balance(node);
        }

        void deleteMax_recurrence_rbt()
        {
            if (isEmpty())return;
            if (!isRed(m_root->left_child) && !isRed(m_root->right_child))
                m_root->color = TreeTools::RED;
            m_root = deleteMax_recurrence_rbt(m_root);
            if (!isEmpty()) m_root->color = TreeTools::BLACK;
            --m_size;
        }

        nodeptr	deleteMax_recurrence_rbt(nodeptr node)
        {
            if (isRed(node->left_child)) 
                node = rotateRight(node);
            if (isNIL(node->right_child))
                return m_nil;
            if (!isRed(node->right_child) && !isRed(node->right_child->left_child))
                node = moveRedRight(node);
            node->right_child = deleteMax_recurrence_rbt(node->right_child);
            return balance(node);
        }

        void delete_recurrence_rbt(const_reference value)
        {
            if (!isRed(m_root->left_child) && !isRed(m_root->right_child))
                m_root->color = TreeTools::RED;
            m_root = delete_recurrence_rbt(m_root, value);
            if (m_root != m_nil) m_root->color = TreeTools::BLACK;
            --m_size;
        }

        nodeptr delete_recurrence_rbt(nodeptr node, const_reference value)
        {
            if (value < node->element) {
                if (!isRed(node->left_child) && !isRed(node->left_child->left_child))
                    node = moveRedLeft(node);
                node->left_child = delete_recurrence_rbt(node->left_child, value);
            }
            else {
                if (isRed(node->left_child))
                    node = rotateRight(node);
                if ((value == node->element) && isNIL(node->right_child))
                    return m_nil;
                if (!isRed(node->right_child) && !isRed(node->right_child->left_child))
                    node = moveRedRight(node);
                if (value == node->element) {
                    nodeptr x = getMin(node->right_child);
                    node->element = x->element;
                    node->right_child = deleteMin_recurrence_rbt(node->right_child);
                }
                else 
                    node->right_child = delete_recurrence_rbt(node->right_child, value);
            }
            return balance(node);
        }

        ///////helper functions of the rbt recurrence methods /////////////
        bool isRed(const_nodeptr node)
        {
            if (isNIL(node))
                return TreeTools::BLACK;
            return node->color;
        }

        nodeptr rotateLeft(nodeptr node)
        {
            nodeptr x = node->right_child;
            node->right_child = x->left_child;
            if (!isNIL(x->left_child))
                x->left_child->parent = node;
            x->parent = node->parent;
            if (isNIL(node->parent))
                m_root = x;
            else
            {
                if (node->parent->left_child == node)
                    node->parent->left_child = x;
                else
                    node->parent->right_child = x;
            }
            x->left_child = node;
            node->parent = x;
            x->color = node->color;
            node->color = TreeTools::RED;
            return x;
        }

        nodeptr rotateRight(nodeptr node)
        {
            nodeptr x = node->left_child;
            node->left_child = x->right_child;
            if (!isNIL(x->right_child))
                x->right_child->parent = node;
            x->parent = node->parent;
            if (isNIL(node->parent))
                m_root = x;
            else
            {
                if (node->parent->left_child == node)
                    node->parent->left_child = x;
                else
                    node->parent->right_child = x;
            }
            x->right_child = node;
            node->parent = x;
            x->color = node->color;
            node->color = TreeTools::RED;
            return x;
        }

        nodeptr moveRedLeft(nodeptr node)
        {
            //supose the color of node is red, node.left and node.left.left both are black
            //make node.left or node.left.left or node.left.right red
            flipColors(node);
            if (isRed(node->right_child->left_child))
            {
                node->right_child = rotateRight(node->right_child);
                node = rotateLeft(node);
                flipColors(node);
            }
            return node;
        }

        nodeptr moveRedRight(nodeptr node)
        {
            //supose the color of node is red, node.right and node.right.left both are black
            //make node.right or node.right.left or node.right.right red
            flipColors(node);
            if (!isRed(node->left_child->left_child))
            {
                node = rotateRight(node);
                flipColors(node);
            }
            return node;
        }

        nodeptr balance(nodeptr node)
        {
            if (isRed(node->right_child))
                node = rotateLeft(node);
            if (isRed(node->left_child) && isRed(node->left_child->left_child))
                node = rotateRight(node);
            if (isRed(node->right_child) && isRed(node->left_child))
                flipColors(node);

            return node;
        }

        void flipColors(nodeptr node)
        {
            node->color = !node->color;
            node->left_child->color = !node->left_child->color;
            node->right_child->color = !node->right_child->color;
        }

        ///////////////////////////////////////////////////////////////
        //    rbt none recurrence methods
        ///////////////////////////////////////////////////////////////
        void insert_none_recurrence_rbt(const_reference value)
        {
            nodeptr newNode = _insert(m_root, value);
            fixRbtAfterInsertion(newNode);
        }

        void fixRbtAfterInsertion(nodeptr newNode)
        {
            if (isNIL(newNode))
                return;

            nodeptr y = m_nil;
            newNode->color = TreeTools::RED;

            while (isRed(newNode->parent))
            {
                if (newNode->parent == newNode->parent->parent->left_child)
                {
                    y = newNode->parent->parent->right_child;
                    if (isRed(y))
                    {
                        // Case 1: z's uncle y is red
                        newNode->parent->color = TreeTools::BLACK;
                        y->color = TreeTools::BLACK;
                        newNode->parent->parent->color = TreeTools::RED;
                        newNode = newNode->parent->parent;
                    }
                    else
                    {
                        if (newNode == newNode->parent->right_child)
                        {
                            // Case 2: z's uncle y is black and z is a right child
                            newNode = newNode->parent;
                            rotateLeft_no_color(newNode);
                        }
                        // Case 3: z's uncle y is black and z is a left child
                        newNode->parent->color = TreeTools::BLACK;
                        newNode->parent->parent->color = TreeTools::RED;
                        rotateRight_no_color(newNode->parent->parent);
                    }
                }
                else
                {
                    y = newNode->parent->parent->left_child;
                    if (isRed(y))
                    {
                        // Case 1: z's uncle y is red
                        newNode->parent->color = TreeTools::BLACK;
                        y->color = TreeTools::BLACK;
                        newNode->parent->parent->color = TreeTools::RED;
                        newNode = newNode->parent->parent;
                    }
                    else
                    {
                        if (newNode == newNode->parent->left_child)
                        {
                            // Case 2: z's uncle y is black and z is a left child
                            newNode = newNode->parent;
                            rotateRight_no_color(newNode);
                        }
                        // Case 3: z's uncle y is black and z is a right child
                        newNode->parent->color = TreeTools::BLACK;
                        newNode->parent->parent->color = TreeTools::RED;
                        rotateLeft_no_color(newNode->parent->parent);
                    }
                }
            }
            m_root->color = TreeTools::BLACK;
        }

        void delete_none_recurrence_rbt(const_reference value)
        {
            nodeptr node_erase = _search(m_root, value);
            nodeptr x = m_nil;
            nodeptr y = node_erase;
            bool yOriginalColor = y->color;

            if (isNIL(node_erase->left_child))
            {
                x = node_erase->right_child;
                transplant(node_erase, node_erase->right_child);
            }
            else if (isNIL(node_erase->right_child))
            {
                x = node_erase->left_child;
                transplant(node_erase, node_erase->left_child);
            }
            else
            {
                y = getMin(node_erase->right_child);
                yOriginalColor = y->color;
                x = y->right_child;
                if (y->parent == node_erase)
                {
                    x->parent = y;
                }
                else
                {
                    transplant(y, y->right_child);
                    y->right_child = node_erase->right_child;
                    y->right_child->parent = y;
                }
                transplant(node_erase, y);
                y->left_child = node_erase->left_child;
                y->left_child->parent = y;
                y->color = node_erase->color;
            }

            if (yOriginalColor == TreeTools::BLACK)
                fixRbtAfterDelete(x);

            freeNode(node_erase);
            --m_size;
        }

        void fixRbtAfterDelete(nodeptr node)
        {
            nodeptr w = m_nil;
            while (node != m_root && !isRed(node))
            {
                if (node == node->parent->left_child)
                {
                    w = node->parent->right_child;

                    if (isRed(w))
                    {
                        // case1: the color of node's brother is red 
                        w->color = TreeTools::BLACK;
                        node->parent->color = TreeTools::RED;
                        rotateLeft_no_color(node->parent);
                        w = node->parent->right_child;
                    }

                    if (!isRed(w->left_child) &&
                        !isRed(w->right_child)
                        )
                    {
                        // case2: the color of node's brother w is black and the two childs of w both are black
                        w->color = TreeTools::RED;
                        node = node->parent;
                    }
                    else
                    {
                        if (!isRed(w->right_child))
                        {
                            // case3: the color of node's brother w is black, 
                            //        but the left child of w is red and the right child of w is black
                            // and thus we have transformed case3 into case4.
                            w->left_child->color = TreeTools::BLACK;
                            w->color = TreeTools::RED;
                            rotateRight_no_color(w);
                            w = node->parent->right_child;
                        }
                        // case4: the color of node's brother w is black and the two childs of w both are red
                        w->color = node->parent->color;
                        node->parent->color = TreeTools::BLACK;
                        w->right_child->color = TreeTools::BLACK;
                        rotateLeft_no_color(node->parent);
                        node = m_root;
                    }
                }
                else
                {
                    w = node->parent->left_child;

                    if (isRed(w))
                    {
                        // case1: the color of node's brother is red 
                        w->color = TreeTools::BLACK;
                        node->parent->color = TreeTools::RED;
                        rotateLeft_no_color(node->parent);
                        w = node->parent->left_child;
                    }

                    if (!isRed(w->left_child) &&
                        !isRed(w->right_child)
                        )
                    {
                        // case2: the color of node's brother w is black and the two childs of w both are black
                        w->color = TreeTools::RED;
                        node = node->parent;
                    }
                    else
                    {
                        if (!isRed(w->left_child))
                        {
                            // case3: the color of node's brother w is black, 
                            //        but the left child of w is red and the right child of w is black
                            // and thus we have transformed case3 into case4.
                            w->right_child->color = TreeTools::BLACK;
                            w->color = TreeTools::RED;
                            rotateRight_no_color(w);
                            w = node->parent->left_child;
                        }
                        // case4: the color of node's brother w is black and the two childs of w both are red
                        w->color = node->parent->color;
                        node->parent->color = TreeTools::BLACK;
                        w->left_child->color = TreeTools::BLACK;
                        rotateLeft_no_color(node->parent);
                        node = m_root;
                    }
                }
            }
            node->color = TreeTools::BLACK;
        }
        ////////helper functions of the rbt none recurrence methods////////
        void rotateLeft_no_color(nodeptr node)
        {
            nodeptr x = node->right_child;
            node->right_child = x->left_child;
            if (!isNIL(x->left_child))
                x->left_child->parent = node;
            x->parent = node->parent;
            if (isNIL(node->parent))
                m_root = x;
            else
            {
                if (node->parent->left_child == node)
                    node->parent->left_child = x;
                else
                    node->parent->right_child = x;
            }
            x->left_child = node;
            node->parent = x;
        }

        void rotateRight_no_color(nodeptr node)
        {
            nodeptr x = node->left_child;
            node->left_child = x->right_child;
            if (!isNIL(x->right_child))
                x->right_child->parent = node;
            x->parent = node->parent;
            if (isNIL(node->parent))
                m_root = x;
            else
            {
                if (node->parent->left_child == node)
                    node->parent->left_child = x;
                else
                    node->parent->right_child = x;
            }
            x->right_child = node;
            node->parent = x;
        }
    
        private:
            unsigned int m_unRecurrenceSentry;
    };
}
#endif
