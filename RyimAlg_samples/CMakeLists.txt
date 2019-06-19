cmake_minimum_required(VERSION 3.2)
PROJECT(RyimAlg)

#3.head file path
INCLUDE_DIRECTORIES(include)

ADD_SUBDIRECTORY()
#4.source directory
AUX_SOURCE_DIRECTORY(src DIR_SRCS)

#5.set environment variable
SET(TEST_MATH ${DIR_SRCS})

#6.add executable file
ADD_EXECUTABLE(${PROJECT_NAME} ${TEST_MATH})

#7.add link library
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} m)
