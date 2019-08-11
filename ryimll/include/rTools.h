#ifndef _R_TOOLS_H_
#define _R_TOOLS_H_
#include <vector>

namespace Ryim
{
    namespace lzMath
    {
        class LeapYearCalculator
        {
        public:
            bool isLeapYear(unsigned long year);
        };

        class factorialCalculator
        {
        public:
            factorialCalculator();
            ~factorialCalculator();
            unsigned long long calc(unsigned long long number);
        private:
            std::vector<unsigned long long> m_table;
        };
    }

}// Ryim end
#endif