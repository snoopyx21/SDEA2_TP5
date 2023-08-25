arbre : my_abint.o main.o
	gcc -o arbre my_abint.o main.o -g -Werror -Wall
my_abint.o : my_abint.c
	gcc -o my_abint.o -c my_abint.c -g -Werror -Wall
main.o : main.c my_abint.h
	gcc -o main.o -c main.c -g -Werror -Wall
clean:
	rm -f *.o core

