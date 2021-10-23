/*
Daniela Esparza Espinosa
Definición de las funciones para el stack
*/
#include "datatypes.h"

#ifndef STACK_H_
#define STACK_H_

struct STRSTACKNODE {
	TYPE data;	// Apuntador a cualquier tipo de elemento.
	struct STRSTACKNODE *prev;
};

typedef struct STRSTACKNODE * STACKNODE;

struct STRSTACK {
	STACKNODE top;
	int size;
};

typedef struct STRSTACK * STACK;

STACK stack_create();
void stack_push(STACK stack,TYPE data);
TYPE stack_pop(STACK stack);
BOOL stack_isempty(STACK stack);
void stack_destroy(STACK stack);
TYPE stack_top(STACK stack);

#endif /* STACK_H_ */
