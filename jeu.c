#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>

#include "fonctions.h"
#include "jeu.h"



int awale[L][C];
int scorej1 = 0;
int scorej2 = 0;
char pseudo1[20];
char pseudo2[20];

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
	
				
			while(partie_pas_finie(awale, &scorej1, &scorej2 ) && reponse != 'q'){
					
					
							/*Tour du joueur 1*/
				if(aide(JOUEUR1, awale, &case_aide) ) {
				printf("\n%s, voulez vous une aide, y pour Oui, n pour Non ?\n", pseudo1);
				scanf("%*c%c", &rep_aide);
					if(rep_aide == 'y') {
						printf("Bougez la case %i !", case_aide);
					}
				}
					
				printf("\n%s : Saisissez votre point de jeu: \n", pseudo1);
				scanf("%*c%i", &coord_x);
							
				while(coord_x > C || coord_x < 0) {
							
					printf("\nVotre choix doit etre compris entre 1 et 6\n");
					printf("\n%s : Saisissez votre point de jeu: \n", pseudo1);
					scanf("%i", &coord_x);
							
				}
				assert(coord_x > 0);
					
				nb_graine = awale[JOUEUR1][coord_x-1];
				manger_graines(nb_graine, awale, JOUEUR1, coord_x-1, &scorej1);
				affiche_matrice(awale);
					
				afficher_score(scorej1, pseudo1);

				/*Tour du joueur 2*/

				if(aide(JOUEUR2, awale, &case_aide)) {
					printf("\n%s, voulez vous une aide, y pour Oui, n pour Non ?\n", pseudo2);
					scanf("%*c%c", &rep_aide);
						if(rep_aide == 'y') {
							printf("Bougez la case %i !", case_aide);
						}
				}
				
				// faire
				// 		afficher un message pour la saisie
				// 		récupère la coordonnée
				// 		vérifier que cette coord est valide, sinon -> afficher message d'erreur
				// 		vérifier que la case n'est pas vide -> sinon message d'erreur
				// tant que (coordonnées invalides OU case est vide )
				
				
				do {
					printf("\n%s : Saisissez votre point de jeu : \n", pseudo2);
					scanf("%*c%i", &coord_x);
					
					if(coord_x > C || coord_x < 0){ //si les coordonnées sont mauvaises
						printf("\nVotre choix doit etre compris entre 1 et 6\n");
					}
					else {
						nb_graine = awale[JOUEUR2][coord_x-1];
						if(nb_graine == 0){ //si la case est vide		
							printf("\n la case est vide !! on ne pas bouger la case !!\n");
						}
					}
				
				} while(coord_x > C || coord_x < 0 || nb_graine == 0);
				
				  
				 // ici on est sur que la case coord_x n'est pas vide !
				 // on peut appeler manger_graines sans probleme !
				  
				manger_graines(nb_graine, awale, JOUEUR2, coord_x-1, &scorej2);
				affiche_matrice(awale);
					
				afficher_score(scorej2, pseudo2);

				printf("Voulez vous abandonner ou quittez le jeu q pour quitter, s pour continuer\n");
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
		
		while(partie_pas_finie(awale, &scorej1, &scorej2 ) && reponse != 'q'){
					
		
			if(aide(JOUEUR1, awale, &case_aide)) {
				printf("\n%s, voulez vous une aide, y pour Oui, n pour Non ?\n", pseudo1);
				scanf("%*c%c", &rep_aide);
					if(rep_aide == 'y') {
						printf("Bougez la case %i !", case_aide);
					}
			}
			printf("\n%s : Saisissez votre point de jeu: \n", pseudo1);
			scanf("%*c%i", &coord_x);
							
			while(coord_x > C || coord_x < 0) {
							
				printf("\nVotre choix doit etre compris entre 1 et 6\n");
				printf("\n%s : Saisissez votre point de jeu: \n", pseudo1);
				scanf("%i", &coord_x);
							
			} 
							
			assert(coord_x > 0);
					
			nb_graine = awale[JOUEUR1][coord_x-1];
			manger_graines(nb_graine, awale, JOUEUR1, coord_x-1, &scorej1);
			affiche_matrice(awale);
					
			afficher_score(scorej1, pseudo1);
							
			/*Tour de l'ordinateur*/
							
			printf("\n Tour de l' Ordinateur \n");
			strcpy(pseudo2, "Ordinateur");
			
			/*Recuperer la case que l'ordinateur va joué*/
							
			case_ordi = jeu_ordi(JOUEUR2, awale);
					
			nb_graine = awale[JOUEUR2][case_ordi];
			manger_graines(nb_graine, awale, JOUEUR2, case_ordi, &scorej2);
			affiche_matrice(awale);
					
			afficher_score(scorej2, pseudo2);
							
			printf("Voulez vous abandonner ou quittez le jeu q pour quitter, s pour continuer\n");
			scanf("%*c%c", &reponse);
				
		}
		printf("Voulez vous sauvegarder la partie y pour Oui et n pour Non\n");
		scanf("%*c%c", &reponse);                                                                                   
		if(reponse == 'y') {
			sauvegarder(fichier);
		}
		fclose(fichier);
		 if (!partie_pas_finie(awale, &scorej1, &scorej2))
			victoire(scorej1,scorej2);
			
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

