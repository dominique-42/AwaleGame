/**
 * \file main.c
 * \brief Programme principal du lancement du jeu awale.
 * \author Okrou Poda, Souleiman Iman Choukri		
 * \version 0.1
 * \date 19 novembre 2014
 *
 * Projet d'etude L2 SPI : Programmation du Jeu Awale
 *
 */

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>

#include "fonctions.h"
#include "jeu.h"
#define M 100

/**
*\fn int main(void)
*\brief Entrée du programme.
*\return EXIT_SUCCESS - Arrêt normal du programme.
*/
int main(void){
	
	int choix, choix2;
	t_joueur record_score[M];
	int nb_score = 0;
	FILE * fic_save;
	FILE * fic_records;	
	fic_save = fopen("sauvegarde.txt", "r+");
	fic_records = fopen("records.txt", "a+");
	

	printf("**********************************************************************************************\n");
	printf("**********************************************************************************************\n");
	printf("                                         AWALE                                                \n");
	printf("**********************************************************************************************\n");
	printf("**********************************************************************************************\n");

	printf("\nMenu :\n");
		
		printf(" 1 - Nouvelle partie\n");
		printf(" 2 - Continuer \n");
		printf(" 3 - Records\n");
		printf(" 4 - Instructions\n");
		printf(" 5 - Quittez AWELE\n");
		printf(" ----Quel est votre choix ?\n");

		scanf("%i",&choix);
	
	switch(choix)
		{	case 1 : /** On demare une nouvelle partie*/
				
				printf("\t\t\t 1 - Jeu à deux\n");
				printf("\t\t\t 2 - Jeu avec l'ordinateur\n");
				printf("\t\t\t ----Quel est votre choix\n");

				scanf("%i",&choix2);

				switch(choix2){
					
					case 1 :/**Le jeu est entre deux joueurs*/
							
							
							printf("Joueur 1\nVeuillez saisir votre pseudonyme ?\n");
							scanf("%s", pseudo1);
							printf("Joueur 2\nVeuillez saisir votre pseudonyme ?\n");
							scanf("%s", pseudo2);
							printf("\nQue la partie commence !\n");
							init_matrice(awale);
							affiche_matrice(awale);		
							jouer_a_deux(fic_save, fic_records);
							fclose(fic_records);
							fclose(fic_save);		

							
					break;
			
			
				
					case 2: /**Le jeu est avec l'ordinateur*/
							printf("Joueur 1\nVeuillez saisir votre pseudonyme ?\n");
							scanf("%s", pseudo1);
							printf("\nQue la partie commence !\n");
							init_matrice(awale);
							affiche_matrice(awale);
							jouer_avec_ordinateur(fic_save, fic_records);
							fclose(fic_records);
							fclose(fic_save);		


			
					break;

					default: printf("Erreur: votre choix doit etre compris entre 1 et 2\n");
		
		
			}
			break;
			
		
		
		/**Reprendre la partie deja enregistré*/
		case 2: 
				if(charger_partie(fic_save)){
					jouer(fic_save, fic_records);
					fclose(fic_records);
					fclose(fic_save);		
				}
				
		break;
		
		/**Afficher la liste des scores*/
		case 3:
				classer_records(fic_records, record_score, &nb_score);
				fclose(fic_records);
		
		break;
		
		/**Afficher les regles du jeu*/
		case 4:
				regles_jeu();
		break;
	
		case 5:  printf("Au revoir\n"); break;
		default: printf("Erreur: votre choix doit etre compris entre 1 et 5\n");
		}
	return EXIT_SUCCESS;
}


