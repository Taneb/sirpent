sirpent : main.o list.o
	cc -o sirpent main.o list.o

main.o : main.c list.h
	cc -c main.c

list.o : list.c list.h
	cc -c list.c

clean :
	rm sirpent main.o list.o
