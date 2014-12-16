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
	
			
			
			printf("Joueur 1\nVeuillez saisir votre pseudonyme ?\n");
			scanf("%s", pseudo1);
			printf("Joueur 2\nVeuillez saisir votre pseudonyme ?\n");
			scanf("%s", pseudo2);
			init_matrice(awale);
			affiche_matrice(awale);				
				

			while(partie_pas_finie(awale, &scorej1, &scorej2 ) && reponse != 'q'){
					
					
							/*Tour du joueur 1*/
				if(aide(joueur1, awale, &case_aide) ) {
				printf("\nVoulez vous une aide, y pour Oui, n pour Non ?\n");
				scanf("%*c%c", &rep_aide);
					if(rep_aide == 'y') {
						printf("Bougez la case %i !", case_aide);
					}
				}
					
				printf("\n%s : Saisissez votre point de jeu: \n", pseudo1);
				scanf("%*c%i", &coord_x);
							
				while(coord_x > C || coord_x < 0) {
							
					printf("\nVotre choix doit etre compris entre 1 et 6\n");
					printf("\n%s : Saisissez votre point de jeu: \n", player1);
					scanf("%i", &coord_x);
							
				}
				assert(coord_x > 0);
					
				nb_graine = awale[JOUEUR1][coord_x-1];
				manger_graines(nb_graine, awale, JOUEUR1, coord_x-1, &scorej1);
				affiche_matrice(awale);
					
				afficher_score(scorej1, pseudo1);

				/*Tour du joueur 2*/

				if(aide(joueur2, awale, &case_aide)) {
					printf("\nVoulez vous une aide, y pour Oui, n pour Non ?\n");
					scanf("%*c%c", &rep_aide);
						if(rep_aide == 'y') {
							printf("Bougez la case %i !", case_aide);
						}
				}
							
				printf("\n%s : Saisissez votre point de jeu : \n", pseudo2);
				scanf("%*c%i", &coord_x);
							
				while(coord_x > C || coord_x < 0) {
							
					printf("\nVotre choix doit etre compris entre 1 et 6\n");
					printf("\n%s : Saisissez votre point de jeu: \n", pseudo2);
					scanf("%i", &coord_x);
							
				}
				nb_graine = awale[JOUEUR2][coord_x-1];
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
		
		
		printf("Joueur 1\nVeuillez saisir votre pseudonyme ?\n");
		scanf("%s", pseudo1);

		printf("\nQue la partie commence !\n");
		init_matrice(awale);
		affiche_matrice(awale);				
				

		while(partie_pas_finie(awale, &scorej1, &scorej2 ) && reponse != 'q'){
					
		
			if(aide(joueur1, awale, &case_aide)) {
				printf("\nVoulez vous une aide, y pour Oui, n pour Non ?\n");
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
			strcpy(player2, "Ordinateur");
			
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
			
	}

void jouer(FILE * fichier){
	
				if(strcmp(pseudo2, "Ordinateur") == 0) {
					jouer_avec_ordinateur(fic_save);
				}
				else {
					jouer_a_deux(fic_save);
				}
	}

