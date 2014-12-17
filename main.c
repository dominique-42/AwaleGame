#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>

#include "fonctions.h"
#include "jeu.h"



/**
*\fn  void victoire (int score1 , score2)
*\brief Permet d'afficher le score et le pseudo du joueur victorieux
*\param score1 score du joueur 1, score 2 score du joueur 2
*/ 

void  victoire (int score1, int score2){
	if (score1>score2 ){
		printf("Victoire du %s \n Score : %i\n", player1, score1);
	}
	else if (score2>score1){
		printf("Victoire du %s \n Score : %i\n", player2, score2);
	}	
}


/**
*\fn void jouer_a_deux(int joueur1, int joueur2, FILE * fichier)
*\brief Permet de joueur
*\param fichier, le fichier de sauvegarde à recuperer
*/
 void jouer_a_deux(int joueur1, int joueur2, FILE * fichier) {
	
	int nb_graine;
	int case_aide;
	int coord_x;
	char reponse;
	char rep_aide;
	
			printf("Joueur 1\nVeuillez saisir votre pseudonyme ?\n");
			scanf("%s", player1);
			printf("Joueur 2\nVeuillez saisir votre pseudonyme ?\n");
			scanf("%s", player2);
			
			printf("\nQue la partie commence !\n");
			init_matrice(awale);
			affiche_matrice(awale);				
				

			while(partie_pas_finie(awale, joueur1, joueur2, &scorej1, &scorej2 ) && reponse != 'q'){
					
					
							/*Tour du joueur 1*/
				if(aide(joueur1, awale, &case_aide) ) {
				printf("\nVoulez vous une aide, y pour Oui, n pour Non ?\n");
				scanf("%*c%c", &rep_aide);
					if(rep_aide == 'y') {
						printf("Bougez la case %i !", case_aide);
					}
				}
					
				printf("\n%s : Saisissez votre point de jeu: \n", player1);
				scanf("%*c%i", &coord_x);
							
				while(coord_x > C || coord_x < 0) {
							
					printf("\nVotre choix doit etre compris entre 1 et 6\n");
					printf("\n%s : Saisissez votre point de jeu: \n", player1);
					scanf("%i", &coord_x);
							
				}
				assert(coord_x > 0);
					
				nb_graine = awale[joueur1][coord_x-1];
				manger_graines(nb_graine, awale, joueur1, coord_x-1, &scorej1);
				affiche_matrice(awale);
					
				afficher_score(scorej1, player1);

				/*Tour du joueur 2*/

				if(aide(joueur2, awale, &case_aide)) {
					printf("\nVoulez vous une aide, y pour Oui, n pour Non ?\n");
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
					printf("\n%s : Saisissez votre point de jeu : \n", player2);
					scanf("%*c%i", &coord_x);
					
					if(coord_x > C || coord_x < 0){ //si les coordonnées sont mauvaises
						printf("\nVotre choix doit etre compris entre 1 et 6\n");
					}
					else {
						nb_graine = awale[joueur2][coord_x-1];
						if(nb_graine == 0){ //si la case est vide		
							printf("\n la case est vide !! on ne pas bouger la case !!\n");
						}
					}
				
				} while(coord_x > C || coord_x < 0 || nb_graine == 0);
				
				/*while(coord_x > C || coord_x < 0) {
							
					printf("\nVotre choix doit etre compris entre 1 et 6\n");
					printf("\n%s : Saisissez votre point de jeu: \n", player1);
					scanf("%i", &coord_x);
							
				}
				nb_graine = awale[joueur2][coord_x-1];
			    while (nb_graine == 0) {
					printf("\n la case est vide !! on ne pas bouger la case !!\n");
					printf("\n%s: saisissez un point de jeu superieur à 0 \n");
					scanf("%i", &coord_x);
					nb_graine = awale[joueur2][coord_x-1];
				  }*/
				  
				 // ici on est sur que la case coord_x n'est pas vide !
				 // on peut appeler manger_graines sans probleme !
				  
				manger_graines(nb_graine, awale, joueur2, coord_x-1, &scorej2);
				affiche_matrice(awale);
					
				afficher_score(scorej2, player2);

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
			if (!partie_pas_finie(awale, joueur1, joueur2, &scorej1, &scorej2))
				victoire(scorej1,scorej2);
}
/**
*\fn void jouer_avec_ordinateur(int joueur1, int joueur2, FILE * fichier)
*\brief Permet de joueur
*\param fichier, le fichier de sauvegarde à recuperer
*/

void jouer_avec_ordinateur(int joueur1, int joueur2, FILE * fichier) {
	

	int nb_graine, coord_x;
	int case_aide;
	int case_ordi;
	
	char reponse;
	
	char rep_aide;
		
		
		printf("Joueur 1\nVeuillez saisir votre pseudonyme ?\n");
		scanf("%s", player1);
		while(partie_pas_finie(awale, joueur1, joueur2, &scorej1, &scorej2 ) && reponse != 'q'){
					
		
			if(aide(joueur1, awale, &case_aide)) {
				printf("\nVoulez vous une aide, y pour Oui, n pour Non ?\n");
				scanf("%*c%c", &rep_aide);
					if(rep_aide == 'y') {
						printf("Bougez la case %i !", case_aide);
					}
			}
			printf("\n%s : Saisissez votre point de jeu: \n", player1);
			scanf("%*c%i", &coord_x);
							
			while(coord_x > C || coord_x < 0) {
							
				printf("\nVotre choix doit etre compris entre 1 et 6\n");
				printf("\n%s : Saisissez votre point de jeu: \n", player1);
				scanf("%i", &coord_x);
							
			} 
							
			assert(coord_x > 0);
					
			nb_graine = awale[joueur1][coord_x-1];
			manger_graines(nb_graine, awale, joueur1, coord_x-1, &scorej1);
			affiche_matrice(awale);
					
			afficher_score(scorej1, player1);
							
			/*Tour de l'ordinateur*/
							
			printf("\n Tour de l' Ordinateur \n");
			strcpy(player2, "Ordinateur");
			
			/*Recuperer la case que l'ordinateur va joué*/
							
			case_ordi = jeu_ordi(joueur2, awale);
					
			nb_graine = awale[joueur2][case_ordi];
			manger_graines(nb_graine, awale, joueur2, case_ordi, &scorej2);
			affiche_matrice(awale);
					
			afficher_score(scorej2, player2);
							
			printf("Voulez vous abandonner ou quittez le jeu q pour quitter, s pour continuer\n");
			scanf("%*c%c", &reponse);
				
		}
		printf("Voulez vous sauvegarder la partie y pour Oui et n pour Non\n");
		scanf("%*c%c", &reponse);                                                                                   
		if(reponse == 'y') {
			sauvegarder(fichier);
		}
		fclose(fichier);
		 if (!partie_pas_finie(awale, joueur1, joueur2, &scorej1, &scorej2))
			victoire(scorej1,scorej2);
			
	}
	




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


