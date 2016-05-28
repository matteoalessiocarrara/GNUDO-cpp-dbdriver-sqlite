cmake_minimum_required(VERSION 2.8)

project(GNUDO CXX)

if (NOT CMAKE_MODULE_PATH)
	set(CMAKE_MODULE_PATH "../cmake")
endif()

find_package(Threads REQUIRED)
find_package(SQLite3 REQUIRED)

set(CMAKE_CXX_FLAGS_RELEASE "-O2 -mtune=native -W")
set(CMAKE_CXX_FLAGS_DEBUG "-std=c++11 -g -D_DEBUG -mtune=native -W -Wall -Wextra -Wshadow")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY bin)

include_directories(${INCLUDE_DIRS})

file(GLOB_RECURSE SRCS "*.cpp")

if(SRCS)
	add_library(gnudosqlite SHARED ${SRCS})
	target_link_libraries(gnudosqlite ${CMAKE_THREAD_LIBS_INIT})
	target_link_libraries(gnudosqlite sqlite3)
endif(SRCS)

