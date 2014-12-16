awale: main.o fonctions.o
		gcc -o awale fonctions.o main.c -Wall	
		
main.o: main.c
		gcc -c  main.c 
		
fonctions.o: fonctions.c
		gcc -c fonctions.c 
			
clean:
	rm -f awale *o
