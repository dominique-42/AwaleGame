#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>


#define L 2
#define C 6
#define N 12

typedef struct {int x; int y; }t_coord;

int init_matrice(int matrice[L][C]){
}

int affiche_matrice(int matrice[L][C]) {
}

int dpl_arriere(int x, int y) {
		
		if(x<5 && y==1) {
			x--;
		}
		else {
			x++;
		}
		if(y == 1 && x==5){
			y--;
		}
		else if(y == 1 && x==0){
			y++;
		}
}
int dpl_avant(int x, int y) {
		
		if(x<5 && y==1) {
			x++;
		}
		else {
			x--;
		}
		if(y == 1 && x==5){
			y--;
		}
		else if(y == 1 && x==0){
			y++;
		}
}
int manger_graines(int nb_graines, int matrice[L][C], int x, int y, int *score) {
	
	assert(nb_graines > 0);
	assert( x>0 && x<C);
	assert( y>0 && y<L);
	
	int i, j= 0;
	t_coord graine_mange[N];
	t_coord graine_dbt;
	graine_dbt.x = x;
	graine_dbt.y = y;
	
	for(i = 0; i<nb_graines;i++) {
		dpl_avant(x,y);
		assert(x>0 && x<L);
		assert(y>0 && y<C);
		
		matrice[x][y]++;
		if(matrice[x][y] == 2 || matrice[x][y] == 3) {			
			graine_mange[j].x = x;						//stocker dans un tableau de type t_coord les coordonnées des graines qu'on peut manger
			graine_mange[j].y = y;
			j++;

		}
	}
	if(matrice[x][y] == 2 || matrice[x][y] == 1) {
		*score = *score+matrice[x][y];
	}
	for(i = nb_graines; i>nb_graines && matrice[x][y]<= 3 ;i--) {	//initialise le score a
			*score = *score+matrice[x][y];
			dpl_arriere(x,y);
	}
	graine_dbt.x = 0;
	graine_dbt.y = 0;	
}

int main(){
	
	int awale[L][C];
	int score = 0;
	int choix;
	char pseudo[20];
	FILE * fic_pseudo;
	FILE * fic_score;
	FILE * fic_partie;

	fic_pseudo = fopen("save_pseudo.txt", "w");
	fic_score = fopen("save_score.txt", "w");
	fic_partie = fopen("save_partie.txt", "w");


	printf("\nMenu :\n");
		printf(" 1 - Voulez vous commencez une nouvelle partie ?\n");
		printf(" 2 - Reprendre la partie\n");
		printf(" 3 - Quittez AWELE\n");

		scanf("%i",&choix);
	
	switch(choix)
		{	case 1 : 
				printf("Joueur 1\nVeuillez saisir votre pseudonyme ?\n");
				scanf("%s", pseudo);
				fprintf(fic_pseudo, "%s\n", pseudo);
				printf("Joueur 2\nVeuillez saisir votre pseudonyme ?\n");
				scanf("%s", pseudo);
				fprintf(fic_pseudo, "%s\n", pseudo);
				
				printf("\nQue la partie commence !\n");

				
			
			
			break;
			case 2:  ; break;
			case 3:  printf("Au revoir\n"); break;
			default: printf("Erreur: votre choix doit etre compris entre 1 et 6\n");
		}
}
