test: lib test.cpp
	c++ -std=c++11 -I ../../lib/sqlite/hdr/ -lpthread -ldl -lsqlite3 gnudo.o test.cpp

lib: gnudo.cpp objects.cpp managers.cpp
	c++ -std=c++11 -I ../../lib/sqlite/hdr/ -o gnudo.o -c gnudo.cpp 
	
sqlite: ../../lib/sqlite/sqlite3.c
	c89 -c ../../lib/sqlite/sqlite3.c -o ../../lib/sqlite/sqlite3.o
	