// Dulhan Maria Alexandra 313CA

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utilitare.h"

// citeste o linie dinamic si o returneaza
char *citire_linie()
{
	char aux[256];
	if (!fgets(aux, sizeof(aux), stdin)) {
		return NULL;
	}

	int capacit = strlen(aux) + 1;
	char *linie = malloc(capacit);
	DIE(!linie, "Eroare alocare linie.\n");
	strcpy(linie, aux);

	while (!strchr(linie, '\n')) {
		if (!fgets(aux, sizeof(aux), stdin)) {
			break;
		}

		int sp_nou = capacit + strlen(aux);
		char *tmp = realloc(linie, sp_nou);
		if (!tmp) {
			printf("Eroare realocare linie\n");
			free(linie);
			return NULL;
		}

		linie = tmp;
		strcat(linie, aux);
		capacit = sp_nou;
	}

	return linie;
}

// extrage descrierea dintre ghilimele din comanda
char *decupare_descr(char *linie)
{
	char *start = strchr(linie, '"');
	char *stop = strrchr(linie, '"');

	DIE(!start || !stop, "Eroare la extragere text in decupare_descr.\n");
	start++;

	int lun = stop - start;
	char *descriere = malloc((lun + 1) * sizeof(char));
	DIE(!descriere, "Eroare la alocare descriere in decupare_descr.\n");

	strncpy(descriere, start, lun);
	descriere[lun] = '\0';

	return descriere;
}
