int main(){
	

	
	int joueur2 = 0;
	int joueur1 = 1;
    int ordinateur = 0;
	int choix, choix2, nb_graine, coord_x;
	int case_aide;
	int case_ordi;
	
	char reponse;
	
	char rep_aide;
		

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
							
							printf("\n%s : Saisissez votre point de jeu : \n", player2);
							scanf("%*c%i", &coord_x);
							
							while(coord_x > C || coord_x < 0) {
							
								printf("\nVotre choix doit etre compris entre 1 et 6\n");
								printf("\n%s : Saisissez votre point de jeu: \n", player1);
								scanf("%i", &coord_x);
							
							}
							nb_graine = awale[joueur2][coord_x-1];
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
							sauvegarder(fic_save);
						}
						fclose(fic_save);
						
					break;
			
			
				/*Partie avec l'ordinateur*/
					case 2: 
						
						/*Tour du joueur 1*/
						printf("Joueur 1\nVeuillez saisir votre pseudonyme ?\n");
						scanf("%s", player1);

			            printf("\nQue la partie commence !\n");
						init_matrice(awale);
						affiche_matrice(awale);				
				

						while(partie_pas_finie(awale, joueur1, ordinateur, &scorej1, &scorej2 ) && reponse != 'q'){
					
		
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
							
							case_ordi = jeu_ordi(ordinateur, awale);
					
							nb_graine = awale[ordinateur][case_ordi];
							manger_graines(nb_graine, awale, ordinateur, case_ordi, &scorej2);
							affiche_matrice(awale);
					
							afficher_score(scorej2, player2);
							
							printf("Voulez vous abandonner ou quittez le jeu q pour quitter, s pour continuer\n");
							scanf("%*c%c", &reponse);
				
						}
						printf("Voulez vous sauvegarder la partie y pour Oui et n pour Non\n");
						scanf("%*c%c", &reponse);                                                                                   
						if(reponse == 'y') {
							sauvegarder(fic_save);
						}
						fclose(fic_save);
			
					break;

					default: printf("Erreur: votre choix doit etre compris entre 1 et 2\n"); break;
		
		
			}
			break;
			
		
		
		/*Reprendre la partie deja enregistré*/
		case 2: 
				
				charger_partie(fic_save);
				
				if(strcmp(player2, "Ordinateur") == 0) {
					
					/*Tour du joueur 1*/
						printf("Joueur 1\nVeuillez saisir votre pseudonyme ?\n");
						scanf("%s", player1);

			            printf("\nQue la partie commence !\n");
						init_matrice(awale);
						affiche_matrice(awale);				
				

						while(partie_pas_finie(awale, joueur1, ordinateur, &scorej1, &scorej2 ) && reponse != 'q'){
					
		
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
							
							case_ordi = jeu_ordi(ordinateur, awale);
					
							nb_graine = awale[ordinateur][case_ordi];
							manger_graines(nb_graine, awale, ordinateur, case_ordi, &scorej2);
							affiche_matrice(awale);
					
							afficher_score(scorej2, player2);
							
							printf("Voulez vous abandonner ou quittez le jeu q pour quitter, s pour continuer\n");
							scanf("%*c%c", &reponse);
				
						}
						printf("Voulez vous sauvegarder la partie y pour Oui et n pour Non\n");
						scanf("%*c%c", &reponse);                                                                                   
						if(reponse == 'y') {
							sauvegarder(fic_save);
						}
						fclose(fic_save);
			
				
				}
				else {
					
					printf("\nQue la partie commence !\n");
				
					affiche_matrice(awale);				
				

					while(partie_pas_finie(awale, joueur1, joueur2, &scorej1, &scorej2 ) && reponse != 'n'){
				
						/*Tour du joueur 1*/
						if(aide(joueur1, awale, &case_aide)) {
							printf("\nVoulez vous une aide, y pour Oui, n pour Non ?\n");
							scanf("%c", &rep_aide);
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
					
						printf("\n%s : Saisissez votre point de jeu : \n", player2);

						scanf("%*c%i", &coord_x);
					
						while(coord_x > C || coord_x < 0) {
							
							printf("\nVotre choix doit etre compris entre 1 et 6\n");
							printf("\n%s : Saisissez votre point de jeu: \n", player1);
							scanf("%i", &coord_x);
							
						}
						nb_graine = awale[joueur2][coord_x-1];
						manger_graines(nb_graine, awale, joueur2, coord_x-1, &scorej2);
						affiche_matrice(awale);
					
						afficher_score(scorej2, player2);

						printf("Voulez vous abandonner ou quittez le jeu q pour quitter, s pour continuer\n");
						scanf("%*c%c", &reponse);
				
					}
			
					printf("Voulez vous sauvegarder la partie y pour Oui et n pour Non\n");
					scanf("%*c%c", &reponse);                                                                                   
					if(reponse == 'y') {
						sauvegarder(fic_save);
					}
					fclose(fic_save);
				}
			
			break;
			case 3:  printf("Au revoir\n"); break;
			default: printf("Erreur: votre choix doit etre compris entre 1 et 6\n");
		}
	return 0;
}
