#include "rGraph_sample.h"
#include "ryimTestUtility.h"
#include <string>
#include <fstream>
#include <sstream>

testGraph::testGraph() {}
testGraph::~testGraph() {}

void testGraph::test()
{
	std::cout << "rGraph_sample.cpp" << std::endl;
	testUndirectedGraph();
}

void testGraph::testUndirectedGraph()
{
	std::cout << "UndirectedGraph" << std::endl;
	ProjectPath outpath;
	outpath.getProjectPath("\\output\\graph\\");
	std::string  soutpath = outpath.getPath();
	std::wstring woutpath = outpath.getWPath();

	ProjectPath inputpath;
	inputpath.getProjectPath("\\input\\graph\\");
	std::string  sinputpath = inputpath.getPath();
	std::wstring winputpath = inputpath.getWPath();

	int vto = 0;
	std::stringstream s;
	std::wstringstream ws;
	std::string svto;
	std::wstring wsvto;
	s << vto;
	s >> svto;
	ws << vto;
	ws >> wsvto;

	Ryim::UndirectedGraph testundigraph1;
	std::ifstream tinyfs(sinputpath + "tinyUndiG.txt");
	testundigraph1.initial(tinyfs);
	{
		ryimTestTimer timer("test tinyUndiG.txt and dfs recurrence");
		testundigraph1.dfs_recurrence(vto); // traverse starting with vto
		std::cout << testundigraph1.hasPathTo(9) << std::endl;
	}
	tinyfs.seekg(0);
	testundigraph1.makeDot(tinyfs, soutpath + "rtinyUndiGstartwith" + svto);
	graphvizHelper::command(woutpath, L"rtinyUndiGstartwith" + wsvto);

	{
		testundigraph1.clearState();
		ryimTestTimer timer("test tinyUndiG.txt and dfs");
		testundigraph1.dfs(vto); // traverse starting with vto
		std::cout << testundigraph1.hasPathTo(9) << std::endl;
	}
	tinyfs.seekg(0);
	testundigraph1.makeDot(tinyfs, soutpath + "tinyUndiGstartwith" + svto);
	graphvizHelper::command(woutpath, L"tinyUndiGstartwith"+ wsvto);

	Ryim::UndirectedGraph testundigraph2;
	std::ifstream mediumfs(sinputpath + "mediumUndiG.txt");
	testundigraph2.initial(mediumfs);
	{
		ryimTestTimer timer("test mediumUndiG.txt and dfs recurrence");
		testundigraph2.dfs_recurrence(0); // traverse starting with 0
	}
	mediumfs.seekg(0);
	testundigraph2.makeDot(mediumfs, soutpath + "rmediumUndiGstartwith" + svto);
	graphvizHelper::command(woutpath, L"rmediumUndiGstartwith" + wsvto);

	{
		testundigraph2.clearState();
		ryimTestTimer timer("test mediumUndiG.txt and dfs");
		testundigraph2.dfs(0); // traverse starting with 0
	}
	mediumfs.seekg(0);
	testundigraph2.makeDot(mediumfs, soutpath + "mediumUndiGstartwith" + svto);
	graphvizHelper::command(woutpath, L"mediumUndiGstartwith" + wsvto);
}