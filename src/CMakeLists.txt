cmake_minimum_required(VERSION 2.8)

project(GNUDO)

set(CMAKE_CXX_FLAGS_RELEASE "-O2 -mtune=native -W")
set(CMAKE_CXX_FLAGS_DEBUG "-g -D_DEBUG -mtune=native -W -Wall -Wextra -Wshadow")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

#set(SRCS ...)

#add_library(gnudo_core STATIC ${SRCS})

add_executable(gnudo main.cpp)

