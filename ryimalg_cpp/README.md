
#PART 1
---
## How to build
### If you want to build them on linux, please execute the commands as follow:
- <b>method 1</b>
  > - python build.py all Debug
  > or
  > - python build.py all Release
- <b>method 2</b>
  > * python build.py ryimll Debug
  > * python build.py utility Debug
  > * python build.py {xxx_sample} Debug
  >
  > or
  > * python build.py ryimll Release
  > * python build.py utility Release
  > * python build.py {xxx_sample} Release
### Build with Visual Studio on Windows
  > - cd ryimll && mkdir build_{64/32} && cd build_{64/32} && cmake
  >   open ryimll.sln && build which you want debug or release
  > - build RyimAlg_samples\utility using the way above
  > - then build other module in the RyimAlg_samples
#PART 2
---
## cmake handbook
- <b>cmake verson，指定cmake版本</b>
  > cmake_minimum_required(VERSION 3.2)
- <b>project name，指定项目的名称，一般和项目的文件夹名称对应</b>
  >PROJECT(RyimAlg)
- <b>head file path，头文件目录</b>
  >INCLUDE_DIRECTORIES(include)
  > ADD_SUBDIRECTORY()
- <b>source directory，源文件目录</b>
  > AUX_SOURCE_DIRECTORY(src DIR_SRCS)
- <b>set environment variable，设置环境变量，编译用到的源文件全部都要放到这里，否则编译能够通过，但是执行的时候会出现各种问题，比如"symbol lookup error xxxxx , undefined symbol"</b>
  > SET(TEST_MATH ${DIR_SRCS})
- <b>add executable file，添加要编译的可执行文件</b>
  > ADD_EXECUTABLE(\${PROJECT_NAME} \${TEST_MATH})
- <b>add link library</b>
  > TARGET_LINK_LIBRARIES(${PROJECT_NAME} m)

## tools
need by as follow:

- graphviz -> http://www.graphviz.org/ for rTree.h
- eigen    -> http://eigen.tuxfamily.org