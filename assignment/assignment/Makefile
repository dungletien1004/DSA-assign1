all: assignment

DEFS = -DUSE_SOME_DEF

assignment: main.o tournament.o
	g++ main.o tournament.o -std=c++11 -o assignment $(DEFS)

main.o: main.cpp defs.h
	g++ -c main.cpp -std=c++11 $(DEFS)
tournament.o: tournament.cpp defs.h
	g++ -c tournament.cpp -std=c++11 $(DEFS)

clean:
	rm *.o assignment
