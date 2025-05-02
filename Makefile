project: main.o file.o encrypt.o
	gcc -o project main.o file.o encrypt.o
main.o: main.c encrypt.h file.h
	gcc -c main.c -std=c99 -Wall -pedantic
encrypt.o: encrypt.c encrypt.h
	gcc -c encrypt.c -std=c99 -Wall -pedantic
file.o: file.c file.h encrypt.h
	gcc -c file.c -std=c99 -Wall -pedantic
clear:
	rm *.o project
