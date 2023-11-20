#include "generation_terrains.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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
  int N, i, l, h;
  float dObst;
  FILE *resFile;
  Terrain T;

  if (argc < 6) {
    printf(
        "Usage: %s <N> <largeur> <hauteur> <densite_obstacle> <fichier_res> \n",
        argv[0]);
    return 1;
  }

  N = strtol(argv[1], NULL, 10);
  l = strtol(argv[2], NULL, 10);
  h = strtol(argv[3], NULL, 10);
  dObst = strtof(argv[4], NULL);

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
  resFile = fopen(argv[5], "w");
  // Écriture du nombre de terrains
  fprintf(resFile, "%d\n", N);

  // Initialisation de la fonction random
  srand(time(NULL));

	float d;
	float dt = 0;
	int valide = 0;
	for (i = 0; i < N; i++)
	{
		// Génération aléatoire des terrains
		d = generation_aleatoire(&T, l, h, dObst);
		// Écriture des terrains générés dans le fichier resFile
		ecrire_terrain(resFile, &T, l / 2, h / 2);
		fprintf(resFile, "densite: %f\ntheorique: %f\n", d, dObst);
		// Écriture/Affichage des statistiques
		afficher_terrain(&T);
		printf("densite: %f\ntheorique: %f\n", d, dObst);
		dt += d;
		if (existe_chemin_vers_sortie(&T))
		{
			valide += 1;
		}
		printf("%f\n", (float) i / (float) N);
	}
	dt = dt / (float) i;
	fprintf(resFile, "totale: %f\n", dt);
	printf("totale: %f\n", dt);
	fprintf(resFile, "valide: %f\n", (float) valide / (float) i);
	printf("valide: %f\n", (float) valide / (float) i);

  // fermeture des fichiers
  fclose(resFile);
  return 0;
}
