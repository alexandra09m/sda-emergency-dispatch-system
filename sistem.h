// Dulhan Maria Alexandra 313CA

#ifndef UNIT_H
#define UNIT_H

#include "utilitare.h"

typedef struct node {
	void *data;
	struct node *next;
} node;

typedef struct queue {
	node *front;
	node *end;

	int size;
} queue;

typedef struct stack{
	node *head;

	int size;
} stack;

// parametri ce descriu echipajele
typedef struct {
	int id;
	char tip;

	// 0 daca e nedisponibil, 1 in caz contrar
	int disponibilitate;
} unit;

// parametri ce descriu incidentele
// lista dublu inlantuita cu santinela
typedef struct incident {
	int id;
	char prioritate[7];
	char *descriere;
	char status[11];

	struct incident *prev, *next;
} incident;

// parametri ce descriu interventiile
// lista dublu inlantuita cu santinela
typedef struct interventie {
	incident *incident;
	unit *unit;

	struct interventie *prev, *next;
} interventie;

// structura ce reprezinta un sistem
typedef struct {
	unit* units;
	int nr_units;

	incident* incidente;
	interventie* interventii;

	queue *q_low;
	queue *q_medium;
	queue *q_high;

	queue *q_units_disponibile;

	stack *st_istoric_dispatch;
} sistem;


sistem *init_sistem();
void elib_sist(sistem *sist);

#endif
