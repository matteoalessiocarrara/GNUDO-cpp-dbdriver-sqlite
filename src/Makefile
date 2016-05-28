LIB = gnudo.o managers.o objects.o

test: lib
	@echo Attenzione: la libreria sqlite3pp non viene ricompilata automaticamente
	c++ -std=c++11 -g -lsqlite3 $(LIB) ../lib/sqlite3pp/src/sqlite3pp.o test/test.cpp -o test/test


lib: $(LIB)


gnudo.o: gnudo.cpp gnudo.hpp
	c++ -std=c++11 -g -c gnudo.cpp


managers.o: managers.cpp managers.hpp
	c++ -std=c++11 -g -c managers.cpp


objects.o: objects.cpp objects.hpp
	c++ -std=c++11 -g -c objects.cpp
	
clean:
	rm *.o test/test