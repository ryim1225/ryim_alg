cmake_minimum_required(VERSION 3.2)
#project name
PROJECT(utility)

SET(CMAKE_DEBUG_POSTFIX "d")
SET(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "./lib")

#head file path
INCLUDE_DIRECTORIES(./include)

#source directory
AUX_SOURCE_DIRECTORY(src DIR_SRCS)

#add library
ADD_LIBRARY(${PROJECT_NAME} STATIC ${DIR_SRCS})


