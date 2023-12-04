#include "observateur.h"

Etat e = EtatAutre;

void observateur(Action a) {
    switch (e) {
        case EtatAvancerApresMesure:
        case EtatAutre:
            switch (a) {
                case ActionAvancer:
                case ActionGauche:
                case ActionDroite:
                    break;
                case ActionMesurer:
                    e = EtatMesure;
            }
            break;
        case EtatMesure:
            switch (a) {
                case ActionAvancer:
                    e = EtatAvancerApresMesure;
                case ActionMesurer:
                    break;
                case ActionGauche:
                case ActionDroite:
                    e = EtatAutre;
            }
    }
}

bool est_valide(void) { return e == EtatAvancerApresMesure; }
