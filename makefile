sirpent : main.o list.o world.o snake.o vector.o
	cc -o sirpent main.o list.o world.o snake.o vector.o

main.o : main.c udp_list/list.h world.h snake.h
	cc -c main.c

list.o : udp_list/list.c udp_list/list.h
	cc -c udp_list/list.c

vector.o : vector.c vector.h
	cc -c vector.c

world.o : world.c world.h snake.h vector.h
	cc -c world.c

snake.o : snake.c snake.h world.h vector.h
	cc -c snake.c

clean :
	rm sirpent main.o list.o world.o snake.o
