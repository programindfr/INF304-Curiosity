#include "observateur.h"

typedef enum {
    EtatAutre,
    EtatMesure,
    EtatApresMesure
} Etat;

Etat e = EtatAutre;

void observateur(Action a) {
    switch (e) {
        case EtatApresMesure:
        case EtatAutre:
            switch (a) {
                case ActionAvancer:
                case ActionGauche:
                case ActionDroite:
                    e = EtatAutre;
                    break;
                case ActionMesurer:
                    e = EtatMesure;
            }
            break;
        case EtatMesure:
            switch (a) {
                case ActionGauche:
                case ActionAvancer:
                    e = EtatApresMesure;
                case ActionMesurer:
                    break;
                case ActionDroite:
                    e = EtatAutre;
            }
    }
}

bool est_valide(void) { return e == EtatApresMesure; }
