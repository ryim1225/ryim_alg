
#include "rGraph.h"
//#include <vector>
//#include <list>
//#include <fstream>
//#include <string>
//#include <iostream>
//#include <stack>
//#include <limits>


////////////////////////////UndirectedGraph//////////////////////////////////////////////////////////////////////

Ryim::UndirectedGraph::UndirectedGraph() :m_vertex(0)
, m_edge(0)
, m_adj(nullptr)
, m_marked(nullptr)
, m_path(nullptr)
{}

Ryim::UndirectedGraph::~UndirectedGraph()
{
	clear();
}

void Ryim::UndirectedGraph::clearState()
{
	m_path->clear();
	m_path->resize(m_vertex, INT_MIN);
	m_marked->clear();
	m_marked->resize(m_vertex);
}

void Ryim::UndirectedGraph::clear()
{
	if (nullptr != m_path)
	{
		delete m_path;
		m_path = nullptr;
	}

	if (nullptr != m_marked)
	{
		delete m_marked;
		m_marked = nullptr;
	}

	if (nullptr != m_adj)
	{
		for (std::size_t v = 0; v < (m_adj->size()); ++v)
		{
			if (nullptr != (*m_adj)[v])
			{
				delete (*m_adj)[v];
				(*m_adj)[v] = nullptr;
			}
		}
		delete m_adj;
		m_adj = nullptr;
	}
}

void Ryim::UndirectedGraph::initial(int Vertex)
{
	m_vertex = Vertex;
	m_edge = 0;
	m_adj = new ADJ_ARRAY(Vertex);
	m_marked = new MARKED(Vertex, false);
	m_path = new PATH(Vertex, INT_MIN);
	for (int v = 0; v < Vertex; ++v)
	{
		(*m_adj)[v] = new ADJ();
	}
}

void Ryim::UndirectedGraph::initial(std::ifstream& in, const char delim /*= ','*/)
{
	std::string line;
	std::getline(in, line);
	initial(std::stoi(line.c_str()));
	std::getline(in, line);
	int E = std::stoi(line.c_str());

	std::string v1, v2;
	for (int e = 0; e < E; ++e)
	{
		std::getline(in, line);
		split(line, v1, v2, delim);
		addEdge(std::stoi(v1.c_str()), std::stoi(v2.c_str()));
	}
	return;
}

void Ryim::UndirectedGraph::makeDot(std::ifstream& in, std::string fullpath, const char delim /*= ','*/)
{
	std::string line;
	std::getline(in, line);
	std::getline(in, line);
	int E = std::stoi(line.c_str());

	// open file and write dot head
	std::ofstream fs;
	fs.open(fullpath + ".gv", std::ios::trunc);
	fs << "digraph UndirectedGraph{\n";
	//fs << " node [arrowhead=\"none\"];\n";

	std::string v1, v2;
	for (int e = 0; e < E; ++e)
	{
		std::getline(in, line);
		split(line, v1, v2, delim);
		if (std::stoi(v2.c_str()) == (*m_path).at(std::stoi(v1.c_str())) ||
			std::stoi(v1.c_str()) == (*m_path).at(std::stoi(v2.c_str())))
		{
			fs << v1 << "->" << v2 << "[dir=\"none\", style=bold, color=red];\n";
		}
		else
		{
			fs << v1 << "->" << v2 << "[dir=\"none\", style=bold];\n";
		}
	}

	// write dot tail
	fs << "}";
	return;
}

const Ryim::UndirectedGraph::ADJ* Ryim::UndirectedGraph::adj(int v) { return (*m_adj).at(v); }

void Ryim::UndirectedGraph::dfs_recurrence(int v)
{
	(*m_marked)[v] = true;

	for (auto w : *((*m_adj).at(v)))
	{
		if (!(*m_marked)[w])
		{
			(*m_path)[w] = v;
			dfs_recurrence(w);
		}
	}
}

void Ryim::UndirectedGraph::dfs(int v)
{
	int vertex = 0;
	int pos = 0;
	std::stack<std::pair<int, int>> recordnext;
	recordnext.push(std::pair<int, int>(v, *((*m_adj).at(v)->begin())));
	std::list<int>::iterator w;
	while (!recordnext.empty())
	{
		vertex = recordnext.top().first;
		pos = recordnext.top().second;
		(*m_marked)[vertex] = true;
		recordnext.pop();

		w = (*m_adj).at(vertex)->begin();
		for (; w != (*m_adj).at(vertex)->end(); ++w)
		{
			if (*w != pos)
				continue;
			else
				break;
		}

		for (; w != (*m_adj).at(vertex)->end(); ++w)
		{
			if (!((*m_marked)[*w]))
			{
				(*m_path)[*w] = vertex;
				int prev = *w;
				++w;
				if (w != (*m_adj).at(vertex)->end())
				{
					recordnext.push(std::pair<int, int>(vertex, *w));
				}

				if ((*m_adj).at(prev)->begin() != (*m_adj).at(prev)->end())
				{
					recordnext.push(std::pair<int, int>(prev, *((*m_adj).at(prev)->begin())));
				}
				break;
			}
		}
	}
}

bool Ryim::UndirectedGraph::hasPathTo(int v)
{
	return (*m_marked)[v];
}

void Ryim::UndirectedGraph::addEdge(int v1, int v2)
{
	(*m_adj)[v1]->push_back(v2);
	(*m_adj)[v2]->push_back(v1);
	m_edge++;
}

void Ryim::UndirectedGraph::split(const std::string& line, std::string& v1, std::string& v2, const char delim/* = ','*/)
{
	std::size_t pos = line.find(delim);
	v1 = line.substr(0, pos);
	v2 = line.substr(pos + 1);
	return;
}


////////////////////////////DirectedGraph//////////////////////////////////////////////////////////////////////
Ryim::DirectedGraph::DirectedGraph() :m_vertex(0)
, m_edge(0)
, m_adj(nullptr)
{}

Ryim::DirectedGraph::~DirectedGraph()
{
	clear();
}

void Ryim::DirectedGraph::clear()
{
	if (nullptr != m_adj)
	{
		for (std::size_t v = 0; v < (m_adj->size()); ++v)
		{
			if (nullptr != (*m_adj)[v])
			{
				delete (*m_adj)[v];
				(*m_adj)[v] = nullptr;
			}
		}
		delete m_adj;
		m_adj = nullptr;
	}
}

void Ryim::DirectedGraph::initial(int Vertex)
{
	m_vertex = Vertex;
	m_edge = 0;
	m_adj = new ADJ_ARRAY(Vertex);
	for (int v = 0; v < Vertex; ++v)
	{
		(*m_adj)[v] = new ADJ();
	}
}

void Ryim::DirectedGraph::initial(std::ifstream& in, const char delim/* = ','*/)
{
	std::string line;
	std::getline(in, line);
	initial(std::stoi(line.c_str()));
	std::getline(in, line);
	int E = std::stoi(line.c_str());

	std::string v1, v2;
	for (int e = 0; e < E; ++e)
	{
		std::getline(in, line);
		split(line, v1, v2, delim);
		addEdge(std::stoi(v1.c_str()), std::stoi(v2.c_str()));
	}
	return;
}

const Ryim::DirectedGraph::ADJ* Ryim::DirectedGraph::adj(int v) { return (*m_adj).at(v); }

void Ryim::DirectedGraph::addEdge(int v1, int v2)
{
	(*m_adj)[v1]->push_back(v2);
	m_edge++;
}

void Ryim::DirectedGraph::split(const std::string& line, std::string& v1, std::string& v2, const char delim/* = ','*/)
{
	std::size_t pos = line.find(delim);
	v1 = line.substr(0, pos);
	v2 = line.substr(pos + 1);
	return;
}

////////////////////////////DirectedDFS//////////////////////////////////////////////////////////////////////

Ryim::DirectedDFS::DirectedDFS() {}

Ryim::DirectedDFS::~DirectedDFS()
{
	if (nullptr != m_path)
	{
		delete m_path;
		m_path = nullptr;
	}

	if (nullptr != m_marked)
	{
		delete m_marked;
		m_marked = nullptr;
	}
}

bool Ryim::DirectedDFS::init(int vs)
{
	m_marked = new MARKED(vs, false);
	m_path = new PATH(vs, INT_MIN);
	return true;
}

void Ryim::DirectedDFS::clearState(int vs)
{
	m_path->clear();
	m_path->resize(vs, INT_MIN);
	m_marked->clear();
	m_marked->resize(vs);
}

void Ryim::DirectedDFS::dfs(DirectedGraph* G, int v)
{
	(*m_marked)[v] = true;
	for (int w : *(G->adj(v)))
	{
		if (!(*m_marked)[w])
		{
			(*m_path)[w] = v;
			dfs(G, w);
		}
	}
}

bool Ryim::DirectedDFS::marked(int v)
{
	return (*m_marked)[v];
}
