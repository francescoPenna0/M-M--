m_m_infinito: main.o funzioni.o
	gcc -g -Wall -o m_m_infinito main.o funzioni.o

main.o: main.c funzioni.h
	gcc -g -Wall -c main.c

funzioni.o: funzioni.c funzioni.h
	gcc -g -c funzioni.c