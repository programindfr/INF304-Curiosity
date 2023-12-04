#ifndef _OBSERVATEUR_H_
#define _OBSERVATEUR_H_

#include <stdbool.h>

typedef enum {
	ActionAvancer,
	ActionGauche,
	ActionDroite,
	ActionMesurer
} Action;

void observateur(Action a);
bool est_valide(void);

#endif
