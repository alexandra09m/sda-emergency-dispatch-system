// Dulhan Maria Alexandra 313CA

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "comenzi.h"
#include "utilitare.h"

int main(void)
{
	sistem *sist = init_sistem();

	unsigned int nr_oper;
	scanf("%d", &nr_oper);
	getchar();

	char *linie;
	for (unsigned int i = 0; i < nr_oper; i++) {
		linie = citire_linie();
		linie[strcspn(linie, "\n")] = '\0';

		if (proc_comanda_incidente(linie, sist) == 0) {
			if (proc_comanda_units(linie, sist) == 0) {
				if(proc_comanda_interv(linie, sist) == 0) {
					if (proc_comanda_dispatch(linie, sist) == 0) {
						perror("Comanda nu a fost gasita!.\n");
					}
				}
			}
		}

		free(linie);
	}

	elib_sist(sist);
	return 0;
}
