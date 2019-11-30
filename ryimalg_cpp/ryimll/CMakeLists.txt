cmake_minimum_required(VERSION 3.2)

#project name
PROJECT(ryimll)

# check C++ flag to know if the compiler support C++11
INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

# set flag using compiling flag
if(COMPILER_SUPPORTS_CXX11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
elseif(COMPILER_SUPPORTS_CXX0X)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
else()
message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

SET(CMAKE_DEBUG_POSTFIX "d")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "./lib")

#head file path
INCLUDE_DIRECTORIES(./include ../ryimtl)

#source directory
AUX_SOURCE_DIRECTORY(src DIR_SRCS)

#add library
ADD_LIBRARY(${PROJECT_NAME} STATIC ${DIR_SRCS})

