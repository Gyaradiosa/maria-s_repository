CC = cc
CFLAGS = -Wall -Wextra -Werror

all : bsq map 
	cat example_file

bsq : main.o
	$(CC) $(CFLAGS) -o bsq main.o

main.o : main.c
	$(CC) $(CFLAGS) -c main.c

map: map.pl
	./map.pl 10 20 5 > example_file

fclean: 
	rm -r bsq main.o map  example_file
