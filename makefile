all: solution

debug: solution.dbg

solution: solution.o tree.o list.o
	gcc -o solution solution.o tree.o list.o

solution.o: solution.c tree.h
	gcc -c -Werror -Wall solution.c

list.o: list.c list.h tree.h
	gcc -c -Werror -Wall list.c

tree.o: tree.c tree.h list.h
	gcc -c -Werror -Wall tree.c

solution.dbg: solution.dbg.o tree.dbg.o list.dbg.o
	gcc -g -o solution.dbg solution.dbg.o tree.dbg.o list.dbg.o

solution.dbg.o: solution.c tree.h
	gcc -g -c -Werror -Wall solution.c -o solution.dbg.o

list.dbg.o: list.c list.h tree.h
	gcc -g -c -Werror -Wall list.c -o list.dbg.o

tree.dbg.o: tree.c tree.h list.h
	gcc -g -c -Werror -Wall tree.c -o tree.dbg.o

clean:
	rm -rf *.o ./solution ./*.dbg