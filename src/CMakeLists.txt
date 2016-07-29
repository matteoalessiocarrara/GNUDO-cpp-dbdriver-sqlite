cmake_minimum_required(VERSION 3.0)

# So quello che faccio, statti zitto compilatore incapace
add_compile_options(-std=c++11 -fpermissive)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE}")

add_library(${PROJECT_NAME} SHARED gnudo.cpp managers.cpp objects.cpp)
#add_executable(testlib test/test.cpp)

# XXX
add_library(sqlite3pp SHARED IMPORTED)
set_property(TARGET sqlite3pp PROPERTY IMPORTED_LOCATION /usr/local/lib/libsqlite3pp.so)
add_library(abstract SHARED IMPORTED)
set_property(TARGET abstract PROPERTY IMPORTED_LOCATION /usr/local/lib/libgnudo-cpp-dbdriver-abstract.so)

target_link_libraries(${PROJECT_NAME} sqlite3pp)
target_link_libraries(${PROJECT_NAME} abstract)
#target_link_libraries(testlib ${PROJECT_NAME})

install(TARGETS ${PROJECT_NAME} DESTINATION lib)
install(FILES dbdefs.hpp gnudo.hpp managers.hpp objects.hpp DESTINATION include/${PROJECT_NAME})
