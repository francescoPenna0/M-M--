m_m_infinito: main.o funzioni.o
	gcc -g -Wall thpool.c -D THPOOL_DEBUG -pthread -o m_m_infinito main.o funzioni.o

main.o: main.c funzioni.h
	gcc -g thpool.c -D THPOOL_DEBUG -pthread -Wall -c main.c

funzioni.o: funzioni.c funzioni.h
	gcc -g thpool.c -D THPOOL_DEBUG -pthread -c funzioni.c