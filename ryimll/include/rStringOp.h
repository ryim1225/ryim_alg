#ifndef _R_STRING_OPERATION_H_
#define _R_STRING_OPERATION_H_

#include "rUtility.h"
#include "rGraph.h"
#include <vector>
#include <stack>
#include <string>


namespace Ryim
{
	namespace SubstringSearch
	{
		//////////////////////////////////////////////////////////////////////////
		// brute force string search:
		// O(patLen * txtLen)
		//
		// Bibliography:
		// https://algs4.cs.princeton.edu/53substring/
		//////////////////////////////////////////////////////////////////////////
		int naive_string_matcher(const std::string &pat, const std::string &txt);


		//////////////////////////////////////////////////////////////////////////
		// Knuth-Morris-Pratt:
		// O(patLen + txtLen)
		//
		// Bibliography:
		// https://algs4.cs.princeton.edu/53substring/
		//////////////////////////////////////////////////////////////////////////
		class kmpMatcher
		{
		public:
			explicit kmpMatcher(std::string& p);

			~kmpMatcher();

			void setPattern(std::string& p);


			bool KMPsearch(std::string txt, std::vector<int>& results);

			void computePrefixSuffix();

		private:
			std::vector<int> m_LofPS;
			std::string m_pattern;
			int m_patLen;
		};
	}

	// Regular Expression
	namespace Regexp
	{
		/////////////////////////////////////////////////////////
		// RegularExp类:正则表达式检索器
		// clear:重置整个正则表达式检索器
		// NFA:根据正则表达式构造NFA(非确定有限状态自动机)
		// Recognize:判断目标文本是否匹配正则表达式
		//////////////////////////////////////////////////////

		class RegularExp
		{
		public:
			// 构造函数  
			RegularExp();
			// 析构函数  
			~RegularExp();

			void clear();

			void NFA(std::string regexp);

			bool Recognize(std::string txt);

		private:
			int M; // 储存正则表达式字符个数  
			std::string re; // 储存正则表达式  
			DirectedGraph *G; // 储存NFA构建的有向图  
		};
	}
}// END Namespace Ryim
#endif