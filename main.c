#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>

#include "fonctions.h"
#include "jeu.h"



int main(){
	
	int choix, choix2;
	FILE * fic_save;

	fic_save = fopen("sauvegarde.txt", "rw+");


	printf("\nMenu :\n");
		
		printf(" 1 - Voulez vous commencez une nouvelle partie ?\n");
		printf(" 2 - Reprendre la partie\n");
		printf(" 3 - Quittez AWELE\n");
		printf(" ----Quel est votre choix\n");

		scanf("%i",&choix);
	
	switch(choix)
		{	case 1 : /* On demare une nouvelle partie*/
				
				printf(" 1 - Jouer à deux ? \n");
				printf(" 2 - Jouez avec l'ordinateur ?\n");
				printf(" ----Quel est votre choix\n");

				scanf("%i",&choix2);

				switch(choix2){
					
					case 1 :/*Le jeu est entre deux joueurs*/
							
							
							printf("Joueur 1\nVeuillez saisir votre pseudonyme ?\n");
							scanf("%s", pseudo1);
							printf("Joueur 2\nVeuillez saisir votre pseudonyme ?\n");
							scanf("%s", pseudo2);
							printf("\nQue la partie commence !\n");
							init_matrice(awale);
							affiche_matrice(awale);		
							jouer_a_deux(fic_save);
						
					break;
			
			
				/*Partie avec l'ordinateur*/
					case 2: 
							printf("Joueur 1\nVeuillez saisir votre pseudonyme ?\n");
							scanf("%s", pseudo1);
							printf("\nQue la partie commence !\n");
							init_matrice(awale);
							affiche_matrice(awale);
							jouer_avec_ordinateur(fic_save);
			
					break;

					default: printf("Erreur: votre choix doit etre compris entre 1 et 2\n"); break;
		
		
			}
			break;
			
		
		
		/*Reprendre la partie deja enregistré*/
		case 2: 
				
				charger_partie(fic_save);
				
				jouer(fic_save);
				
				
			
			break;
			case 3:  printf("Au revoir\n"); break;
			default: printf("Erreur: votre choix doit etre compris entre 1 et 6\n");
		}
	return 0;
}


