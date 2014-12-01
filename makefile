fonction.exe: fonction.c
			gcc -g fonction.c -o fonction.exe  -Wall
clean:
	rm -f fonction.exe *o
