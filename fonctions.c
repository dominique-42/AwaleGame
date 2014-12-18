#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<assert.h>

#include "fonctions.h"

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
	int clan;
	int nb_gr_fin;
	t_coord graine_dbt;
	graine_dbt.joueur = joueur;
	graine_dbt.x = x;
	clan = joueur;
		
	for(i = 0; i<nb_graines;i++) {
		dpl_avant(&x,&joueur);
		
		matrice[joueur][x] = matrice[joueur][x]+1;
		
		if(i == nb_graines-1) {
		nb_gr_fin = matrice[joueur][x];
		}
	}
	
	matrice[graine_dbt.joueur][graine_dbt.x] = 0;

	i = nb_graines;
	if((matrice[joueur][x] == 2 || matrice[joueur][x] == 3 ) && clan != joueur) {
		*score = *score+matrice[joueur][x];
		matrice[joueur][x] = 0;
		while( i>0 && nb_gr_fin<=3 && nb_gr_fin > 1 && clan != joueur) {	//initialise le score selon le nb de graines mangées
			(*score) = (*score)+matrice[joueur][x];
			matrice[joueur][x] = 0;
			dpl_arriere(&x, &joueur);
			nb_gr_fin = matrice[joueur][x];
			i--;
		}	
	}

} 

 
/**
*\fn int jeu_ordi(int matrice[L][C])
*\brief  La case que l'ordinateur devrait bouger
*\param ordinateur , matrice represente le plateau de jeu
*\return la case à déplacer
**/

int jeu_ordi(int matrice[L][C]){

	int score[C];
	int j, k;
	int case_ordi;
	int max;
	int mat_tmp[L][C];
	int case_mat;
	
	//init scores pour chaque case
    for(j=0; j<C; j++)
		score[j] = 0;

	// on essaye de jouer dans chaque case, et on regarde le score de chaque case
	for(case_mat = 0; case_mat<C ;case_mat++) {
		

		//Actualiser la matrice aide avec la disposition du plateau
		for(k = 0; k<L; k++) {		
			for(j=0; j<C; j++) {
				mat_tmp[k][j] = matrice[k][j];
			}
		}
				
		if(mat_tmp[ORDINATEUR][case_mat] != 0){ //s'il y a au mons 1 graine dans la case, on essaye de jouer à partir de cette case
			manger_graines(mat_tmp[ORDINATEUR][case_mat], mat_tmp ,ORDINATEUR, case_mat, &score[case_mat]);
		} 
		
		else {
			//fprintf(stderr, "ORDI : case vide !!\n");
			score[case_mat] = -1; //on ne doit pas choisir cette case
		}
	}
	
	//Actualiser la matrice aide avec la disposition du plateau
		for(k = 0; k<L; k++) {		
			for(j=0; j<C; j++) {
				mat_tmp[k][j] = matrice[k][j];
			}
		}
		
	//détecter la case qui permet de manger le plus de graines
		max = score[0];
		case_ordi = 0;
		for(j=1; j<C; j++) {
			
			if(max < score[j]){
				max = score[j];
				case_ordi = j;
			}
		
		}
	/*si l'adversaire est affamé choisir une case qui le nourri*/
	if(plateau_vide(matrice, JOUEUR1)) {	
		for(j=0; j<C; j++) {
			if(nourir_case(mat_tmp, ORDINATEUR, j)){
				case_ordi = j;
			}
		}
	}
	
	fprintf(stderr, "---> ORDI va jouer %d\n", case_ordi+1);
	return case_ordi;
}
	
    
/**
*\fn int aide(int joueur, int matrice[L][C], int * case_aide)
*\brief  quelle case bouger pour avoir plus de graines 
*\param score virtuel , parametre qui permet de calculer le nombre de graines avant de jouer pour avoir le maximum de graines 
*\return 0 si il n'ya aucune possibilité de ramasser des graines, et retourne la valeur de la case en pointeur
**/

int aide(int joueur, int matrice[L][C], int * case_aide){

	int score[C];
	int j, k;
	int max;
	int mat_tmp[L][C];
	int case_mat;
	int detecteur_aide = 0;
	
	//init scores pour chaque case
    for(j=0; j<C; j++)
		score[j] = 0;

	// on essaye de jouer dans chaque case, et on regarde le score de chaque case
	for(case_mat = 0; case_mat<C ;case_mat++) {
		

		//Actualiser la matrice aide avec la disposition du plateau
		for(k = 0; k<L; k++) {		
			for(j=0; j<C; j++) {
				mat_tmp[k][j] = matrice[k][j];
			}
		}
				
		if(mat_tmp[joueur][case_mat] != 0){ //s'il y a au mons 1 graine dans la case, on essaye de jouer à partir de cette case
			manger_graines(mat_tmp[joueur][case_mat], mat_tmp ,joueur, case_mat, &score[case_mat]);
			if(score[case_mat] > 0) {
				detecteur_aide++; //incrementer le compteur qui permet de signaler si l'aide est necessaire ou pas
			}
		} 
		else {
			score[case_mat] = -1; //on ne doit pas choisir cette case
		}
	}
	
	
	//détecter la case qui permet de manger le plus de graines
		max = score[0];
		*case_aide = 0;
		for(j=1; j<C; j++) {
			
			if(max < score[j]){
				max = score[j];
				*case_aide = j; //on actualise la variable case_aide
			}
		
		}
	if(detecteur_aide > 0) { //si l'aide est necessaire alors on envoie vraie 
		*case_aide = *case_aide + 1; // on adapte l'indice de la case à l'affichage du plateau qui est de 1 à 6
		return 1;
	}
	else if(detecteur_aide == 0){// si l'aide n'est pas necessaire on envoie 0
		return 0;
	}
	return 0;
}

/**
*\fn int nourir(int matrice[L][C], int joueur)
*\brief est-ce que le joueur j peut nourir son adversaie qui est affame ?
*\param matrice[L][C], joueur
*\return 0 si on ne peut pas le nourir, 1 si oui
**/
int nourir(int matrice[L][C], int joueur) {
	
	//int nb_depl; // nbr de deplacement correspondant a chaque case pour pouvoir nourir l'adversaire
	int x;			//coordonnée de la case du plateau du joueur

	if(joueur == JOUEUR2 || joueur == ORDINATEUR) {
		//nb_depl = C;
		for(x = C-1; x>=0; x--) {
			if(matrice[joueur][x] > x){ //dans la case x, il faut au moins x+1 graines (ex: case 0 -> 1 graine minimum, case 5 -> 6 graines ..)
				return 1;	// retourne 1 si nourir l'adversaire est possible
			}
			//nb_depl--;
		}
	}
	else if(joueur == JOUEUR1) {
		//nb_depl = C;
		for(x = 0; x<C; x++ ){
			if(matrice[joueur][x] >= C-x){
				return 1;	//retourne 1 si nourir l'adversaire est possible
			}
			//nb_depl--;
		}
	}
	return 0;	
}

/**
*\fn int nourir_case(int matrice[L][C], int joueur, int coord_x)
*\brief est-ce que le joueur j peut nourir son adversaie qui est affame en jouant la case coord_x?
*\param matrice[L][C], joueur, coord_x
*\return 0 si on ne peut pas le nourir, 1 si oui
**/
int nourir_case(int matrice[L][C], int joueur, int coord_x) {
	
	if(joueur == JOUEUR2 || joueur == ORDINATEUR) {
		if(matrice[joueur][coord_x] > coord_x){ //dans la case x, il faut au moins x+1 graines (ex: case 0 -> 1 graine minimum, case 5 -> 6 graines ..)
			return 1;	// retourne 1 si nourir l'adversaire est possible
		}
	}
	else if(joueur == JOUEUR1) {
		if(matrice[joueur][coord_x] >= C-coord_x){
			return 1;	//retourne 1 si nourir l'adversaire est possible
		}
	}
	return 0;	
}


   
/**
*\fn int plateau_vide(int matrice[L][C], int joueur)
*\brief est-ce que le plateau du joueur est vide?
*\param matrice[L][C], joueur
*\return
**/  
int plateau_vide(int matrice[L][C], int joueur) {
	int cpt = 0;
	int i;
	for(i = 0; i<C; i++) {
		cpt = cpt + matrice[joueur][i];
	}
	if(cpt == 0) { //si le plateau est vide on renvoie 1
		return 1;
	}
	//else
	
	return 0; //si le plateau du joueur n'est pas vide on renvoie 0


}
   
 
        
/**
*\fn int gagner(int*score,int*score2)
*\brief verifie si le score des joueurs "joueur1" ou "joueur2" a depassé 25 ou pas
*\param score (score du joueurà, joueur
*\return 0 si score des deux joueurs <25, 1 sinon
*/
 int gagne(int *score1, int *score2) {
	
	if((*score1) >= 25 || (*score2) >= 25) {
		return 1;
		}
	else 
		return 0;
 }
 
 /**
*\fn partie_finie(int matrice[L][C], int joueur1, int joueur2, int score1, int score2 )
*\brief Permet de verifier si une partie est terminée ou pas en verifiant si l'on peut nourir l'adversaire et si l'un des score est superieure ou egale à 25
*\param matrice[L][C], joueur1, joueur2, score1, score2
*\return 1 si partie finie, 0 sinon
*/
int partie_pas_finie(int matrice[L][C], int *score1, int *score2 ) {
	if(nourir(matrice, JOUEUR1) == 1 || nourir(matrice, JOUEUR2) == 1) {
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






