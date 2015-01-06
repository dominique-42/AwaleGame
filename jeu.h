#ifndef __JEU_H__
#define __JEU_H__
/**
 * \file jeu.h
 * \brief Fichier contenant les en-tête des fonctions qui déroule le jeu.
 * \author Okrou Poda, Souleiman Iman Choukri		
 * \version 0.1
 * \date 19 novembre 2014
 *
 * Projet d'etude L2 SPI : Programmation du Jeu Awale
 *
 */

/**
*\def L 
*\brief Represente le nombre de ligne de la matrice*/
#define L 2

/**
*\def C 
*\brief Represente le nombre de colonne de la matrice*/
#define C 6

/**
*\def N 
*\brief Represente le nombre de case dans la matrice*/
#define N 12

/**
*\def JOUEUR1 
*\brief Represente le territoire du joueur1 sur le plateau*/
#define JOUEUR1 1

/**
*\def JOUEUR2 
*\brief Represente le territoire du joueur2 sur le plateau*/
#define JOUEUR2 0

/**
*\def ORDINATEUR 
*\brief Represente le territoire de l'ORDINATEUR sur le plateau*/
#define ORDINATEUR 0

char pseudo1[20]; /**<Pseudonyme du JOUEUR1*/
char pseudo2[20]; /**<Pseudonyme du JOUEUR2*/
int awale[L][C];  /**<Matrice représentant le plateau de jeu*/

/**
 * \struct t_joueur jeu.h
 * \brief  Structure definissant le score et le pseudonyme du joueur  
 */
typedef struct{char pseudo[20]; int score;} t_joueur;


void sauvegarder(FILE * fichier);
int charger_partie(FILE * fichier);
void jouer_a_deux(FILE * fichier, FILE * fic_records);
void jouer_avec_ordinateur(FILE * fichier, FILE * fic_records);
void jouer(FILE * fichier, FILE * fic_records);
void  victoire (FILE * fichier);
int coup_possible(int coord_x, int matrice [L][C], int joueur);
int jeu_possible(int matrice [L][C], int j);
int gain_difficile(int matrice[L][C], int * nb_coups);
void classer_records(FILE * fichier, t_joueur * record_score, int * nb_score);
void regles_jeu();
#endif
