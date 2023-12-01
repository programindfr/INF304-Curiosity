#include "terrain.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

char * print_terrain_err(erreur_terrain e) {
  switch (e) {
    case OK:
      return "Ok";
    case ERREUR_FICHIER:
      return "Erreur fichier";
    case ERREUR_LARGEUR_SUP:
      return "Erreur largeur supérieure";
    case ERREUR_HAUTEUR_SUP:
      return "Erreur hauteur supérieure";
    case ERREUR_LARGEUR_INF:
      return "Erreur largeur inférieure";
    case ERREUR_HAUTEUR_INF:
      return "Erreur hauteur inférieure";
    case ERREUR_DIM:
      return "Erreur dimensions";
    case ERREUR_CHAR:
      return "Erreur caractère inconnu";
    case ERREUR_ROBOT:
      return "Erreur pas ou trop de robots";
  }
}

int main(int argc, char ** argv) {
  FILE * f;
  Terrain t;
  int x, y;
  erreur_terrain err = ERREUR_FICHIER;
  char buf[2048];
  bool first = true;

  if (argc < 2) {
    printf("Usage : %s <fichier>\n", argv[0]);
    return 1;
  }

  strcpy(buf, argv[1]);

  while (err == ERREUR_FICHIER) {
    if (!first) {
      printf("Entrez le nouveau fichier >> ");
      fgets(buf, sizeof(buf), stdin);
    } else first = false;

    printf(">> %s\n", buf);
    f = fopen(buf, "r");
    err = lire_terrain(f, &t, &x, &y);
    printf("%s\n", print_terrain_err(err));
    fclose(f);
  }
}
