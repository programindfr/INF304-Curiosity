#include "environnement.h"
#include "interprete.h"
#include "programme.h"
#include "robot.h"
#include "observateur.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char * argv[]) {
	Environnement envt;
	Programme prog;
	etat_inter etat;
	resultat_inter res = OK_ROBOT;

	if (argc < 3) {
		printf("Usage: %s <terrain> <programme>\n", argv[0]);
		return 1;
	}

	init_etat(&etat);

  gestion_erreur_terrain(
		initialise_environnement(&envt, argv[1]), true);
	gestion_erreur_programme(
		lire_programme(&prog, argv[2]), true);

	for (int i = 0;; i++) {
		printf("Étape n°%i\n", i+1);
		res = exec_pas(&prog, &envt, &etat);
		afficher_envt(&envt);
		
		if (est_valide())
			printf("La propriété est valide !\n\n");
		else
			printf("La propriété n'est pas valide.\n\n");

		if (res != OK_ROBOT)
			break;
	}

	return 0;
}
