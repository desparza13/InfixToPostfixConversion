/*
Daniela Esparza Espinosa
Implementación de las funciones del tipo de dato abstracto Stack
*/
#include "stack.h"

STACK stack_create()
{
	STACK tmp=malloc(sizeof(struct STRSTACK));
	tmp->top=NULL;
	tmp->size=0;
	return tmp;
}

void stack_push(STACK stack,TYPE data)
{
	STACKNODE new = malloc(sizeof(struct STRSTACKNODE));
	new->data = data;
	new->prev = stack->top;
	stack->top=new;
	stack->size++;
}

TYPE stack_pop(STACK stack)
{
	STACKNODE node=stack->top;
	TYPE retval=NULL;

	// Si el stack no est� vac�o
	if(node!=NULL)
	{
		retval=node->data;
		stack->top=node->prev;

		free(node);
		stack->size--;
	}

	return(retval);
}

BOOL stack_isempty(STACK stack)
{
	return(stack->top==NULL);
}

void stack_destroy(STACK stack)
{
	while(!stack_isempty(stack))
		stack_pop(stack);
	free(stack);
}

TYPE stack_top(STACK stack)
{
	return(stack->top->data);
}
