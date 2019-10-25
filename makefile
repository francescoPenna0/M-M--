m_m_infinito: main.o funzioni.o
	gcc -g -Wall -o m_m_infinito main.o mminfinito.o

main.o: main.c mminfinito.h
	gcc -g -Wall -c main.c

funzioni.o: mminfinito.c mminfinito.h
	gcc -g -c mminfinito.c