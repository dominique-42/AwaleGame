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

void sauvegarder(FILE * fichier);
void charger_partie(FILE * fichier);
void jouer_a_deux(FILE * fichier);
void jouer_avec_ordinateur(FILE * fichier);
void jouer(FILE * fichier);


#endif
