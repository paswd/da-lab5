FLAGS=-pedantic -Wall -Werror -Wno-sign-compare -Wno-long-long -lm -std=c++11 -O2
COMPILLER=g++

#all: lib start
all: start

#start: main.o
#	$(COMPILLER) $(FLAGS) -o da-lab4 main.o -L. lib/lib-z-search.a

start: suffixtree.o main.o
	$(COMPILLER) $(FLAGS) -o da-lab5 suffixtree.o main.o

main.o: main.cpp
	$(COMPILLER) -c $(FLAGS) main.cpp

suffixtree.o: suffixtree.cpp
	$(COMPILLER) -c $(FLAGS) suffixtree.cpp

clean:
	rm -f *.o *.gch *.dat da-lab5
	#rm lib/lib-z-search.a
