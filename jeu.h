#ifndef __JEU_H__
#define __JEU_H__

#define L 2
#define C 6
#define N 12

#define JOUEUR1 1
#define JOUEUR2 0
#define ORDINATEUR 0

char pseudo1[20];
char pseudo2[20];
int awale[L][C];
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
void incrementer(int * nb_score);



#endif
