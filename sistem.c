// Dulhan Maria Alexandra 313CA

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "sistem.h"
#include "implementari_date.h"

// aloca sistemul si il initializeaza cu datele din fisier
// fisierul este deschis in prealabil si nu este inchis in fisier
sistem *init_sistem()
{
	sistem *sist = malloc(sizeof(sistem));
	DIE(!sist, "Eroare la alocare in init_sist la sist.\n");

	scanf("%d", &sist->nr_units);

	// aloca si initializeaza unitatile
	sist->units = malloc(sist->nr_units * sizeof(unit));
	DIE(!sist->units, "Eroare la alocare units in init_sist.\n");

	for (int i = 0; i < sist->nr_units; i++) {
		scanf("%d %c", &sist->units[i].id, &sist->units[i].tip);
		sist->units[i].disponibilitate = 1;
	}

	// aloca si initializeaza incidentele
	sist->incidente = creare_lista_incidente();

	// aloca si initializeaza interventiile
	sist->interventii = creare_lista_interv();

	// aloca si initializeaza cele 3 cozi de asteptare
	sist->q_low = creare_q();
	sist->q_medium = creare_q();
	sist->q_high = creare_q();

	sist->q_units_disponibile = creare_q();
	for (int i = 0; i < sist->nr_units; i++) {
		enqueue(sist->q_units_disponibile, &sist->units[i], 1);
	}

	sist->st_istoric_dispatch = creare_st();

	return sist;
	
}

// elibereaza toate datele din sistem
void elib_sist(sistem *sist)
{
	free(sist->units);
	elib_lista_incidente(sist->incidente);
	elib_lista_interv(sist->interventii);

	elib_q(sist->q_low);
	elib_q(sist->q_medium);
	elib_q(sist->q_high);

	elib_q(sist->q_units_disponibile);

	elib_st(sist->st_istoric_dispatch);

	free(sist);
}

