#include "terrain.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

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
    gestion_erreur_terrain(err, false);
    if (!err) printf("0 Ok\n");
    fclose(f);
  }
}
