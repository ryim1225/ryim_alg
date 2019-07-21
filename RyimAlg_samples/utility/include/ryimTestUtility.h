#ifndef _RYIM_TEST_TIMER_H_
#define _RYIM_TEST_TIMER_H_

#include <chrono>
#include <iostream>
#include <iterator>
#include <string>
#if WIN32
#include <direct.h>
#elif UNIX
#include <unistd.h>
#endif

template<typename Container>
void print(Container& a, std::string str = "")
{
    std::cout << str << std::endl;
    for (typename Container::iterator it = a.begin(); it != a.end(); ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template<typename _iter>
void print(_iter _first, _iter _last, std::string str = "")
{
    std::cout << str << std::endl;
    for (_iter it = _first; it != _last; ++it)
    {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
}

template<typename Type>
void print(Type a[], int size, std::string str = "")
{
    std::cout << str << std::endl;
    for (int i = 0; i < size; ++i)
    {
        std::cout << a[i] << " ";
    }
    std::cout << std::endl;
}

template<typename Container>
void printstream(Container& a, std::string str = "")
{
    std::cout << str << std::endl;
    std::copy(a.begin(), a.end(), std::ostream_iterator<typename Container::value_type>(std::cout, " "));
    std::cout << std::endl;
}

template<typename Container>
void printCapacitySize(Container& _container)
{
    std::cout << "capacity = " << _container.capacity() << " size = " << _container.size() << std::endl;
}

class graphvizHelper
{
public:
    #if WIN32
    static void command(const std::wstring& wpath, const std::wstring& filename)
    {
        std::wstring _command(L"dot -Tpng ");
        _command += (wpath + filename + L".gv") + L" -o " + (wpath + filename + L".png");
        _wsystem(_command.c_str());
    }
    #elif UNIX
    static void command(const std::wstring& path, const std::string& filename)
    {
        std::string _command("dot -Tpng ");
        _command += (path + filename + ".gv") + " -o " + (path + filename + ".png");
        system(_command.c_str());
    }
    #endif


};


class ProjectPath
{
public:
    ProjectPath();
    ~ProjectPath();

    void getProjectPath(std::string complementPath)
    {
        // Get the current working directory:
        #if WIN32
        if ((m_buffer = _getcwd(NULL, 0)) == NULL)
            perror("_getcwd error");
        else
            std::cout << m_buffer << std::endl;
        #elif UNIX
        if ((m_buffer = getcwd(NULL, 0)) == NULL)
            perror("getcwd error");
        else
            std::cout << m_buffer << std::endl;
        #endif
       
        
        m_path = m_buffer;
        m_path += complementPath;
        m_wpath.assign(m_path.begin(), m_path.end());
    }

    std::string getPath() const
    {
        return m_path;
    }

    std::wstring getWPath() const
    {
        return m_wpath;
    }

private:
    char* m_buffer;
    std::string m_path;
    std::wstring m_wpath;
};



class ryimTestTimer
{
public:
    explicit ryimTestTimer(std::string label);
    ~ryimTestTimer();
private:
    std::chrono::steady_clock::time_point t1;
    std::chrono::steady_clock::time_point t2;
    std::string m_label;
};
#endif

