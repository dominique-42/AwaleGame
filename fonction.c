#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>


#define L 2
#define C 6
#define N 12

int awale[L][C];
int scorej1 = 0;
int scorej2 = 0;
char player1[20];
char player2[20];

typedef struct {int joueur; int x; }t_coord;
/**
*\fn init_matrice(int matrice[L][C])
*\brief Permet d'initialiser la matrice avec 4 graines dans chaque case
*\param matrice[L][C] matrice representant le plateau du jeu
*\return
*/
void init_matrice(int matrice[L][C]){
	int i, j;
	for(i = 0; i<L; i++) {
		for(j=0; j<C; j++) {
			matrice[i][j] = 4;
		}
	}
}

/**
*\fn afficher_matrice(int matrice[L][C])
*\brief Permet d'afficher la matrice representant le plateau du jeu
*\param matrice[L][C] matrice representant le plateau du jeu
*\ 
*/
void affiche_matrice(int matrice[L][C]) {
	int i, j;
	for(i = 0; i<L; i++) {
		printf("------------------------------------------------------\n");
		for(j=0; j<C; j++) {
			printf(" %i\t||", matrice[i][j]);
		}
		printf("\n");
	}
		printf("-------------------------------------------------------");

}

/**
*\fn dpl_arriere(int x, int y)
*\brief Permet de se deplacer sur la grille en arriere 
*\param prend en parametre les adresses des coordonnées x et y du tas choisi à deplacer
*\return x coordonnée x d'une position, y coordonnée y d'une position 
*/
void dpl_arriere(int*x, int*y) {
		
		if((*x)<5 && (*y)==1) {
			(*x)--;
		}
		else if((*x)<5 && (*y) == 0) {
			(*x)++;
		}
		else if((*y) == 0 && (*x)==5){
			(*y)++;
		}
		else if((*y) == 0 && (*x)==0){
			(*y)--;
		}
}
/**
*\fn int dpl_avant(int x, int y)
*\brief Permet de se deplacer dans la grille en avant
*\param x coordonnée x d'une position, y coordonnée y d'une position 
*\ 
*/
void dpl_avant(int *x, int *y) {
		
		if((*x)<5 && (*y)==1) {
			(*x)++;
		}
		else if((*x) == 0 && (*y)==0){
			(*y)++;
		}
		else if(((*x)<=5 && (*y)== 0) && (x != 0)){
			(*x)--;
		}
		
		else if((*x) == 5 && (*y)==1){
			(*y)--;
		}
		
}
/**
*\fn int manger_graines(int nb_graines, int matrice[L][C], int x, int y, int *score)
*\brief Permet jouer en se deplacant sur le plateau et en mangeant les graines qui se presentent et incremente le score du joueur
*\param nb_graines (nombre de graines dans la case), matrice[L][C] (plateau du jeu), x, y (coordonnées de la case), score (score du joueur)
*\
*/
void manger_graines(int nb_graines, int matrice[L][C], int joueur, int x, int *score) {
	
	assert(nb_graines > 0);
	assert( x>=0 && x<C);
	assert( joueur>=0 && joueur<L);
	
	int i;
	int nb_gr_fin;
	t_coord graine_dbt;
	graine_dbt.joueur = joueur;
	graine_dbt.x = x;
	
	matrice[graine_dbt.joueur][graine_dbt.x] = 0;
	
	for(i = 0; i<nb_graines;i++) {
		dpl_avant(&x,&joueur);
		
		if(i == nb_graines-1) {
		nb_gr_fin = matrice[joueur][x];
		}
		matrice[joueur][x] = matrice[joueur][x]+1;
	}
	
	i = nb_graines;
	if(matrice[joueur][x] == 2 || matrice[joueur][x] == 3) {
		*score = *score+matrice[joueur][x];
		matrice[joueur][x] = 0;
		while( i>0 && nb_gr_fin<=3 && nb_gr_fin > 1) {	//initialise le score 
			(*score) = (*score)+matrice[joueur][x];
			matrice[joueur][x] = 0;
			dpl_arriere(&x, &joueur);
			nb_gr_fin = matrice[joueur][x];
			i--;
		}	
	}

}


/**
*\fn int nourir(int matrice[L][C], int joueur)
*\brief est-ce que le joueur j peut nourir son adversaie qui est affame ?
*\param matrice[L][C], joueur
*\return 0 si on ne peut pas le nourir, 1 si oui
**/
int nourir(int matrice[L][C], int joueur) {
	
	int depl;
	int x;
	if(joueur == 0) {
		depl = 6;
		for(x = 5; x>0; x--) {
			if(matrice[joueur][depl] > depl){
				return 1;
			}
			depl--;
		}
	}
	else if(joueur == 0) {
		depl = 6;
		for(depl = 0; depl>0; depl++ ){
			if(matrice[joueur][depl] > depl){
				return 1;
			}
		}
	}
	return 0;	
}
/**
*\fn int gagne(int*score,int*score2)
*\brief verifie si le score des joueurs "joueur1" ou "joueur2" a depassé 25 ou pas
*\param score (score du joueurà, joueur
*\return 0 si score des deux joueurs <25, 1 sinon
*/
 int gagne(int*score1, int *score2) {
	
	if(*score1 > 25 || *score2 >25) {
		return 1;
		}
	else 
		return 0;
 }
 
 
 /**
*\fn partie_finie(int matrice[L][C], int joueur1, int joueur2, int score1, int score2 )
*\brief Permet de verifier si une partie est terminée ou pas en verifiant si l'on peut nourir l'adversaire et si l'un des score est sup a 25
*\param matrice[L][C], joueur1, joueur2, score1, score2
*\return 1 si partie finie, 0 sinon
*/
int partie_pas_finie(int matrice[L][C], int joueur1, int joueur2, int *score1, int *score2 ) {
	if(nourir(matrice, joueur1) == 1 || nourir(matrice, joueur2) == 1) {
		return 1;
		}
	if(gagne(score1, score2)) {
		return 1;
		}
	else 
		return 0;
}


 /**
*\fn afficher_score(int score, char joueur[20])
*\brief Permet d'afficher le score du joueur en indiquant son pseudo
*\param score score du joueur, joueur pseudo du joueur
*/
void afficher_score(int score, char joueur[20]) {
	printf("\nLe score du joueur %s est %i\n", joueur, score);

}

/**
*\fn void sauvegarder(void)
*\brief Permet de sauvegarder une partie en cours, les scores et pseudos de la partie inclues
*\param 
*/
void sauvegarder(FILE * fichier) {
	
	int i, j;
	
	fprintf(fichier, "%s\n", player1);
	fprintf(fichier, "%i\n", scorej1);
	fprintf(fichier, "%s\n", player2);
	fprintf(fichier, "%i\n", scorej2);
	
	for(i = 0; i<L; i++) {
		for(j=0; j<C; j++) {
			fprintf(fichier, "%i\n", awale[i][j]);
		}
	}
	 
}

void charger_partie(FILE * fichier) {
	
	int i, j;
	int valeur;
	fscanf(fichier, "%s\n", player1);
	fscanf(fichier, "%i\n", &scorej1);
	fscanf(fichier, "%s\n", player2);
	fscanf(fichier, "%i\n", &scorej2);
	
	for(i = 0; i<L; i++) {
		for(j=0; j<C; j++) {
			fscanf(fichier, "%i", &valeur);
			awale[i][j] = valeur;
		}
	}

}

int main(){
	

	
	int joueur2 = 0;
	int joueur1 = 1;

	int choix, nb_graine, coord_x;
	char reponse;
	
	

	FILE * fic_save;

	fic_save = fopen("sauvegarde.txt", "rw+");


	printf("\nMenu :\n");
		printf(" 1 - Voulez vous commencez une nouvelle partie ?\n");
		printf(" 2 - Reprendre la partie\n");
		printf(" 3 - Quittez AWELE\n");
		printf(" ----Quel est votre choix\n");

		scanf("%i",&choix);
	
	switch(choix)
		{	case 1 : 
				printf("Joueur 1\nVeuillez saisir votre pseudonyme ?\n");
				scanf("%s", player1);
				printf("Joueur 2\nVeuillez saisir votre pseudonyme ?\n");
				scanf("%s", player2);
			
				printf("\nQue la partie commence !\n");
				init_matrice(awale);
				affiche_matrice(awale);				
				

				while(partie_pas_finie(awale, joueur1, joueur2, &scorej1, &scorej2 ) && reponse != 'q'){
				
					printf("\n%s : Saisissez votre point de jeu: \n", player1);
					scanf("%i", &coord_x);
					assert(coord_x > 0);
					
					nb_graine = awale[joueur1][coord_x-1];
					manger_graines(nb_graine, awale, joueur1, coord_x-1, &scorej1);
					affiche_matrice(awale);
					
					afficher_score(scorej1, player1);

					
					printf("\n%s : Saisissez votre point de jeu : \n", player2);
					scanf("%i", &coord_x);
					
					nb_graine = awale[joueur2][6-coord_x];
					manger_graines(nb_graine, awale, joueur2, 6-coord_x, &scorej2);
					affiche_matrice(awale);
					
					afficher_score(scorej2, player2);

					printf("Voulez vous abandonner ou quittez le jeu q pour quitter, s pour continuer\n");
					scanf("%*c%c", &reponse);
				
				}
                printf("Voulez vous sauvegarder la partie y pour Oui et n pour Non\n");
				scanf("%*c%c", &reponse);                                                                                   
				if(reponse == 'y') {
						sauvegarder(fic_save);
				}
				fclose(fic_save);
			break;
			
			/*Reprendre la partie*/
			
			case 2: 
			
				
				charger_partie(fic_save);
				
				printf("\nQue la partie commence !\n");
				
				affiche_matrice(awale);				
				

				while(partie_pas_finie(awale, joueur1, joueur2, &scorej1, &scorej2 ) && reponse != 'n'){
				
					printf("\n%s : Saisissez votre point de jeu: \n", player1);
					scanf("%i", &coord_x);
					assert(coord_x > 0);
					
					nb_graine = awale[joueur1][coord_x-1];
					manger_graines(nb_graine, awale, joueur1, coord_x-1, &scorej1);
					affiche_matrice(awale);
					
					afficher_score(scorej1, player1);

					
					printf("\n%s : Saisissez votre point de jeu : \n", player2);
					scanf("%i", &coord_x);
					
					nb_graine = awale[joueur2][6-coord_x];
					manger_graines(nb_graine, awale, joueur2, 6-coord_x, &scorej2);
					affiche_matrice(awale);
					
					afficher_score(scorej2, player2);

					printf("Voulez vous abandonner ou quittez le jeu\n");
					scanf("%*c%c", &reponse);
				
				}
			
				printf("Voulez vous sauvegarder la partie y pour Oui et n pour Non\n");
				scanf("%*c%c", &reponse);                                                                                   
				if(reponse == 'y') {
						sauvegarder(fic_save);
				}
				fclose(fic_save);
			
			break;
			case 3:  printf("Au revoir\n"); break;
			default: printf("Erreur: votre choix doit etre compris entre 1 et 6\n");
		}
	return 0;
}


