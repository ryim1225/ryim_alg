cmake_minimum_required(VERSION 3.2)
PROJECT(rAlgorithms_sort_sample)

# check C++ flag to know if the compiler support C++11
INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

# set flag using compiling flag
IF(COMPILER_SUPPORTS_CXX11)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSEIF(COMPILER_SUPPORTS_CXX0X)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
ELSE()
    MESSAGE(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
ENDIF()

message("${CMAKE_CURRENT_SOURCE_DIR}")
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../ryimtl)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../../ryimll/include) 
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/../utility/include)

AUX_SOURCE_DIRECTORY(${CMAKE_CURRENT_SOURCE_DIR} DIR_SRCS)

MATH(EXPR BITS "8*${CMAKE_SIZEOF_VOID_P}")
SET(ryimll_library_dir ${CMAKE_CURRENT_SOURCE_DIR}/../../ryimll/build_${BITS})
SET(utility_library_dir ${CMAKE_CURRENT_SOURCE_DIR}/../utility/build_${BITS})
message("${ryimll_library_dir}")
message("${utility_library_dir}")
IF (WIN32)
    IF(CMAKE_BUILD_TYPE MATCHES "Debug")
        LINK_DIRECTORIES(${ryimll_library_dir}/lib/Debug)
        LINK_DIRECTORIES(${utility_library_dir}/lib/Debug)
    ELSE()
        LINK_DIRECTORIES(${ryimll_library_dir}/lib/Release)
        LINK_DIRECTORIES(${utility_library_dir}/lib/Release)
    ENDIF()
ELSEIF (APPLE)
	MESSAGE(STATUS "Now is Apple systens.")
ELSEIF (UNIX)
    MESSAGE(STATUS "Now is UNIX-like OS's.")
    LINK_DIRECTORIES(${ryimll_library_dir}/lib)
    LINK_DIRECTORIES(${utility_library_dir}/lib)
ENDIF ()


ADD_EXECUTABLE(${PROJECT_NAME} ${DIR_SRCS})

IF(CMAKE_BUILD_TYPE MATCHES "Debug")
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ryimlld utilityd)
ELSE()
    TARGET_LINK_LIBRARIES(${PROJECT_NAME} ryimll utility)
ENDIF()