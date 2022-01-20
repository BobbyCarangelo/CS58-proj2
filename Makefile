CFLAGS=-g -pthread

all:	main

bridge_sim.o:		bridge_sim.c bridge_sim.h
								gcc $(CFLAGS) -c bridge_sim.c

main.o:					main.c
								gcc $(CFLAGS) -c main.c

main:						main.o bridge_sim.o
								gcc $(CFLAGS) bridge_sim.o main.c -o main

clean:
								rm *.o main
