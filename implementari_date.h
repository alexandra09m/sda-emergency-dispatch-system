// Dulhan Maria Alexandra 313CA

#ifndef IMPL_DATE_H
#define IMPL_DATE_H

#include "sistem.h"
#include "utilitare.h"

incident *creare_lista_incidente(void);
incident *adaugare_incident(incident *santinela, int id, char prioritate[7], char *descriere);
incident *gaseste_incident(incident *santinela, int id);
void elib_lista_incidente(incident *santinela);

interventie *creare_lista_interv(void);
int get_size_interv(interventie *santinela);
interventie *gaseste_interv(interventie *santinela, int id);
void adauga_final_interv(interventie *santinela, interventie *nou);
void elib_lista_interv(interventie *santinela);

unit *gaseste_unit_id(sistem *sist, int id);

queue *creare_q(void);
unsigned int get_size_q(queue *q);
void enqueue(queue *q, void *data, int poz);
void *dequeue(queue *q);
incident *gaseste_coada_priorit(sistem *sist);
void elib_q(queue *q);

stack *creare_st(void);
void push(stack *st, void *data);
void *pop(stack *st);
void elib_st(stack *st);

#endif
