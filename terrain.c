#include "terrain.h"
#include "robot.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

erreur_terrain
lire_terrain(FILE *f, Terrain *t, int *x, int *y)
{
    int l, h;   // Dimensions du terrain
    int rx, ry; // Coordonnées initiales du robot
    rx = -1;
    ry = -1;

    if (f == NULL) {
        return ERREUR_FICHIER;
    }
    
    fscanf(f, "%d\n%d\n", &l, &h);
    t->largeur = l;
    t->hauteur = h;
    
    if (l < 0 || l > DIM_MAX || h < 0 || h > DIM_MAX)
    {
        t->largeur = 0;
        t->hauteur = 0;
        return ERREUR_DIM;
    }
    
    char c;
    int posx = 0;
    int posy = 0;
    while (!feof(f))
    {
        fscanf(f, "%c", &c);
        switch (c)
        {
        case 'C':
            if (rx != -1 || ry != -1)
            {
                t->largeur = 0;
                t->hauteur = 0;
                return ERREUR_ROBOT;
            }
            rx = posx;
            ry = posy;
            t->tab[posx][posy] = LIBRE;
            posx++;
            break;
        case '.':
            t->tab[posx][posy] = LIBRE;
            posx++;
            break;
        case '~':
            t->tab[posx][posy] = EAU;
            posx++;
            break;
        case '#':
            t->tab[posx][posy] = ROCHER;
            posx++;
            break;
        case '\n':
            posy++;
            if (posx < l && posy <= h)
            {
                t->largeur = 0;
                t->hauteur = 0;
                return ERREUR_LARGEUR_INF;
            }
            posx = 0;
            break;
        default:
            t->largeur = 0;
            t->hauteur = 0;
            return ERREUR_CHAR;
        }
        if (posx > l)
        {
            t->largeur = 0;
            t->hauteur = 0;
            return ERREUR_LARGEUR_SUP;
        }
        if (posy-1 > h)
        {
            t->largeur = 0;
            t->hauteur = 0;
            return ERREUR_HAUTEUR_SUP;
        }
    }
    if (posy < h)
    {
        t->largeur = 0;
        t->hauteur = 0;
        return ERREUR_HAUTEUR_INF;
    }

    if (rx == -1 && ry == -1)
      return ERREUR_ROBOT;
    
    *x = rx;
    *y = ry;

    return OK;
}

/* Largeur d'un terrain */
int
largeur(Terrain *t)
{
    return t->largeur;
}

/* Hauteur d'un terrain */
int
hauteur(Terrain *t)
{
    return t->hauteur;
}

/* Indique si la case de coordonnées (x,y) est libre
   Renvoie vrai ssi les 3 conditions suivantes sont vraies :
    - 0 <= x < largeur
    - 0 <= y < hauteur
    - t.tab[x][y] = LIBRE
 */
int
est_case_libre(Terrain *t, int x, int y)
{
    return (0 <= x && x < t->largeur)
        && (0 <= y && y < t->hauteur)
        && t->tab[x][y] == LIBRE;
}

/* Affichage d'un terrain t sur la sortie standard */
void
afficher_terrain(Terrain *t)
{
    for (int hau = 0; hau < t->hauteur; hau++)
    {
        for (int lar = 0; lar < t->largeur; lar++)
        {
            switch (t->tab[lar][hau])
            {
            case LIBRE:
                printf(".");
                break;
            case EAU:
                printf("~");
                break;
            case ROCHER:
                printf("#");
                break;
            }
        }
        printf("\n");
    }
}

/* Écriture d'un terrain t dans un fichier f ouvert en écriture.
   x et y contiennent les coordonnées du robot
   Le terrain est écrit au format lisible par lire_terrain */
void
ecrire_terrain(FILE *f, Terrain *t, int x, int y)
{
    fprintf(f, "%d\n%d\n", t->largeur, t->hauteur);
    for (int hau = 0; hau < t->hauteur; hau++)
    {
        for (int lar = 0; lar < t->largeur; lar++)
        {
            if (x == lar && y == hau)
                fprintf(f, "C");
            else
            {
                switch (t->tab[lar][hau])
                {
                case LIBRE:
                    fprintf(f, ".");
                    break;
                case EAU:
                    fprintf(f, "~");
                    break;
                case ROCHER:
                    fprintf(f, "#");
                    break;
                }
            }
        }
        fprintf(f, "\n");
    }
}

void gestion_erreur_terrain(erreur_terrain e, bool exit1) {
    switch (e) {
    case OK:
        return;
    case ERREUR_FICHIER:
        fprintf(stderr, "1 Erreur terrain : erreur d'ouverture du fichier\n");
        break;
    case ERREUR_LARGEUR_SUP:
        fprintf(stderr, "2 Erreur terrain : largeur supérieure\n");
        break;
    case ERREUR_HAUTEUR_SUP:
        fprintf(stderr, "3 Erreur terrain : hauteur supérieure\n");
        break;
    case ERREUR_LARGEUR_INF:
        fprintf(stderr, "4 Erreur terrain : largeur inférieure\n");
        break;
    case ERREUR_HAUTEUR_INF:
        fprintf(stderr, "5 Erreur terrain : hauteur inférieure\n");
        break;
    case ERREUR_DIM:
        fprintf(stderr, "6 Erreur terrain : dimensions\n");
        break;
    case ERREUR_CHAR:
        fprintf(stderr, "7 Erreur terrain : caractère inconnu\n");
        break;
    case ERREUR_ROBOT:
        fprintf(stderr, "8 Erreur terrain : pas ou trop de robots\n");
    }
    if (exit1) exit(1);
}
