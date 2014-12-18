#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>

#include "fonctions.h"
#include "jeu.h"

int scorej1 = 0;
int scorej2 = 0;

/**
*\fn  void victoire (int score1 , score2)
*\brief Permet d'afficher le score et le pseudo du joueur victorieux
*\param score1 score du joueur 1, score 2 score du joueur 2
*/ 

void  victoire (int score1, int score2){
	if (score1>score2 ){
		printf("Victoire du %s \n Score : %i\n", pseudo1, score1);
	}
	else if (score2>score1){
		printf("Victoire du %s \n Score : %i\n", pseudo2, score2);
	}	
}

/**
*\fn int jeu_possible(int matrice [L][C], int joueur, char pseudo[20])
*\brief est-ce que le joueur j peut-il jouer ?
*\param coord_x, matrice,joueur, pseudo
*\return  0 si le joueur ne peut pas jouer, 1 sinon
**/

int jeu_possible(int matrice [L][C], int j){
	
	/*le jeu est possible si le joueur n'a pas son plateau vide
	 * -si le joueur peut nourir et si son adversaire est affamé */
	 
	if(!plateau_vide(matrice, j)){ /*si le plateau du joueur n'est pas vide*/
		if(j == JOUEUR1) 
			return (plateau_vide(matrice, JOUEUR2) && nourir(matrice, JOUEUR1)); /*renvoie vrai si l'adversaire est affamé est le joueur j capable de le nourir*/
		if(j == JOUEUR2) 
			return (plateau_vide(matrice, JOUEUR1) && nourir(matrice, JOUEUR2)); 
	}
	return (plateau_vide(matrice, j));
	
	/*Renvoi vraie si
	 * -le plateau du joueur n'est pas vide et que l'adversaire est affamé et le joueur j capable de le nourir*/
	 
	 /*Renvoie faux si 
	  * -si le jeu n'est pas possible cad ->> si le plateau du joueur j est vide 
	  * 								  ->> si */
}



/**
*\fn int coup_possible(int coord_x, int matrice [L][C], int joueur, char pseudo[20])
*\brief est-ce que le joueur j peut jouer à la case de coord_x
*\param coord_x, matrice,joueur, pseudo
*\return  1 si la partie n'est plus jouable, 0 sinon
**/

int coup_possible(int coord_x, int matrice [L][C], int joueur){
	
	
	// si l'adversaire est affamé -> est-ce que la case coord_x peut nourrir l'adversaire
	
	if(joueur == JOUEUR1 && plateau_vide(matrice,JOUEUR2)) {
		
		// si elle est vide on verifie si le joueur adverse peut le nourir avce la case coord_x !
		if(nourir_case(matrice, JOUEUR1, coord_x)){
			return 1;
		}
		else {
			return 0; //on ne peut pas jouer ici ...
		}
	}
	else if((joueur == JOUEUR2 || joueur == ORDINATEUR) && plateau_vide(matrice,JOUEUR1)) {

		if(nourir_case(matrice, ORDINATEUR, coord_x) && strcmp(pseudo2, "Ordinateur") == 1)
			return 1;
		
		else if(nourir_case(matrice, JOUEUR2, coord_x) && strcmp(pseudo2, "Ordinateur") != 1) 
			return 1;
	}
		else 
			return 0;
	return 1;
}

/**
*\fn void sauvegarder(FILE*fichier)
*\brief Permet de sauvegarder une partie en cours, les scores et pseudos de la partie inclues
*\param fichier, le fichier de sauvegarde
*/
void sauvegarder(FILE * fichier) {
	
	int i, j;
	
	fprintf(fichier, "%s\n", pseudo1);
	fprintf(fichier, "%i\n", scorej1);
	fprintf(fichier, "%s\n", pseudo2);
	fprintf(fichier, "%i\n", scorej2);
	
	for(i = 0; i<L; i++) {
		for(j=0; j<C; j++) {
			fprintf(fichier, "%i\n", awale[i][j]);
		}
	}
	 
}
/**
*\fn void sauvegarder(FILE*fichier)
*\brief Permet de charger une partie sauvegarder, les scores et pseudos de la partie inclues
*\param fichier, le fichier de sauvegarde à recuperer
*/
void charger_partie(FILE * fichier) {
	
	int i, j;
	int valeur;
	fscanf(fichier, "%s\n", pseudo1);
	fscanf(fichier, "%i\n", &scorej1);
	fscanf(fichier, "%s\n", pseudo2);
	fscanf(fichier, "%i\n", &scorej2);
	
	for(i = 0; i<L; i++) {
		for(j=0; j<C; j++) {
			fscanf(fichier, "%i", &valeur);
			awale[i][j] = valeur;
		}
	}

}
/**
*\fn void jouer_a_deux(int joueur1, int joueur2, FILE * fichier)
*\brief Permet de joueur
*\param fichier, le fichier de sauvegarde à recuperer
*/
 void jouer_a_deux(FILE * fichier) {
	
	int nb_graine;
	int case_aide;
	int coord_x;
	char reponse;
	char rep_aide;
	int nb_jocker_j1 = 3;
	int nb_jocker_j2 = 3;

	
				
			while(partie_pas_finie(awale, &scorej1, &scorej2 ) && reponse != 'q'){
					
					
							/*Tour du joueur 1*/
				
				if(aide(JOUEUR1, awale, &case_aide) && nb_jocker_j1 <= 3 && nb_jocker_j1 > 0) {
				printf("\n%s, voulez vous une aide, y pour Oui, n pour Non ?\n", pseudo1);
				scanf("%*c%c", &rep_aide);
					if(rep_aide == 'y') {
						printf("Bougez la case %i !", case_aide);
						nb_jocker_j1--;
					}
				}
					
				if(!jeu_possible(awale, JOUEUR1)){ /*On verifie si le jeu est possible*/
					victoire(scorej1, scorej2);
					break;

				}	
				
				printf("\n%s : Saisissez votre point de jeu: \n", pseudo1);
				scanf("%*c%i", &coord_x);
				
				/*Si le joueur est affamé est qu'on peut le nourir, on verifie si le coord_x saisie permet de le nourir 
				 * et on repete la saisie tant que la bonne case n'est pas saisie
				 */
				 
				if(jeu_possible(awale, JOUEUR1)) {
					
					do{
						printf("\n%s : Attention vous devez nourir votre adversaire !!\n", pseudo1); 
						printf("\n%s : Saisissez votre point de jeu: \n", pseudo1);
						scanf("%*c%i", &coord_x);
						
					}while(!coup_possible(coord_x-1, awale, JOUEUR1));
				}
					
				do {
					if(coord_x > C || coord_x < 0){ //si les coordonnées sont mauvaises
					printf("\nVotre choix doit etre compris entre 1 et 6\n");
					}
					else {
						nb_graine = awale[JOUEUR1][coord_x-1];
						if(nb_graine == 0){ //si la case est vide		
							printf("\nLa case est vide !! On ne peut pas bouger la case !!\n");
							printf("\n%s : Saisissez votre point de jeu : \n", pseudo1);
							scanf("%*c%i", &coord_x);
						}
					}
				
				} while(coord_x > C || coord_x < 0 || nb_graine == 0 || !coup_possible(coord_x, awale, JOUEUR1));			
				
				
				
				nb_graine = awale[JOUEUR1][coord_x-1];
				manger_graines(nb_graine, awale, JOUEUR1, coord_x-1, &scorej1);
				affiche_matrice(awale);
					
				afficher_score(scorej1, pseudo1);

				/*Tour du joueur 2*/

				if(aide(JOUEUR2, awale, &case_aide) && nb_jocker_j2 <= 3  && nb_jocker_j2 > 0) {
					printf("\n%s, voulez vous une aide, y pour Oui, n pour Non ?\n", pseudo2);
					scanf("%*c%c", &rep_aide);
						if(rep_aide == 'y') {
							printf("Bougez la case %i !", case_aide);
							nb_jocker_j2--;

						}
				}
				
				if(!jeu_possible(awale, JOUEUR1)){ /*On verifie si le jeu est possible*/
					victoire(scorej1, scorej2);
					break;

				}	
		
				printf("\n%s : Saisissez votre point de jeu : \n", pseudo2);
				scanf("%i", &coord_x);
				
				/*Si le joueur est affamé est qu'on peut le nourir, on verifie si le coord_x saisie permet de le nourir 
				 * et on repete la saisie tant que la bonne case n'est pas saisie
				 */
				if(jeu_possible(awale, JOUEUR2)) {	
					
					do{
						printf("\n%s : Attention vous devez nourir votre adversaire !!\n", pseudo2); 
						printf("\n%s : Saisissez votre point de jeu: \n", pseudo2);
						scanf("%*c%i", &coord_x);
						
					}while(!coup_possible(coord_x-1, awale, JOUEUR2));
				}
				
				do {
					if(coord_x > C || coord_x < 0){ //si les coordonnées sont mauvaises
					printf("\nVotre choix doit etre compris entre 1 et 6\n");
					}
					else {
						nb_graine = awale[JOUEUR2][coord_x-1];
						if(nb_graine == 0){ //si la case est vide		
							printf("\nLa case est vide !! On ne peut pas bouger la case !!\n");
							printf("\n%s : Saisissez votre point de jeu : \n", pseudo2);
							scanf("%*c%i", &coord_x);
						}
					}
				} while(coord_x > C || coord_x < 0 || nb_graine == 0);			
				  
				manger_graines(nb_graine, awale, JOUEUR2, coord_x-1, &scorej2);
				affiche_matrice(awale);
				afficher_score(scorej2, pseudo2);

				printf("Voulez quittez le jeu q pour quitter, s pour continuer\n");
				scanf("%*c%c", &reponse);
				
			}
			/*Demander si la partie devrait etre sauvegarder*/
			
			printf("Voulez vous sauvegarder la partie y pour Oui et n pour Non\n");
			scanf("%*c%c", &reponse);                                                                                   
			if(reponse == 'y') {
				sauvegarder(fichier);
			}
			fclose(fichier);
			if (!partie_pas_finie(awale, &scorej1, &scorej2)) {
				victoire(scorej1,scorej2);
			}
}			
				
				
/**
*\fn void jouer_avec_ordinateur(int joueur1, int joueur2, FILE * fichier)
*\brief Permet de joueur
*\param fichier, le fichier de sauvegarde à recuperer
*/

void jouer_avec_ordinateur(FILE * fichier) {
	

	int nb_graine, coord_x;
	int case_aide;
	int case_ordi;
	char reponse;
	char rep_aide;
	int nb_jocker_j1 = 3;
		
		while(partie_pas_finie(awale, &scorej1, &scorej2 ) && reponse != 'q'){
					
		
			if(aide(JOUEUR1, awale, &case_aide) && nb_jocker_j1 <= 3  && nb_jocker_j1 > 0) {
				printf("\n%s, voulez vous une aide, y pour Oui, n pour Non ?\n", pseudo1);
				scanf("%*c%c", &rep_aide);
					if(rep_aide == 'y') {
						printf("Bougez la case %i !", case_aide);
						nb_jocker_j1--;
					}
				}
			if(!jeu_possible(awale, JOUEUR1)){ /*On verifie si le jeu est possible*/
					victoire(scorej1, scorej2);
					break;

				}	
				
			printf("\n%s : Saisissez votre point de jeu: \n", pseudo1);
			scanf("%i", &coord_x);
			
			/*Si le joueur est affamé est qu'on peut le nourir, on verifie si le coord_x saisie permet de le nourir 
			* et on repete la saisie tant que la bonne case n'est pas saisie
			*/
			if(jeu_possible(awale, JOUEUR1)) {
					
					do{
						printf("\n%s : Attention vous devez nourir votre adversaire !!\n", pseudo1); 
						printf("\n%s : Saisissez votre point de jeu: \n", pseudo1);
						scanf("%*c%i", &coord_x);
						
					}while(!coup_possible(coord_x-1, awale, JOUEUR1));
				}
			
				
			do {
					
					if(coord_x > C || coord_x < 0){ //si les coordonnées sont mauvaises
					printf("\nVotre choix doit etre compris entre 1 et 6\n");
					}
					else {
						nb_graine = awale[JOUEUR1][coord_x-1];
						if(nb_graine == 0){ //si la case est vide		
							printf("\nLa case est vide !! On ne peut pas bouger la case !!\n");
							printf("\n%s : Saisissez votre point de jeu : \n", pseudo1);
							scanf("%*c%i", &coord_x);
						}
					}
				
			} while(coord_x > C || coord_x < 0 || nb_graine == 0);	
			
			
			
				
			nb_graine = awale[JOUEUR1][coord_x-1];
			manger_graines(nb_graine, awale, JOUEUR1, coord_x-1, &scorej1);
			affiche_matrice(awale);
					
			afficher_score(scorej1, pseudo1);
							
			/*Tour de l'ordinateur*/
							
			printf("\n Tour de l' Ordinateur \n");
			strcpy(pseudo2, "Ordinateur");
			
			if(!jeu_possible(awale, ORDINATEUR)){ /*On verifie si le jeu est possible*/
					victoire(scorej1, scorej2);
					break;

				}	

			/*Recuperer la case que l'ordinateur va joué*/
							
			case_ordi = jeu_ordi(awale);
			

			nb_graine = awale[JOUEUR2][case_ordi];
			manger_graines(nb_graine, awale, JOUEUR2, case_ordi, &scorej2);
			affiche_matrice(awale);
					
			afficher_score(scorej2, pseudo2);
							
			printf("Voulez vous quittez le jeu q pour quitter, s pour continuer\n");
			scanf("%*c%c", &reponse);
				
		}
		printf("Voulez vous sauvegarder la partie y pour Oui et n pour Non\n");
		scanf("%*c%c", &reponse);                                                                                   
		if(reponse == 'y') {
			sauvegarder(fichier);
		}
		fclose(fichier);
		 /*if (!partie_pas_finie(awale, &scorej1, &scorej2))
			victoire(scorej1,scorej2);*/
			
	}

	


void jouer(FILE * fichier){
	
				if(strcmp(pseudo2, "Ordinateur") == 0) {
					affiche_matrice(awale);		
					jouer_avec_ordinateur(fichier);
				}
				else {
					affiche_matrice(awale);		
					jouer_a_deux(fichier);
				}
	}



