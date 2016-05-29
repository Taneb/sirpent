sirpent : main.o list.o grid.o
	cc -o sirpent main.o list.o grid.o

main.o : main.c list.h grid.h
	cc -c main.c

list.o : list.c list.h
	cc -c list.c

grid.o : grid.c grid.h
	cc -c grid.c

clean :
	rm sirpent main.o list.o grid.o
