void init_matrice(int matrice[L][C]);
void affiche_matrice(int matrice[L][C]) ;
void dpl_arriere(int*x, int*y);
void dpl_avant(int *x, int *y);
void manger_graines(int nb_graines, int matrice[L][C], int joueur, int x, int *score);
int jeu_ordi(int ordinateur, int matrice[L][C]);
int aide(int joueur, int matrice[L][C], int * case_aide);
int nourir(int matrice[L][C], int joueur);
int gagne(int*score1, int *score2);
int partie_pas_finie(int matrice[L][C], int joueur1, int joueur2, int *score1, int *score2 ) ;
void afficher_score(int score, char joueur[20]);

