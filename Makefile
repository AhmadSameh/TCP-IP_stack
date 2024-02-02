CC=gcc
CFLAGS=-g
TARGET=test.exe

OBJS = ./build/gluethreads/glthreads.o ./build/graph.o ./build/topologies.o ./build/net.o

all: ${OBJS} ./testapp.o
	${CC} ${CFLAGS} testapp.o ${OBJS} -o test

./testapp.o: ./testapp.c
	${CC} ${CFLAGS} -c ./testapp.c  -o ./testapp.o

./build/gluethreads/glthreads.o: ./gluethreads/glthreads.c
	${CC} ${CFLAGS} -c -I./gluethreads gluethreads/glthreads.c -o ./build/gluethreads/glthreads.o

./build/graph.o: ./graph.c
	${CC} ${CFLAGS} -c -I. ./graph.c -o ./build/graph.o

./build/topologies.o: ./topologies.c
	${CC} ${CFLAGS} -c -I. ./topologies.c -o ./build/topologies.o

./build/net.o: ./net.c
	${CC} ${CFLAGS} -c -I. ./net.c -o ./build/net.o

clean:
	rm ./test
	rm ${OBJS}
	rm ./testapp.o
