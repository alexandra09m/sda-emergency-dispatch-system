// Dulhan Maria Alexandra 313CA

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "implementari_date.h"

incident *creare_lista_incidente(void)
{
	incident *santinela = malloc(sizeof(incident));
	DIE(!santinela, "Eroare la alocare santinela in creare_lista_incidente\n");

	santinela->id = 0;
	strcpy(santinela->prioritate, "low");
	santinela->descriere = "test incident";
	strcpy(santinela->status, "solved");
	
	santinela->prev = santinela;
	santinela->next = santinela;

	return santinela;
}

// adauga in coada un incident nou si il returneaza
incident *adaugare_incident(incident *santinela, int id, char prioritate[7], char *descriere)
{
	// creeaza nod nou
	incident *nou = malloc(sizeof(incident));
	DIE(!nou, "Eroare la alocare incident nou in adaugare_incident.\n");

	nou->id = id;
	strcpy(nou->prioritate, prioritate);
	strcpy(nou->status, "queued");

	nou->descriere = malloc(strlen(descriere) + 1);
	strcpy(nou->descriere, descriere);

	// adauga nodul in lista
	incident *curr = santinela->prev;
	nou->prev = curr;
	nou->next = santinela;
	curr->next = nou;
	santinela->prev = nou;

	return nou;
}

// returneaza incidentul cu id ul dat
// daca id ul nu este valid, returneaza NULL
incident *gaseste_incident(incident *santinela, int id)
{
	incident *curr = santinela->next;
	while (curr != santinela) {
		if (curr->id == id) {
			return curr;
		}

		curr = curr->next;
	}

	return NULL;
}

// elibereaza o lista de incidente
void elib_lista_incidente(incident *santinela)
{
	incident *curr = santinela->next;

	while (curr != santinela) {
		incident *tmp = curr;
		curr = curr->next;
		free(tmp->descriere);
		free(tmp);
	}

	free(santinela);
}

interventie *creare_lista_interv(void)
{
	interventie *santinela = malloc(sizeof(interventie));
	DIE(!santinela, "Eroare la alocare santinela in creare_lista_interv.\n");

	santinela->incident = NULL;
	santinela->unit = NULL;

	santinela->prev = santinela;
	santinela->next = santinela;

	return santinela;
}

int get_size_interv(interventie *santinela)
{
	int cnt  = 0;
	interventie *curr = santinela->next;
	while (curr != santinela) {
		cnt++;
		curr = curr->next;
	}

	return cnt;
}

// returneaza interventia data de id
// daca id ul este invalid, atunci returneaza NULL
interventie *gaseste_interv(interventie *santinela, int id)
{
	interventie *curr = santinela->next;
	while (curr != santinela) {
		if (curr->incident->id == id) {
			return curr;
		}

		curr = curr->next;
	}

	return NULL;
}

void adauga_final_interv(interventie *santinela, interventie *nou)
{
	interventie *last = santinela->prev;
	nou->prev = last;
	nou->next = santinela;
	last->next = nou;
	santinela->prev = nou;
}

// elibereaza lista de interventii
void elib_lista_interv(interventie *santinela)
{
	interventie *curr = santinela->next;

	while (curr != santinela) {
		interventie *tmp = curr;
		curr = curr->next;
		free(tmp);
	}

	free(santinela);
}

// returneaza unit ul dupa id
// daca id ul este invalid returneaza NULL
unit *gaseste_unit_id(sistem *sist, int id)
{
	for (int i = 0; i < sist->nr_units; i++) {
		if (sist->units[i].id == id) {
			return &sist->units[i];
		}
	}

	return NULL;
}

// Aloca memorie pentru o noua coada si o initializeaza
queue *creare_q(void)
{
	queue *q = malloc(sizeof(queue));
	DIE(!q, "Eroare la creare coada in creare_q.\n");

	q->front = NULL;
	q->end = NULL;
	q->size = 0;

	return q;
}

unsigned int get_size_q(queue *q)
{
	return q->size;
}

// insereaza un element nou la la finalul cozii daca x = 1
// si la inceputul cozii daca x = 0
void enqueue(queue *q, void *data, int poz)
{
	node *nou = malloc(sizeof(node));
	DIE(!nou, "Eroare la nod nou in enqueue.\n");

	nou->next = NULL;
	nou->data = data;

	if (!q->end) {
		q->front = nou;
		q->end = nou;
	} else if (poz == 1) {
		q->end->next = nou;
		q->end = nou;
	} else if (poz == 0) {
		nou->next = q->front;
		q->front = nou;
	}

	q->size++;
}

// scoate primul element din coada, returneaza ce stocheaza si il elibereaza
void *dequeue(queue *q)
{
	if (!q->size) {
		return NULL;
	}

	node *nod = q->front;
	void *data = nod->data;

	q->front = q->front->next;
	if (!q->front) {
		q->end = NULL;
	}
	q->size--;

	free(nod);
	return data;
}

// returneaza primul incident din coada de asteptare in functie de prioritate
// daca nu exista niciun incident in asteptare, returneaza NULL 
incident *gaseste_coada_priorit(sistem *sist)
{
	incident *inc = (incident *)dequeue(sist->q_high);
	if (inc) {
		return inc;
	}

	inc = (incident *)dequeue(sist->q_medium);
	if (inc) {
		return inc;
	}

	inc = (incident *)dequeue(sist->q_low);
	if (inc) {
		return inc;
	}

	return NULL;
}

void elib_q(queue *q)
{
	node *curr = q->front;
	while (q->size) {
		node *tmp = curr->next;
		free(curr);
		curr = tmp;
		q->size--;
	}

	free(q);
}

stack *creare_st(void)
{
	stack *st = malloc(sizeof(stack));
	DIE(!st, "Eroare la alocare stiva in creare_st.\n");

	st->head =  NULL;
	st->size = 0;

	return st;
}

// adauga un nod nou in varful stivei
void push(stack *st, void *data)
{
	// nod nou
	node *nou = malloc(sizeof(node));
	DIE(!nou, "Eroare la alocare nod nou in push.\n");

	nou->data = data;
	nou->next = st->head;
	st->head = nou;

	st->size++;
}

// elimina elementul din varful stivei si il returneaza
// returneaza NULL daca nu exista elemente in stiva
void *pop(stack *st)
{
	if (!st->size) {
		return NULL;
	}

	node *nod = st->head;
	void *data = nod->data;

	st->head = nod->next;
	st->size--;

	free(nod);
	return data;
}

void elib_st(stack *st)
{
	node *curr = st->head;
	while (curr != NULL) {
		node *tmp = curr->next;
		free(curr);
		curr = tmp;
	}
	
	free(st);
}
