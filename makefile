sirpent : main.o list.o world.o snake.o vector.o
	cc -o sirpent main.o list.o world.o snake.o vector.o

main.o : main.c udp_list/list.h world.h snake.h
	cc -c main.c --std=gnu99

list.o : udp_list/list.c udp_list/list.h
	cc -c udp_list/list.c  --std=gnu99

vector.o : vector.c vector.h
	cc -c vector.c --std=gnu99

world.o : world.c world.h snake.h vector.h
	cc -c world.c --std=gnu99

snake.o : snake.c snake.h world.h vector.h
	cc -c snake.c --std=gnu99

clean :
	rm sirpent main.o list.o world.o snake.o
