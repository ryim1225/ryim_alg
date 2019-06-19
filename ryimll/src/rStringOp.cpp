#include "rStringOp.h"

using namespace Ryim;


//////////////////////////////////////////////////////////////////////////
// brute force string search:
// O(patLen * txtLen)
//
// Bibliography:
// https://algs4.cs.princeton.edu/53substring/
//////////////////////////////////////////////////////////////////////////
int SubstringSearch::naive_string_matcher(const std::string &pat, const std::string &txt)
{
	int patLen = pat.length();
	int txtLen = txt.length();
	if (txtLen < patLen) return txtLen;
	int j;
	for (int i = 0; i < txtLen - patLen; i++)
	{
		for (j = 0; j < patLen; j++)
		{
			if (txt.at(i + j) != pat.at(j))
				break;
		}
		if (j == patLen)
			return i; // found
	}
	return txtLen;  // not found
}

//////////////////////////////////////////////////////////////////////////
// Knuth-Morris-Pratt:
// O(patLen + txtLen)
//
// Bibliography:
// https://algs4.cs.princeton.edu/53substring/
//////////////////////////////////////////////////////////////////////////

SubstringSearch::kmpMatcher::kmpMatcher(std::string& p) :m_pattern(p)
{
	m_patLen = m_pattern.size();
	m_LofPS.resize(m_patLen);
	computePrefixSuffix();
}

SubstringSearch::kmpMatcher::~kmpMatcher() {}

void SubstringSearch::kmpMatcher::setPattern(std::string& p)
{
	m_pattern.clear();
	m_pattern.assign(p.begin(), p.end());
	m_patLen = m_pattern.size();
	computePrefixSuffix();
}

bool SubstringSearch::kmpMatcher::KMPsearch(std::string txt, std::vector<int>& results)
{
	int txtLen = txt.length();
	if (txtLen < m_patLen)
	{
		return false;
	}

	int q = -1;

	for (int i = 0; i < txtLen; ++i)
	{
		while (q >= 0 && m_pattern[q + 1] != txt[i])
		{
			q = m_LofPS[q];
		}

		if (m_pattern[q + 1] = txt[i])
			q++;

		if (q == m_patLen)
		{
			results.push_back(i - m_patLen);
			q = m_LofPS[q];
		}
	}
	return true;
}

void SubstringSearch::kmpMatcher::computePrefixSuffix()
{
	m_LofPS[0] = 0;
	int k = 0;

	for (int i = 0; i < m_patLen; ++i)
	{
		while (k > 0 && m_pattern[k + 1] != m_pattern[i])
		{
			k = m_LofPS[k];
		}
		if (m_pattern[k + 1] == m_pattern[i])
		{
			k++;
		}
		m_LofPS[i] = k;
	}
}


/////////////////////////////////////////////////////////
// RegularExp类:正则表达式检索器
// clear:重置整个正则表达式检索器
// NFA:根据正则表达式构造NFA(非确定有限状态自动机)
// Recognize:判断目标文本是否匹配正则表达式
//////////////////////////////////////////////////////

	// 构造函数  
Regexp::RegularExp::RegularExp() :G(nullptr) {}
// 析构函数  
Regexp::RegularExp::~RegularExp() { clear(); }

// 接口函数  
void Regexp::RegularExp::clear()
{
	if (G != nullptr)
	{
		delete G;
		G = nullptr;
	}
}
void Regexp::RegularExp::NFA(std::string regexp)
{
	std::stack <int> ops;
	// 储存正则表达式并获取其长度
	re = regexp;
	M = regexp.length();
	// 构建新的有向图
	G = new DirectedGraph;
	G->initial(M + 1);

	int orOper = 0;
	int lp = 0;
	// 遍历整个正则表达式
	for (int i = 0; i < M; i++) {
		lp = i;     // 储存起始位置
					// 碰到'('或'|'则将该位置压入栈中，即进行括号配对
		if (re[i] == '(' || re[i] == '|')
		{
			ops.push(i);
		}
		else if (re[i] == ')') // 括号配对
		{
			orOper = ops.top();
			ops.pop();
			// 处理括号中有'|'的特殊情况
			if (re[orOper] == '|') {
				lp = ops.top();
				ops.pop();
				// 链接或符号
				G->addEdge(lp, orOper + 1);
				G->addEdge(orOper, i);
			}
			else
				lp = orOper;
		}

		// 当其下一位为闭包操作时
		if (i < M - 1 && re[i + 1] == '*') {
			// 进行双向链接
			G->addEdge(lp, i + 1);
			G->addEdge(i + 1, lp);
		}

		// 特定符号直接连向下一位
		if (re[i] == '(' || re[i] == '*' || re[i] == ')')
			G->addEdge(i, i + 1);
	}
}

bool Regexp::RegularExp::Recognize(std::string txt)
{
	// 构造Bag
	std::vector<int> pc;
	// 构造DFS搜索器
	DirectedDFS *dfs = new DirectedDFS();
	// 根据有向图G初始化DFS搜索器
	dfs->init(G->V());
	// 从第一个顶点开始进行DFS搜索
	dfs->dfs(G, 0);

	// 依次将从第一个顶点可达顶点加入Bag
	for (int v = 0; v < G->V(); v++)
		if (dfs->marked(v))
			pc.push_back(v);

	// 遍历整个文本
	std::vector<int> match;
	for (int i = 0; i < txt.length(); i++)
	{
		match.clear();
		// 构建匹配Bag
		// 遍历所有可达顶点
		for (int v = 0; v < pc.size(); v++)
			if (pc[v] < M)
				if (re[pc[v]] == txt[i] || re[pc[v]] == '.') // 获取所有可能的匹配并加入match
					match.push_back(pc[v] + 1);

		// 重置Bag以及DFS搜索器
		pc.clear();
		dfs->clearState(G->V());
		// 通过有向图G初始化DFS搜索器
		//dfs->init(G->V());
		// 将所有匹配文本对应位置的节点进行DFS搜索
		for (int i = 0; i < match.size(); i++)
			dfs->dfs(G, match[i]);

		// 依次将所有可达节点加入Bag
		for (int v = 0; v < G->V(); v++)
			if (dfs->marked(v))
				pc.push_back(v);
	}

	// 遍历所有可达节点
	for (int i = 0; i < pc.size(); i++)
		if (pc[i] == M) // 判断是否匹配正则表达式
			return true;

	return false;
}