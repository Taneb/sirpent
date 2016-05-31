sirpent : main.o list.o grid.o
	cc -o sirpent main.o list.o grid.o

main.o : main.c udp_list/list.h grid.h
	cc -c main.c

list.o : udp_list/list.c udp_list/list.h
	cc -c udp_list/list.c

grid.o : grid.c grid.h
	cc -c grid.c

clean :
	rm sirpent main.o list.o grid.o
