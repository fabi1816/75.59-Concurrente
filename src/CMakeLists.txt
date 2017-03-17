cmake_minimum_required ( VERSION 2.6 )
project ( atrevidoV1 )

set ( CMAKE_CXX_FLAGS "-g -ggdb -O0" )

set ( SRCS main.cpp )
add_executable ( atrevidoV1 ${SRCS} )

