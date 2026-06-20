// Dulhan Maria Alexandra 313CA

#ifndef COMENZI_H
#define COMENZI_H

#include "sistem.h"
#include "implementari_date.h"

// toate functiile returneaza 1 daca gasesc comanda, altfel returneaza 0

int proc_comanda_incidente(char *linie, sistem *sist);
int proc_comanda_units(char *linie, sistem *sist);
int proc_comanda_interv(char *linie, sistem *sist);
int proc_comanda_dispatch(char *linie, sistem *sist);

#endif
