/**
 * \file jeu.c
 * \brief Fichier contenant les fonctions necessaire au déroulement du jeu.
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


int faux = 0; /**<Booleen faux*/
int vrai = 1; /**<Booleen vrai*/

int scorej1 = 0; /**<Score du JOUEUR1*/
int scorej2 = 0; /**<Score du JOUEUR2*/
int nb_tours = 0; /**<Nombre de tour dont les coups gangnants de la partie sont difficile à trouver*/


/**
*\fn  void victoire(FILE * fichier)
*\brief Permet d'afficher le score et le pseudo du joueur victorieux et de l'enregistrer dans le record des scores
*\param fichier Fichier où les scores des joeuurs gagnants sont enregistrés
*/ 

void  victoire(FILE * fichier){
	
	if (scorej1>scorej2 ){
		printf("\n %s, A toi la VICTOIRE !!\n Score : %i\n", pseudo1, scorej1);
		fprintf(fichier, "%s\n", pseudo1);
		fprintf(fichier, "%i\n", scorej1);
		
	}
	else if (scorej2>scorej1){
		printf("\n %s, A toi la VICTOIRE !!\n Score : %i\n", pseudo2, scorej2);
		fprintf(fichier, "%s\n", pseudo2);
		fprintf(fichier, "%i\n", scorej2);
	}	
}

/**
*\fn int gain_difficile(int matrice[L][C], int * nb_tour)
*\brief Permet de detecter si un tour est difficile à jouer et incremente le nombre de tour où ce cas est rencontré.
*\param  matrice Plateau de jeu
*\param nb_tour Pointeur sur le nombre de tour 
*\return  0 si il existe des coup gagnants, 1 si c'est difficile de trouver des coups gagnants
**/

int gain_difficile(int matrice[L][C], int * nb_tour) {

	if(!plateau_vide(matrice, JOUEUR1) && !plateau_vide(matrice, JOUEUR2) && !nourir(matrice, JOUEUR1) && !nourir(matrice, JOUEUR2)){
		(*nb_tour)++;
		return 1;
	}
	return 0;
}

/**
*\fn int jeu_possible(int matrice[L][C], int joueur)
*\brief Est-ce que le joueur "joueur" peut-il jouer ?
*\param  matrice Represente le plateau de jeu
*\param  joueur L'un des joueur
*\return  Renvoi vraie (1) si :
* -le plateau du joueur n'est pas vide et que l'adversaire est affamé et le joueur j capable de le nourir
* -le plateau du joueur vide et son adversaire capable de le nourir
* -le plateau du joueur n'est pas vide
* Renvoie faux (0) si :
* -le jeu n'est pas possible si l'adversaire est affamé et le joueur incapable de le nourir
* -le plateau du joueur est vide et que l'adversaire est incapable de le nourir  
**/


int jeu_possible(int matrice[L][C], int joueur){
	

	if(!plateau_vide(matrice, joueur)){ /*Si le plateau du joueur n'est pas vide*/
		
		if(joueur == JOUEUR1 && plateau_vide(matrice, JOUEUR2) && nourir(matrice, JOUEUR1)) 
			return 1; 
		else if(joueur == JOUEUR1 && !plateau_vide(matrice, JOUEUR2) && nourir(matrice, JOUEUR1))
			return 1;
		else if(joueur == JOUEUR1 && !plateau_vide(matrice, JOUEUR2) && !nourir(matrice, JOUEUR1))
			return 1;
		else if(joueur == JOUEUR1 && plateau_vide(matrice, JOUEUR2) && !nourir(matrice, JOUEUR1))
			return 0;
		
		if(joueur == JOUEUR2 && plateau_vide(matrice, JOUEUR1) && nourir(matrice, JOUEUR2)) 
			return 1; 
		else if(joueur == JOUEUR2 && !plateau_vide(matrice, JOUEUR1) && nourir(matrice, JOUEUR2))
			return 1;
		else if(joueur == JOUEUR2 && !plateau_vide(matrice, JOUEUR1) && !nourir(matrice, JOUEUR2))
			return 1;
		else if(joueur == JOUEUR2 && plateau_vide(matrice, JOUEUR1) && !nourir(matrice, JOUEUR2))
			return 0;
	}
	else if(plateau_vide(matrice, joueur)) {/*Si le plateau du joueur est vide*/
		if(joueur == JOUEUR1 && plateau_vide(matrice, JOUEUR1) && !nourir(matrice, JOUEUR2)) 
			return 0; 
		else if(joueur == JOUEUR1 && plateau_vide(matrice, JOUEUR1) && nourir(matrice, JOUEUR2)) 
			return 1; 
		if(joueur == JOUEUR2 && plateau_vide(matrice, JOUEUR2) && !nourir(matrice, JOUEUR1)) 
			return 0; 
		if(joueur == JOUEUR2 && plateau_vide(matrice, JOUEUR2) && nourir(matrice, JOUEUR1)) 
			return 1; 	
	}
	return 0;
}



/**
*\fn int coup_possible(int coord_x, int matrice [L][C], int joueur)
*\brief Est-ce que le joueur j peut jouer à la case de coord_x ?
*\param coord_x Coordonnée x à verifier 
*\param matrice Plateau du jeu
*\param joueur 
*\return  1 si la case saisie est joueable, 0 sinon
**/

int coup_possible(int coord_x, int matrice [L][C], int joueur){
	
	/*Si l'adversaire est affamé est ce que cette case peut le nourir*/
	if(joueur == JOUEUR1 && plateau_vide(matrice,JOUEUR2)) {
	
		if(nourir_case(matrice, JOUEUR1, coord_x))
			return 1;
		else
			return 0; /*On ne peut pas jouer ici*/
	}
	else if((joueur == JOUEUR2 || joueur == ORDINATEUR) && plateau_vide(matrice,JOUEUR1)) {

		if(nourir_case(matrice, joueur, coord_x)) 
			return 1;
		else 
			return 0; /*On ne peut pas jouer ici*/
	}	
	return 1;
}

/**
*\fn  void regles_jeu(void)
*\brief Permet d'afficher les regles du jeu
*/ 

void regles_jeu(void) {
	fprintf(stderr, "Les règles de l'Awalé.\n");

	fprintf(stderr,"\nRègle 1 : Le terrain de jeu .\nLe but du jeu est de s'emparer d'un maximum de graines. Le terrain de jeu est divisé en deux territoires de 6 trous chacun. Le territoire du joueur 1 est le territoire Sud; celui du Joueur 2 est le territoire Nord.\n"); 

	fprintf(stderr,"\nRègle 2 : Le tour de jeu.\n"); 
	fprintf(stderr,"Prendre l'ensemble des graines présentes en entrant les nombre de 1 à 6 puis entrez votre choix.\n");
	fprintf(stderr,"Si la dernière graine semée tombe dans un trou de l'adversaire comportant déjà 1 ou 2 graines, le joueur capture les 2 ou 3 graines résultantes.\n");

	fprintf(stderr,"\nRègle 4: Capture multiple\n");
	fprintf(stderr,"Lorsqu'un joueur s'empare de deux ou trois graines, si la case précédente contient également deux ou trois graines, elles sont capturées aussi et ainsi de suite.\n");

	fprintf(stderr,"\nRègle 5: Donner à manger\n");
	fprintf(stderr,"On n'a pas le droit d'affamer l'adversaire en capturant toutes ses graines ou en refusant de le nourir si il est affamé, on doit le nourir.\n");

	fprintf(stderr,"\nRègle 6: Fin de jeu\n");
	fprintf(stderr,"Le jeu se termine lorsque un joueur n'a plus de graines dans son camp et que l'adversaire ne peut pas le nourir.\n");
}
/**
*\fn void sauvegarder(FILE*fichier)
*\brief Permet de sauvegarder une partie en cours, les scores et le pseudo du JOUEUR2 de la partie.
*\param fichier Le fichier de sauvegarde
*/
void sauvegarder(FILE * fichier) {
	
	int i, j;	
	fprintf(fichier, "%s\n", pseudo2);
	fprintf(fichier, "%i\n", scorej1);
	fprintf(fichier, "%i\n", scorej2);
	for(i = 0; i<L; i++) {
		for(j=0; j<C; j++) {
			fprintf(fichier, "%i\n", awale[i][j]);
		}
	}
	 
}

/**
*\fn int classer_records(FILE*fichier, t_joueur * record_score, int * nb_score)
*\brief Permet d'afficher les 10 meilleures scores enregistrés du jeu
*\param fichier Le fichier de sauvegarde à recuperer
*\param record_score Pointeur sur une structure de type t_joueur
*\param nb_score Pointeur sur le nombre de score
*/
void classer_records(FILE * fichier, t_joueur * record_score, int * nb_score) {
	
	int i, j;
	int bien_place;
	t_joueur tmp;
	
	
	/*Verifier si aucun score est enregistré*/
	fscanf(fichier, "%s", record_score[*nb_score].pseudo);
	if(feof(fichier)) {
		printf("Aucun score a été enregistré\n");
	}
	else {
		fscanf(fichier, "%i", &(record_score[*nb_score].score));
		(*nb_score)++;
		/*Stocker les scores du fichiers dans un tableau*/
		while(!feof(fichier)) {
			fscanf(fichier, "%s", record_score[*nb_score].pseudo);
			fscanf(fichier, "%i", &(record_score[*nb_score].score));
			(*nb_score)++;

		}
		(*nb_score)--;

		/*Trier le tableau des scores dans l'ordre decroissant*/
		if((*nb_score) > 1){
			for(i =0; i<(*nb_score); i++) {
				j=i;
				bien_place = faux;
				while(j>0 && !bien_place) {
					bien_place = (record_score[j].score <= record_score[j-1].score);
					if (!bien_place) {
						tmp = record_score[j-1];
						record_score[j-1] = record_score[j];
						record_score[j] = tmp;
						j--;	
					}
				}
			}	
		}
		
		/*Afficher les scores dans l'ordre*/
		printf("\nLes 10 meilleures scores\n");
		for(i = 0; i<(*nb_score) && i<10; i++) {
			printf("%s\t", record_score[i].pseudo);
			printf("%i\n", record_score[i].score);
		}
	}
}

/**
*\fn int charger_partie(FILE*fichier)
*\brief Permet de charger une partie sauvegarder
*\param fichier Le fichier de sauvegarde à recuperer
*\return 0 si aucune partie est sauvegardée, 1 si oui
*/
int charger_partie(FILE * fichier) {
	
	int i, j;
	int valeur;
	if(feof(fichier)) {
		printf("Aucune partie est sauvegardée\n");
		return 0;
	}
	else {
		fscanf(fichier, "%s", pseudo2);
		fscanf(fichier, "%i", &scorej1);
		fscanf(fichier, "%i", &scorej2);
		fscanf(fichier, "%i", &valeur);
		for(i = 0; i<L; i++) {
			for(j=0; j<C; j++) {
				awale[i][j] = valeur;
				fscanf(fichier, "%i", &valeur);
			}
		}
	}
	return 1;
}
/**
*\fn void jouer_a_deux(FILE * fichier, FILE * fic_records)
*\brief Permet de joueur une partie entre deux joueurs
*\param fichier Le fichier de sauvegarde
*\param fic_records Le fichier contenant les records
*/
 void jouer_a_deux(FILE * fichier, FILE * fic_records) {
	
	int nb_graine;
	int case_aide;
	int coord_x;
	char reponse;
	char rep_aide;
	int sc_tmp_j1 = 0;
	int sc_tmp_j2 = 0;
	int nb_jocker_j1 = 3;
	int nb_jocker_j2 = 3;
	
		while(!partie_finie(awale, scorej1, scorej2) && reponse != 'q'){
				
			/*Tour du joueur 1*/
			if(aide(JOUEUR1, awale, &case_aide) && nb_jocker_j1 <= 3 && nb_jocker_j1 > 0) {
				printf("\n%s, voulez vous une aide, y pour Oui, n pour Non ?\n", pseudo1);
				if(nb_jocker_j1 == 1)
						printf("Attention c'est votre dernier jocker !!\n");
				scanf("%*c%c", &rep_aide);
				if(rep_aide == 'y') {
					printf("Bougez la case %i !", case_aide);
					nb_jocker_j1--;							
				}
			}
				
			if(jeu_possible(awale, JOUEUR1) == 0){ /*On verifie si le jeu n'est pas possible*/
				victoire(fic_records);
				break;

			}
			
			/*Permet d'initiliser nb_tours à 0 si les tours non gagnants ne sont pas successives*/
			if(!gain_difficile(awale, &nb_tours))
				nb_tours = 0;
					
			/*Si les coups gagnants sont difficiles à jouer incrementer le nombre de tour 
			* puis comparer les deux scores */
			if(gain_difficile(awale, &nb_tours)) {
				if(sc_tmp_j1 == 0)
					sc_tmp_j1 = scorej1;
				if(sc_tmp_j2 == 0)
					sc_tmp_j1 = scorej1;
				if(nb_tours == 3) {
					if(sc_tmp_j1 == scorej1 && sc_tmp_j2 == scorej2)
						printf("Il devient difficile de continuer, et de trouver des coups gagnants\n");
						printf("Que la,partie s'arrête\n");
						scorej1 = scorej1 + graines_restantes(awale, JOUEUR1);
						scorej2 = scorej2 + graines_restantes(awale, JOUEUR2);
						victoire(fic_records);
						break;

				}
			}
			
			printf("\n%s : Saisissez votre point de jeu: \n", pseudo1);
			scanf("%*c%i", &coord_x);
			
			/*Si le joueur est affamé est qu'on peut le nourir, on verifie si le coord_x saisie permet de le nourir 
			 * et on repete la saisie tant que la bonne case n'est pas saisie
			 */
			if(jeu_possible(awale, JOUEUR1) && plateau_vide(awale, JOUEUR2) && !coup_possible(coord_x-1, awale, JOUEUR1)) {
				do{
					printf("\n%s : Attention vous devez nourir votre adversaire !!\n", pseudo1); 
					printf("\n%s : Saisissez votre point de jeu: \n", pseudo1);
					scanf("%*c%i", &coord_x);
					
				}while(!coup_possible(coord_x-1, awale, JOUEUR1));
			}
			
			do {
				if(coord_x > C || coord_x < 0){ /*Si les coordonnées sont mauvaises*/
				printf("\nVotre choix doit etre compris entre 1 et 6\n");
				printf("\n%s : Saisissez votre point de jeu : \n", pseudo1);
				scanf("%*c%i", &coord_x);
				nb_graine = awale[JOUEUR1][coord_x-1];
				}
				else {
					nb_graine = awale[JOUEUR1][coord_x-1];
					if(nb_graine == 0){ /*si la case est vide*/	
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

			/*Tour du joueur 2*/

			if(aide(JOUEUR2, awale, &case_aide) && nb_jocker_j2 <= 3  && nb_jocker_j2 > 0) {
				printf("\n%s, voulez vous une aide, y pour Oui, n pour Non ?\n", pseudo2);
				if(nb_jocker_j2 == 1)
						printf("Attention c'est votre dernier jocker !!\n");
				scanf("%*c%c", &rep_aide);
					if(rep_aide == 'y') {
						printf("Bougez la case %i !", case_aide);
						nb_jocker_j2--;

					}
			}
			
			if(jeu_possible(awale, JOUEUR2) == 0){ /*On verifie si le jeu n'est pas possible*/
				victoire(fic_records);
				break;
			}	
			printf("\n%s : Saisissez votre point de jeu : \n", pseudo2);
			scanf("%i", &coord_x);
			
			/*Si le joueur est affamé est qu'on peut le nourir, on verifie si le coord_x saisie permet de le nourir 
			 * et on repete la saisie tant que la bonne case n'est pas saisie
			 */
			if(jeu_possible(awale, JOUEUR2) && plateau_vide(awale, JOUEUR1) && !coup_possible(coord_x-1, awale, JOUEUR2)) {	
				do{
					printf("\n%s : Attention vous devez nourir votre adversaire !!\n", pseudo2); 
					printf("\n%s : Saisissez votre point de jeu: \n", pseudo2);
					scanf("%*c%i", &coord_x);
					
				}while(!coup_possible(coord_x-1, awale, JOUEUR2));
			}
			
			do {
				if(coord_x > C || coord_x < 0){ /*Si les coordonnées sont mauvaises*/
				printf("\nVotre choix doit etre compris entre 1 et 6\n");
				printf("\n%s : Saisissez votre point de jeu : \n", pseudo2);
				scanf("%*c%i", &coord_x);
				nb_graine = awale[JOUEUR2][coord_x-1];
				}
				else {
					nb_graine = awale[JOUEUR2][coord_x-1];
					if(nb_graine == 0){ /*Si la case est vide*/		
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
		/*Afficher le gagnant de la partie si la partie est finie*/
		if(partie_finie(awale, scorej1, scorej2)) {
			victoire(fic_records);
		}
		/*Demander si la partie devrait etre sauvegarder*/
		if(reponse == 'q') {
			printf("\nVoulez vous sauvegarder la partie y pour Oui et n pour Non\n");
			scanf("%*c%c", &reponse);                                                                                   
			if(reponse == 'y') {
				sauvegarder(fichier);
			}
		}
			
}			
				
				
/**
*\fn void jouer_avec_ordinateur(FILE * fichier, FILE * fic_records)
*\brief Permet de joueur une partie avec l'ordinateur
*\param fichier Le fichier de sauvegarde
*\param fic_records Le fichier contenant les records
*/

void jouer_avec_ordinateur(FILE * fichier, FILE * fic_records) {
	
	int nb_graine, coord_x;
	int case_aide;
	int case_ordi;
	char reponse;
	char rep_aide;
	int nb_jocker_j1 = 3;
	int sc_tmp_j1 = 0;
	int sc_tmp_j2 = 0;
		
		while(!partie_finie(awale, scorej1, scorej2) && reponse != 'q'){
					
			if(aide(JOUEUR1, awale, &case_aide) && nb_jocker_j1 <= 3  && nb_jocker_j1 > 0) {
				printf("\n%s, voulez vous une aide, y pour Oui, n pour Non ?\n", pseudo1);
				if(nb_jocker_j1 == 1)
					printf("Attention c'est votre dernier jocker !!\n");
				scanf("%*c%c", &rep_aide);
				if(rep_aide == 'y') {
					printf("Bougez la case %i !", case_aide);
					nb_jocker_j1--;
					}
				}
			if(jeu_possible(awale, JOUEUR1) == 0){ /*On verifie si le jeu n'est pas possible*/
					victoire(fic_records);
					break;
			}
				
			/*Permet d'initiliser nb_tours  à 0 si les tours non gagnants ne sont pas successives*/
			if(!gain_difficile(awale, &nb_tours))
					nb_tours = 0;	
					
			/*Si les coups gagnants sont difficiles à jouer incrementer le nombre de coups 
			 * puis comparer les deux scores */
			if(gain_difficile(awale, &nb_tours)) {
					if(sc_tmp_j1 == 0)
						sc_tmp_j1 = scorej1;
					if(sc_tmp_j2 == 0)
						sc_tmp_j1 = scorej1;
					if(nb_tours == 3) {
						if(sc_tmp_j1 == scorej1 && sc_tmp_j2 == scorej2)
							printf("\nIl devient difficile de continuer, et de trouver des coups gagnants\n");
							printf("Que la partie s'arrête\n");
							scorej1 = scorej1 + graines_restantes(awale, JOUEUR1);
							scorej2 = scorej2 + graines_restantes(awale, ORDINATEUR);
							victoire(fic_records);
							break;
				}
			}
			
			printf("\n%s : Saisissez votre point de jeu: \n", pseudo1);
			scanf("%i", &coord_x);
			
			/*Si le joueur est affamé est qu'on peut le nourir, on verifie si le coord_x saisie permet de le nourir 
			* et on repete la saisie tant que la bonne case n'est pas saisie
			*/
			if(jeu_possible(awale, JOUEUR1) && plateau_vide(awale, JOUEUR2) && !coup_possible(coord_x-1, awale, JOUEUR1)) {
					do{
						printf("\n%s : Attention vous devez nourir votre adversaire !!\n", pseudo1); 
						printf("\n%s : Saisissez votre point de jeu: \n", pseudo1);
						scanf("%*c%i", &coord_x);
						
					}while(!coup_possible(coord_x-1, awale, JOUEUR1));
				}
			
				
			do {
					
					if(coord_x > C || coord_x < 0){ /*Si les coordonnées sont mauvaises*/
					printf("\nVotre choix doit etre compris entre 1 et 6\n");
					printf("\n%s : Saisissez votre point de jeu : \n", pseudo1);
					scanf("%*c%i", &coord_x);
					nb_graine = awale[JOUEUR1][coord_x-1];
					}
					
					else {
						nb_graine = awale[JOUEUR1][coord_x-1];
						if(nb_graine == 0){ /*Si la case est vide*/		
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
			if(jeu_possible(awale, ORDINATEUR) == 0){ /*On verifie si le jeu est possible*/
					victoire(fic_records);
					break;

				}	
			/*Recuperer la case que l'ordinateur va joué*/				
			case_ordi = jeu_ordi(awale);
			printf("---> ORDINATEUR va jouer %d\n", case_ordi+1);
			nb_graine = awale[ORDINATEUR][case_ordi];
			manger_graines(nb_graine, awale, ORDINATEUR, case_ordi, &scorej2);
			affiche_matrice(awale);
					
			afficher_score(scorej2, pseudo2);
							
			printf("Voulez vous quittez le jeu q pour quitter, s pour continuer\n");
			scanf("%*c%c", &reponse);
				
		}
		/*Afficher le gagnant de la partie si la partie est finie*/
		if(partie_finie(awale, scorej1, scorej2))
			victoire(fic_records);
		/*Demander si la partie devrait etre sauvegarder*/
		if(reponse == 'q') {
			printf("Voulez vous sauvegarder la partie y pour Oui et n pour Non\n");
			scanf("%*c%c", &reponse);                                                                                   
			if(reponse == 'y') {	
				sauvegarder(fichier);
			}
		}
}

	

/**
*\fn void jouer(FILE * fichier, FILE * fic_records)
*\brief Permet de joueur
*\param fichier Le fichier de sauvegarde
*\param fic_records Le fichier contenant les records
*/
void jouer(FILE * fichier, FILE * fic_records){
	
	if(strcmp(pseudo2, "Ordinateur") == 0) {
		printf("Joueur 1\nVeuillez saisir votre pseudonyme ?\n");
		scanf("%s", pseudo1);
		printf("\nQue la partie commence !\n");
		affiche_matrice(awale);		
		jouer_avec_ordinateur(fichier, fic_records);
	}
	else {
		printf("Joueur 1\nVeuillez saisir votre pseudonyme ?\n");
		scanf("%s", pseudo1);
		printf("Joueur 2\nVeuillez saisir votre pseudonyme ?\n");
		scanf("%s", pseudo2);
		printf("\nQue la partie commence !\n");
		affiche_matrice(awale);		
		jouer_a_deux(fichier, fic_records);
	}
}

       


