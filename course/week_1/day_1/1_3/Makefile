name_age: name.o printNameAndAge.o
	g++ -o name name.o printNameAndAge.o

name.o: name.cpp
	g++ -c name.cpp

printNameAndAge.o: printNameAndAge.cpp
	g++ -c printNameAndAge.cpp

.PHONY: install
install: name

.PHONY: clean
clean: 
	rm *.o
	rm name
