#ifndef _R_GRAPH_H_
#define _R_GRAPH_H_

#include <vector>
#include <list>
#include <fstream>
#include <string>
#include <iostream>
#include <stack>
#include <limits>


namespace Ryim
{
	class UndirectedGraph
	{
	public:
		typedef std::list<int> ADJ;
		typedef std::vector<ADJ* > ADJ_ARRAY;	
		typedef std::vector<int> PATH;
		typedef std::vector<bool> MARKED;
	public:
		UndirectedGraph();

		~UndirectedGraph();

		void clearState();

		void clear();

		void initial(int Vertex);

		void initial(std::ifstream& in, const char delim = ',');

		void makeDot(std::ifstream& in, std::string fullpath, const char delim = ',');

		inline int V()const { return m_vertex; };
		inline int E()const { return m_edge; };
		const ADJ* adj(int v);

		void dfs_recurrence(int v);

		void dfs(int v);

		bool hasPathTo(int v);

		void addEdge(int v1, int v2);

	private:
		void split(const std::string& line, std::string& v1, std::string& v2, const char delim = ',');

	private:
		int m_vertex;
		int m_edge;
		ADJ_ARRAY* m_adj;
		std::vector<bool>* m_marked; // check whether dfs() is called by specific vertex 
		std::vector<int>* m_path;
	};

	class DirectedGraph
	{
	public:
		typedef std::list<int> ADJ;
		typedef std::vector<ADJ* > ADJ_ARRAY;
	public:
		DirectedGraph();

		~DirectedGraph();

		void clear();

		void initial(int Vertex);

		void initial(std::ifstream& in, const char delim = ',');

		inline int V()const { return m_vertex; };
		inline int E()const { return m_edge; };
		const ADJ* adj(int v);

		void addEdge(int v1, int v2);

	private:
		void split(const std::string& line, std::string& v1, std::string& v2, const char delim = ',');

	private:
		int m_vertex;
		int m_edge;
		ADJ_ARRAY* m_adj;
	};

	class DirectedDFS
	{
	public:
		typedef std::vector<int> PATH;
		typedef std::vector<bool> MARKED;
		DirectedDFS();
		~DirectedDFS();

		bool init(int vs);

		void clearState(int vs);

		void dfs(DirectedGraph* G, int v);

		bool marked(int v);
	private:
		MARKED* m_marked; // check whether dfs() is called by specific vertex 
		PATH* m_path;

	};
}
#endif
