#include "rAlgorithms_substring_sample.h"
#include "ryimTestUtility.h"


testAlgroithmsSubstring::testAlgroithmsSubstring()
{

}
testAlgroithmsSubstring::~testAlgroithmsSubstring()
{

}

void testAlgroithmsSubstring::test()
{
	std::string txt = "ABCD";
	std::string regexp = "(A*(B|A)C)D";
	Ryim::Regexp::RegularExp re;
	re.NFA(regexp);
	bool r = re.Recognize(txt);
	std::cout << std::boolalpha << r << std::endl;
}