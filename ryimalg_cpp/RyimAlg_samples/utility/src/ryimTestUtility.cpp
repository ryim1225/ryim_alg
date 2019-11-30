#include "ryimTestUtility.h"

///////////////////////////////////////////////////////////////
ProjectPath::ProjectPath()
{
}

ProjectPath::~ProjectPath()
{
	free(m_buffer);
}

//////////////////////////////////////////////////////////////
ryimTestTimer::ryimTestTimer(std::string label):m_label(label)
{
#if _MSC_VER < 1800
	// do something
#else
	t1 = std::chrono::steady_clock::steady_clock::now();
#endif

	std::cout << "-----------Test " << m_label << " [Begin]------------" << std::endl;
}


ryimTestTimer::~ryimTestTimer()
{
#if _MSC_VER < 1800
	// do something
#else
	t2 = std::chrono::steady_clock::steady_clock::now();
	std::chrono::duration<double> time_span = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
	std::cout << "cost: " << time_span.count() << std::endl;
#endif

	std::cout << "-----------Test " << m_label << " [End]------------" << std::endl;
	std::cout << std::endl;
}
