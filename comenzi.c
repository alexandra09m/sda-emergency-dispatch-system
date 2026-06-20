// Dulhan Maria Alexandra 313CA

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "comenzi.h"

// proceseaza comenzile legate de incidente
int proc_comanda_incidente(char *linie, sistem *sist)
{
	if (!strncmp(linie, "ADD_INCIDENT ", 13)) {
		int id;
		char prioritate[13];
		sscanf(linie + 13, "%d %s", &id, prioritate);

		char *descriere = decupare_descr(linie);

		incident *inc;
		inc = adaugare_incident(sist->incidente, id, prioritate, descriere);
		free(descriere);

		if (strncmp(prioritate, "low", 3) == 0) {
			enqueue(sist->q_low, inc, 1);
		} else if (strncmp(prioritate, "medium", 6) == 0) {
			enqueue(sist->q_medium, inc, 1);
		} else {
			enqueue(sist->q_high, inc, 1);
		}

		return 1;
	}

	if (!strncmp(linie, "SHOW_INCIDENT ", 14)) {
		int id;
		sscanf(linie + 14, "%d", &id);

		incident *inc = gaseste_incident(sist->incidente, id);

		// id invalid
		if (inc == NULL) {
			printf("INVALID OPERATION! ERROR 404\n");
			return 1;
		}

		printf("Incident %d has %s priority, ", id, inc->prioritate);
		printf("the following description: \"%s\" and is %s\n",
			   inc->descriere, inc->status);
		return 1;
	}

	if (!strncmp(linie, "SOLVED_INCIDENT ", 16)) {
		int id;
		sscanf(linie + 16, "%d", &id);

		incident *inc = gaseste_incident(sist->incidente, id);

		// id invalid sau incidentul nu are statusul "intervened"
		if (inc == NULL || strcmp(inc->status, "intervened")) {
			printf("INVALID OPERATION! ERROR 404\n");
			return 1;
		}

		// marcheaza interventia ca "solved" si echipajul devine din nou
		// disponibil
		interventie *interv = gaseste_interv(sist->interventii, id);
		strcpy(inc->status, "solved");
		interv->unit->disponibilitate = 1;
		enqueue(sist->q_units_disponibile, interv->unit, 1);

		return 1;
	}

	return 0;
}

// proceseaza comenzile legate de unitati
int proc_comanda_units(char *linie, sistem *sist)
{
	if (!strncmp(linie, "SHOW_UNIT ", 10)) {
		int id;
		sscanf(linie + 10, "%d", &id);

		unit *ut = gaseste_unit_id(sist, id);

		// verifica daca id ul este invalid
		if (!ut) {
			printf("INVALID OPERATION! ERROR 404\n");
			return 1;
		}

		char disponibilitate[12];
		if (ut->disponibilitate) {
			strcpy(disponibilitate, "available");
		} else {
			strcpy(disponibilitate, "unavailable");
		}

		printf("Unit %d is type %c and is %s\n", id, ut->tip, disponibilitate);
		return 1;
	}

	if (!strncmp(linie, "CHECK_UNITS_AVAILABILITY", 24)) {
		unsigned int cnt = get_size_q(sist->q_units_disponibile);
		printf("Number of available units: %u\n", cnt);
		
		return 1;
	}

	return 0;
}

// proceseaza comenzile legate de interventii
int proc_comanda_interv(char *linie, sistem *sist)
{
	if (!strncmp(linie, "SHOW_INTERVENTIONS", 18)) {
		interventie *curr = sist->interventii->next;
		if (curr == sist->interventii) {
			printf("No intervention has been initiated\n");
			return 1;
		}

		while (curr != sist->interventii) {
			printf("Incident %d was assigned to unit %d, ", curr->incident->id,
				   curr->unit->id);
			printf("and has the following status: \"%s\"\n",
				   curr->incident->status);
			curr = curr->next;
		}

		return 1;
	}

	return 0;
}

// proceseaza comenzile legate de dispatch
int proc_comanda_dispatch(char *linie, sistem *sist)
{
	if (!strcmp(linie, "DISPATCH")) {

		// daca nu exista incidente in cozile de asteptare sau daca nu sunt
		// unitati disponibile
		incident *inc = gaseste_coada_priorit(sist);
		if (!inc) {
			printf("INVALID OPERATION! ERROR 404\n");
			return 1;
		}
		unit *ut = dequeue(sist->q_units_disponibile);
		if (!ut) {
			printf("INVALID OPERATION! ERROR 404\n");
			return 1;
		}

		interventie *interv = malloc(sizeof(interventie));
		DIE(!interv, "Eroare la alocare interv in proc_com_dispatch.\n");
		interv->incident = inc;
		interv->unit = ut;
		adauga_final_interv(sist->interventii, interv);

		strcpy(inc->status, "intervened");
		ut->disponibilitate = 0;

		push(sist->st_istoric_dispatch, interv);

		return 1;
	}

	if (!strcmp(linie, "UNDO_LAST_DISPATCH")) {

		// scoate ultima interventie in desfasurare
		interventie *interv = pop(sist->st_istoric_dispatch);
		while (interv && !strcmp(interv->incident->status, "solved")) {
			interv = pop(sist->st_istoric_dispatch);
		}

		// daca nu exista interventii in desfasurare
		if (!interv) {
			printf("INVALID OPERATION! ERROR 404\n");
			return 1;
		}

		// reintroduce incidentul in asteptare
		incident *inc = interv->incident;
		strcpy(inc->status, "queued");
		if (strncmp(inc->prioritate, "low", 3) == 0) {
			enqueue(sist->q_low, inc, 0);
		} else if (strncmp(inc->prioritate, "medium", 6) == 0) {
			enqueue(sist->q_medium, inc, 0);
		} else {
			enqueue(sist->q_high, inc, 0);
		}		

		// reintroduce echipajul ca fiind disponibil
		unit *ut = interv->unit;
		ut->disponibilitate = 1;
		enqueue(sist->q_units_disponibile, ut, 1);

		// elimina interventia din lista de interventii
		interv->prev->next = interv->next;
		interv->next->prev = interv->prev;
		free(interv);

		return 1;
	}

	return 0;
}
