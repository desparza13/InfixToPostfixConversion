/*
 * queue.h
 *
 *  Created on: 21 oct. 2021
 *      Author: José Luis Elvira
 */

#include "datatypes.h"

#ifndef QUEUE_H_
#define QUEUE_H_

struct STRQUEUENODE {
	TYPE data;	// Apuntador a cualquier tipo de elemento.
	struct STRQUEUENODE *next;
};

typedef struct STRQUEUENODE * QUEUENODE;

struct STRQUEUE {
	QUEUENODE first,last;
	int size;
};

typedef struct STRQUEUE * QUEUE;

QUEUE queue_create();
void queue_offer(QUEUE queue,TYPE data);
TYPE queue_poll(QUEUE queue);
BOOL queue_isempty(QUEUE queue);
int queue_size(QUEUE queue);
void queue_destroy(QUEUE queue);
TYPE queue_peek(QUEUE queue);



#endif /* QUEUE_H_ */
