/*
 * queue.c
 *
 *  Created on: 21 oct. 2021
 *      Author: Jos� Luis Elvira
 */
#include "queue.h"

QUEUE queue_create()
{
	QUEUE tmp=malloc(sizeof(struct STRQUEUE));
	tmp->first=NULL;
	tmp->last=NULL;
	tmp->size=0;
	return tmp;
}

void queue_offer(QUEUE queue,TYPE data)
{
	QUEUENODE new=malloc(sizeof(struct STRQUEUENODE));
	new->data=data;
	new->next=NULL;

	if(queue->first==NULL)
		queue->first=new;
	else
		queue->last->next=new;

	queue->last=new;
	queue->size++;
}

TYPE queue_poll(QUEUE queue)
{
	QUEUENODE to_remove=queue->first;
	TYPE retdata=NULL;

	// Checar si la cola, a�n tiene elementos
	if(to_remove!=NULL)
	{
		retdata=to_remove->data;	// Obtenemos el dato que est� en el nodo
		queue->first=queue->first->next;	// El primero, ahora ser� el siguiente del primero
		queue->size--;				// Decrementamos el tama�o
		free(to_remove);			// Liberamos el nodo de la memoria din�mica

		if(queue->first==NULL)  // Qued� la cola vac�a
			queue->last=NULL;
	}

	return(retdata);
}

BOOL queue_isempty(QUEUE queue)
{
	return queue->first==NULL;
}

int queue_size(QUEUE queue)
{
	return queue->size;
}

TYPE queue_peek(QUEUE queue)
{
	return queue->first->data;
}

void queue_destroy(QUEUE queue)
{
	while(!queue_isempty(queue))
	{
		queue_poll(queue);
	}
	free(queue);
}
