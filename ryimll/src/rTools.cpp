#include "rTools.h"
#include <iostream>

namespace Ryim
{
    namespace lzMath
    {
        bool LeapYearCalculator::isLeapYear(unsigned long year)
        {
            if (year % 100 == 0)
            {
                if (year % 400 == 0)
                    return true;
            }
            else if (year % 4 == 0)
            {
                return true;
            }
            return false;
        }

        factorialCalculator::factorialCalculator()
        {
            std::cout << "initialize table [BEGIN]..." << std::endl;
            m_table.reserve(21);
            m_table.push_back(1);
            for(unsigned long long i = 1; i < 21; ++i)
            {
                m_table.push_back(i * m_table[i-1]);
            }
            std::cout << "initialize table [END]" << std::endl;
        }

        unsigned long long factorialCalculator::calc(unsigned long long number)
        {
            if(number > 21) return 0;
            return m_table[number];
        }
    } // namespace lzMath
} // namespace Ryim