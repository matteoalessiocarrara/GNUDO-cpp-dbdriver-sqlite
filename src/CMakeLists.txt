cmake_minimum_required(VERSION 2.8)

project(GNUDO CXX)

set(CMAKE_CXX_FLAGS_RELEASE "-O2 -mtune=native -W")
set(CMAKE_CXX_FLAGS_DEBUG "-g -D_DEBUG -mtune=native -W -Wall -Wextra -Wshadow")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

file(GLOB_RECURSE SRCS "*.cpp")

if(SRCS)
  add_executable(gnudo ${SRCS})
else()
  message("-!- SRCS not specified!")
endif(SRCS)

