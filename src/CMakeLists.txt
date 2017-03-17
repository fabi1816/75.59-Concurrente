cmake_minimum_required ( VERSION 2.6 )
project ( atrevidoV1 )

set ( CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread -Wall -Wpedantic -Wextra" )
set ( CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -DNDEBUG" )
set ( CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} -g -ggdb -O0 -fprofile-arcs -ftest-coverage" )
set ( CMAKE_CXX_LINKER_FLAGS_DEBUG "${CMAKE_CXX_LINKER_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage" )

if ( NOT CMAKE_BUILD_TYPE )
    set ( CMAKE_BUILD_TYPE Debug )
endif ()

set ( SRCS main.cpp )
add_executable ( atrevidoV1 ${SRCS} )

