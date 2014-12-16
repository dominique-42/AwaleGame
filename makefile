
OBJS=fonctions.o jeu.o
CC=gcc
PROG=awale
OPTS=-Wall

awale: main.c ${OBJS}
		${CC} -o ${PROG} ${OBJS} main.c ${OPTS}	
		
		
fonctions.o: fonctions.c
		${CC} -c fonctions.c ${OPTS}
			
jeu.o: jeu.c
		${CC} -c jeu.c ${OPTS}

clean:
	rm -f ${PROG} *.o
