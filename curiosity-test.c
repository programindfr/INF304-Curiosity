#include "environnement.h"
#include "interprete.h"
#include "programme.h"
#include "robot.h"

#include <stdio.h>
#include <stdlib.h>

char code(resultat_inter res) {
	switch (res) {
		case OK_ROBOT:
			return 'N';
		case ARRET_ROBOT:
			return 'F';
		case SORTIE_ROBOT:
			return 'S';
		case CRASH_ROBOT:
			return 'O';
		case PLOUF_ROBOT:
			return 'P';
		default:
			return '?';
	}
}

char orientation(Orientation o) {
	switch (o) {
		case Nord:
			return 'N';
		case Est:
			return 'E';
		case Ouest:
			return 'O';
		case Sud:
			return 'S';
	}
}

int main(int argc, char * argv[]) {
	Environnement envt;
	Programme prog;
	etat_inter etat;
	resultat_inter res = OK_ROBOT;

	char fterrain[512];
	char fprog[512];
	int pas_max;
	char e;
	int x, y;
	char o;

	if (argc < 2) {
		printf("Usage: %s <test>\n", argv[0]);
		return 1;
	}

	init_etat(&etat);

	FILE * test = fopen(argv[1], "r");
	fscanf(test, "%s\n%s\n%i\n%c\n", fterrain, fprog, &pas_max, &e);
	if (e == 'N' || e == 'F')
		fscanf(test, "%i %i\n%c", &x, &y, &o);

	printf("Terrain : %s\n"
		   "Programme : %s\n"
		   "Nombre de pas : %i\n"
		   "Fin attendue : %c\n",
		   fterrain, fprog, pas_max, e);
	if (e == 'N' || e == 'F')
		printf("X : %i\n"
			   "Y : %i\n"
			   "Orientation : %c\n",
			   x, y, o);
	printf("\n");

  gestion_erreur_terrain(
		initialise_environnement(&envt, fterrain), true);
	gestion_erreur_programme(
		lire_programme(&prog, fprog), true);

	for (int i = 0; i < pas_max && res == OK_ROBOT; i++) {
		printf("Étape n°%i\n", i+1);
		res = exec_pas(&prog, &envt, &etat);
		afficher_envt(&envt);
	}

	if (e == code(res)) {
		if ((e == 'N' || e == 'F') 
			&& (x != envt.r.x
				|| y != envt.r.y
				|| o != orientation(envt.r.o)))
			printf("2 Les coordonnées et orientation (%i, %i, %c) "
				   "ne sont pas ceux attendus (%i, %i, %c).\n",
				   x, y, o, envt.r.x, envt.r.y, orientation(envt.r.o));
		else
			printf("0 Le test s'est déroulé correctement.\n");
	} else
		printf("1 Le code de retour (%c) n'est pas celui attendu (%c).\n", code(res), e);

	fclose(test);

	return 0;
}
