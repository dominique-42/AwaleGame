/**
 * \file fonctions.c
 * \brief Fichier contenant les fonctions necessaire à la construction du jeu.
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
/**
 * \struct t_coord 
 * \brief  Structure definissant les coordonnées du plateau  
 */
typedef struct {int ligne; int x; }t_coord;

/**
*\fn void init_matrice(int matrice[L][C])
*\brief Permet d'initialiser la matrice avec 4 graines dans chaque case
*\param matrice Matrice representant le plateau du jeu
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
*\fn void affiche_matrice(int matrice[L][C])
*\brief Permet d'afficher la matrice representant le plateau du jeu
*\param matrice Matrice representant le plateau du jeu
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
*\fn dpl_arriere(int*x, int*y)
*\brief Permet de se deplacer sur la grille en arriere 
*\param x Pointeur sur le coordonnée x
*\param y Pointeur sur le coordonnée y
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
*\fn void dpl_avant(int *x, int *y) 
*\brief Permet de se deplacer dans la grille en avant
*\param x Pointeur sur le coordonnée x
*\param y Pointeur sur le coordonnée y
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
*\fn void manger_graines(int nb_graines, int matrice[L][C], int joueur, int x, int *score)
*\brief Permet jouer en se deplacant sur le plateau et en mangeant les graines qui se presentent et incremente le score du joueur
*\param nb_graines Nombre de graines dans la case
*\param matrice Plateau du jeu
*\param joueur Coordonnée y de la case 
*\param score Pointeur sur le coordonnée x de la case 
*/
void manger_graines(int nb_graines, int matrice[L][C], int joueur, int x, int *score) {
	
	int i;
	int clan;
	int nb_gr_fin;
	t_coord graine_dbt;
	graine_dbt.ligne = joueur;
	graine_dbt.x = x;
	clan = joueur;
	
	/*Distribution des graines */
	for(i = 0; i<nb_graines;i++) {
	
		dpl_avant(&x,&joueur);
		if(graine_dbt.ligne == joueur && graine_dbt.x == x)
			dpl_avant(&x,&joueur);
	
		matrice[joueur][x] = matrice[joueur][x]+1;
			
		if(i == nb_graines-1) {
			nb_gr_fin = matrice[joueur][x];
		}
	}
	matrice[graine_dbt.ligne][graine_dbt.x] = 0;
	
	/*Ramassage des graines lors d'un coup gagnant, si ce coup n'affame pas l'adversaire*/
	if(!non_affame(nb_graines, matrice, clan, joueur, x)){
		i = nb_graines;
		if((matrice[joueur][x] == 2 || matrice[joueur][x] == 3 ) && clan != joueur) {
			(*score) = (*score)+matrice[joueur][x];
			matrice[joueur][x] = 0;
			while( i>0 && nb_gr_fin<=3 && nb_gr_fin > 1 && clan != joueur) {	/*Initialise le score selon le nb de graines mangées*/
				(*score) = (*score)+matrice[joueur][x];
				matrice[joueur][x] = 0;
				dpl_arriere(&x, &joueur);
				nb_gr_fin = matrice[joueur][x];
				i--;
			}	
		}
	} 
}

/**
*\fn int non_affame(int nb_graines, int matrice[L][C], int clan, int joueur, int x) 
*\brief Permet de connaitre si un joueur sera affamé si l'adversaire joue un coup permettant de ramasser des graines
*\param nb_graines Nombre de graine dans la case à deplacer
*\param matrice[L][C] Plateau du jeu
*\param clan Ligne du joueur
*\param joueur Representant la ligne du joueur
*\param x Corrdonnée x de la case
*\return 1 si l'adversaire est affame apres le coup, 0 sinon
*/

int non_affame(int nb_graines, int matrice[L][C], int clan, int joueur, int x) {
	
	int mat_tmp[L][C];
	int i, j;
	int nb_gr_fin;
	
	/*Actualiser la matrice temporaire avec la disposition du plateau*/
	for(i = 0; i<L; i++) {		
		for(j=0; j<C; j++) {
			mat_tmp[i][j] = matrice[i][j];
		}
	}
	/*Jouer le coup gagnant si il existe*/
	i = nb_graines;
	if((mat_tmp[joueur][x] == 2 || mat_tmp[joueur][x] == 3) && clan != joueur) {
		nb_gr_fin = mat_tmp[joueur][x];
		mat_tmp[joueur][x] = 0;
		while( i>0 && nb_gr_fin<=3 && nb_gr_fin > 1 && clan != joueur) {	/*initialise le score selon le nb de graines mangées*/
			mat_tmp[joueur][x] = 0;
			dpl_arriere(&x, &joueur);
			nb_gr_fin = mat_tmp[joueur][x];
			i--;
		}	
	}	
	/*Verifier si le plateau de l'adversaire devient vide après ce jeu*/
	if(clan == JOUEUR1){
		if(plateau_vide(mat_tmp, JOUEUR2))
			return 1;
	}
	else if(clan == JOUEUR2){
			if(plateau_vide(mat_tmp, JOUEUR1))
				return 1;
	}
	return 0;
			
}

 
/**
*\fn int jeu_ordi(int matrice[L][C])
*\brief  Permet de simuler le jeu de l'ordinateur
*\param matrice Representant le plateau de jeu
*\return La case à déplacer
**/

int jeu_ordi(int matrice[L][C]){

	int score[C];
	int j, k;
	int case_ordi;
	int max;
	int mat_tmp[L][C];
	int case_mat;
	
	/*Init scores pour chaque case*/
    for(j=0; j<C; j++)
		score[j] = 0;

	/*On essaye de jouer dans chaque case, et on regarde le score de chaque case*/
	for(case_mat = 0; case_mat<C ;case_mat++) {
		

		/*Actualiser la matrice aide avec la disposition du plateau*/
		for(k = 0; k<L; k++) {		
			for(j=0; j<C; j++) {
				mat_tmp[k][j] = matrice[k][j];
			}
		}
				
		if(mat_tmp[ORDINATEUR][case_mat] != 0){ /*S'il y a au mons 1 graine dans la case, on essaye de jouer à partir de cette case*/
			manger_graines(mat_tmp[ORDINATEUR][case_mat], mat_tmp ,ORDINATEUR, case_mat, &score[case_mat]);
		} 
		
		else {
			score[case_mat] = -1; /*On ne doit pas choisir cette case*/
		}
	}
	
	/*Actualiser la matrice aide avec la disposition du plateau*/
		for(k = 0; k<L; k++) {		
			for(j=0; j<C; j++) {
				mat_tmp[k][j] = matrice[k][j];
			}
		}
		
	/*Détecter la case qui permet de manger le plus de graines*/
		max = score[0];
		case_ordi = 0;
		for(j=1; j<C; j++) {
			
			if(max < score[j]){
				max = score[j];
				case_ordi = j;
			}
		
		}
	/*Si l'adversaire est affamé choisir une case qui le nourri*/
	if(plateau_vide(matrice, JOUEUR1)) {	
		for(j=0; j<C; j++) {
			if(nourir_case(mat_tmp, ORDINATEUR, j)){
				case_ordi = j;
			}
		}
	}
	return case_ordi;
}
	
    
/**
*\fn int aide(int joueur, int matrice[L][C], int * case_aide)
*\brief  Quelle case bouger pour avoir le plus de graines à un coup à jouer?
*\param joueur Joueur pour lequel l'aide est recherchee
*\param matrice Plateau du jeu
*\param case_aide Pointeur sur la case à bouger pour obtenir l'aide
*\return 0 si il n'ya aucune possibilité de ramasser des graines, 1 si oui
**/

int aide(int joueur, int matrice[L][C], int * case_aide){

	int score[C];
	int j, k;
	int max;
	int mat_tmp[L][C];
	int case_mat;
	int detecteur_aide = 0;
	
	/*Init scores pour chaque case*/
    for(j=0; j<C; j++)
		score[j] = 0;

	/*On essaye de jouer dans chaque case, et on regarde le score de chaque case*/
	for(case_mat = 0; case_mat<C ;case_mat++) {
		/*Actualiser la matrice aide avec la disposition du plateau*/
		for(k = 0; k<L; k++) {		
			for(j=0; j<C; j++) {
				mat_tmp[k][j] = matrice[k][j];
			}
		}
				
		if(mat_tmp[joueur][case_mat] != 0){ /*S'il y a au mons 1 graine dans la case, on essaye de jouer à partir de cette case*/
			manger_graines(mat_tmp[joueur][case_mat], mat_tmp ,joueur, case_mat, &score[case_mat]);
			if(score[case_mat] > 0) {
				detecteur_aide++; /*Incrementer le compteur qui permet de signaler si l'aide est necessaire ou pas*/
			}
		} 
		else {
			score[case_mat] = -1; /*On ne doit pas choisir cette case*/
		}
	}
	
	
	/*Détecter la case qui permet de manger le plus de graines*/
		max = score[0];
		*case_aide = 0;
		for(j=1; j<C; j++) {
			
			if(max < score[j]){
				max = score[j];
				*case_aide = j; /*On actualise la variable case_aide*/
			}
		
		}
	if(detecteur_aide > 0) { /*Si l'aide est necessaire alors on envoie vraie*/ 
		*case_aide = *case_aide + 1; /*On adapte l'indice de la case à l'affichage du plateau qui est de 1 à 6*/
		return 1;
	}
	else if(detecteur_aide == 0){/*Si l'aide n'est pas necessaire on envoie 0*/
		return 0;
	}
	return 0;
}

/**
*\fn int nourir(int matrice[L][C], int joueur)
*\brief Est-ce que le joueur j peut nourir son adversaie qui est affame ?
*\param matrice Plateau du jeu
*\param joueur Joueur dont la capacité de nourir est testé
*\return 0 si on ne peut pas le nourir, 1 si oui
**/
int nourir(int matrice[L][C], int joueur) {
	
	int x;			/*Coordonnée de la case du plateau du joueur*/

	if(joueur == JOUEUR2 || joueur == ORDINATEUR) {
		for(x = C-1; x>=0; x--) {
			if(matrice[joueur][x] > x) /*Dans la case x, pour le JOUEUR2, il faut au moins x+1 graines (ex: case 0 -> 1 graine minimum, case 5 -> 6 graines)*/
				return 1;	/*Retourne 1 si nourir l'adversaire est possible*/
		}
	}
	else if(joueur == JOUEUR1) {
		for(x = 0; x<C; x++ ){
			if(matrice[joueur][x] >= C-x) /*Dans la case x, pour le JOUEUR1, il faut au moins C-x graines (ex: case 0 -> 6 graine minimum, case 5 -> 1 graines)*/
				return 1;	/*Retourne 1 si nourir l'adversaire est possible*/
		}
	}
	return 0;	
}

/**
*\fn int nourir_case(int matrice[L][C], int joueur, int coord_x)
*\brief Est-ce que le joueur "joueur" peut nourir son adversaie qui est affame en jouant la case coord_x?
*\param matrice Plateau de jeu 
*\param joueur Representant la ligne du joueur
*\param coord_x Coordonnée x de la case 
*\return 0 si on ne peut pas le nourir, 1 si oui
**/
int nourir_case(int matrice[L][C], int joueur, int coord_x) {
	
	if(joueur == JOUEUR2 || joueur == ORDINATEUR) {
		if(matrice[joueur][coord_x] > coord_x){ /*Dans la case x, il faut au moins x+1 graines (ex: case 0 -> 1 graine minimum, case 5 -> 6 graines)*/
			return 1;	
		}
	}
	else if(joueur == JOUEUR1) {
		if(matrice[joueur][coord_x] >= C-coord_x){ /*Dans la case x, il faut au moins C-x graines (ex: case 0 -> 6 graine minimum, case 5 -> 1 graines)*/
			return 1;	
		}
	}
	return 0;	
}


   
/**
*\fn int plateau_vide(int matrice[L][C], int joueur)
*\brief Est-ce que le plateau du joueur "joueur" est vide?
*\param matrice Plateau de jeu
*\param joueur Represente la ligne du joueur
*\return 1 si le platau est vide, 0 sinon
**/  
int plateau_vide(int matrice[L][C], int joueur) {
	int cpt = 0;
	int i;
	for(i = 0; i<C; i++) {
		cpt = cpt + matrice[joueur][i];
	}
	if(cpt == 0) { 
		return 1;
	}	
	return 0; 
}

/**
*\fn int graines_restantes(int matrice[L][C], int joueur)
*\brief Compter le nombre de graines dans le plateau de jeu pour chaque joueur
*\param matrice Plateau de jeu
*\param joueur Represente la ligne du joueur
*\return Le nombre de graine restantes dans la ligne du joueur
**/  
int graines_restantes(int matrice[L][C], int joueur) {
	
	int cpt = 0;
	int i;
	for(i = 0; i<C; i++) {
		cpt = cpt + matrice[joueur][i];
	}
	return cpt;
}

 /**
*\fn int partie_finie(int matrice[L][C], int score1, int score2 )
*\brief Permet de verifier si une partie est terminée ou pas en verifiant si l'un des score est superieure ou egale à 25
*\param matrice Plateau de jeu
*\param score1 Score du joueur 1
*\param score2 Score du joueur 2
*\return 1 si la partie est finie, 0 sinon
*/
int partie_finie(int matrice[L][C], int score1, int score2 ) {
	if(score1 >= 25 || score2>= 25) {
		return 1;
		}
	else 
		return 0;
}


/**
*\fn afficher_score(int score, char joueur[20])
*\brief Permet d'afficher le score du joueur en indiquant son pseudo
*\param score score du joueur
*\param joueur pseudo du joueur
*/
void afficher_score(int score, char joueur[20]) {
	printf("\nLe score du joueur %s est %i\n", joueur, score);
}






