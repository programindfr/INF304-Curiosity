#include "generation_terrains.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "environnement.h"
#include "interprete.h"
#include "programme.h"

int nb_cases_occupees(Terrain *T) {
  int occupee = 0;
  int x, y;
  for (x = 0; x < largeur(T); x++) {
    for (y = 0; y < hauteur(T); y++) {
      if (T->tab[x][y] != LIBRE)
        occupee++;
    }
  }
  return occupee;
}

// Test de generation aléatoire de terrains
// Le programme génère n terrains de largeur et hauteur fixes
// avec largeur et hauteur impaires et inférieures a dimension_max de terrain.h
// avec densité d'obstacle dObst
// autre que la case centrale soit occupee
// l'appel du programme se fait avec 5 arguments :
// generation_terrains N largeur hauteur dObstacle fichier_res
// la sortie se fait dans le fichier resultat

int main(int argc, char **argv) {
  int N, i, l, h, graine, nb;
  float dObst;
  FILE* resFile;
  Terrain T;

  if (argc <= 8) {
    printf(
        "Usage: %s <fichier_programme> <N> <L> <H> <d> <graine> <nb_step_max> <fichier_res> \n",
        argv[0]);
    return 1;
  }

  N = strtol(argv[2], NULL, 10);
  l = strtol(argv[3], NULL, 10);
  h = strtol(argv[4], NULL, 10);
  dObst = strtof(argv[5], NULL);
  graine = strtol(argv[6], NULL, 10);
  nb = strtol(argv[7], NULL, 10);

  // test de l et h
  if (l > DIM_MAX || l % 2 == 0) {
    printf("Largeur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if (h > DIM_MAX || h % 2 == 0) {
    printf("Hauteur incorrecte : doit être impaire et <= %d\n", DIM_MAX);
    return 1;
  }
  if ((dObst > 1) || (dObst < 0)) {
    printf("Densité incorrecte : doit être comprise entre 0 et 1\n");
    return 1;
  }

  // Ouverture du fichier résultat
  resFile = fopen(argv[8], "w");
  // Écriture du nombre de terrains
  fprintf(resFile, "%d\n", N);

  // Initialisation de la fonction random
  srand(graine);

  Environnement envt;
  Programme prog;
  etat_inter etat;
  resultat_inter res;
  int valide = 0;
  int totalePas = 0;

	for (i = 0; i < N; i++)
	{
		/* Initialisation de l'environnement : lecture du terrain,
		 initialisation de la position du robot */
		generation_aleatoire(&T, l, h, dObst);
		int x = l/2, y = h/2;
		init_robot(&(envt.r), x, y, Est);
		envt.t = T;
		lire_programme(&prog, argv[1]);

		/* Initialisation de l'état */
		int pas = 0;
		init_etat(&etat);
		do {
			res = exec_pas(&prog, &envt, &etat);
			pas++;
			/* Affichage du terrain et du robot */
			afficher_envt(&envt);
		} while (res == OK_ROBOT && pas < nb);
    totalePas += pas;

		/* Affichage du résultat */
		switch (res) {
		case SORTIE_ROBOT:
		fprintf(resFile, "%d\n", pas);
    valide++;
		break;
		
		case OK_ROBOT:
		case ARRET_ROBOT:
		fprintf(resFile, "%d\n", -1);
		break;
		case PLOUF_ROBOT:
		fprintf(resFile, "%d\n", -2);
		break;
		case CRASH_ROBOT:
		fprintf(resFile, "%d\n", -3);
		break;
		
		case ERREUR_PILE_VIDE:
		printf("ERREUR : pile vide\n");
		break;
		case ERREUR_ADRESSAGE:
		printf("ERREUR : erreur d'adressage\n");
		break;
		case ERREUR_DIVISION_PAR_ZERO:
		printf("ERREUR : division par 0\n");
		break;
		}
	}
  printf("invalide: %i%%\n", (int) (100 * (1 - (float) valide / (float) N)));
  printf("pas: %f\n", (float) totalePas / (float) N);
  return 0;
}
