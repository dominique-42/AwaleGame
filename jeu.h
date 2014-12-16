#ifndef __JEU_H__
#define __JEU_H__

#define L 2
#define C 6
#define N 12

#define JOUEUR1 0
#define JOUEUR2 1
#define ORDINATEUR 1


void sauvegarder(FILE * fichier);
void charger_partie(FILE * fichier);
void jouer_a_deux(int joueur1, int joueur2, FILE * fichier);
void jouer_avec_ordinateur(int joueur1, int joueur2, FILE * fichier);
void jouer();


#endif
