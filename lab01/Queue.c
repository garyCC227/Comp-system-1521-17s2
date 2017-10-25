// ADT for a FIFO queue
// COMP1521 17s2 Week01 Lab Exercise
// Written by John Shepherd, July 2017
// Modified by ...

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "Queue.h"

typedef struct QueueNode {
   int jobid;  // unique job ID
   int size;   // size/duration of job
   struct QueueNode *next;
} QueueNode;

struct QueueRep {
   int nitems;      // # of nodes
   QueueNode *head; // first node
   QueueNode *tail; // last node
};



// TODO:
// remove the #if 0 and #endif
// once you've added code to use this function

// create a new node for a Queue
static
QueueNode *makeQueueNode(int id, int size)
{
   QueueNode *new;
   new = malloc(sizeof(struct QueueNode));
   assert(new != NULL);
   new->jobid = id;
   new->size = size;
   new->next = NULL;
   return new;
}



// make a new empty Queue
Queue makeQueue()
{
   Queue new;
   new = malloc(sizeof(struct QueueRep));
   assert(new != NULL);
   new->nitems = 0; new->head = new->tail = NULL;
   return new;
}

// release space used by Queue
void  freeQueue(Queue q)
{
   assert(q != NULL);
   QueueNode *n = q->head;
	
	while(n != NULL){
		QueueNode *n2 = n;	
		free(n);
		n = n2->next;
	}
	free(q);
}

// add a new item to tail of Queue
void  enterQueue(Queue q, int id, int size)
{
   assert(q != NULL);
   QueueNode *n1 = q->head;
   QueueNode *n2 = q->tail;
   QueueNode *new = makeQueueNode(id, size);
	if(n2 == NULL){
		q->tail = q->head = new;
		
	}else{
		n2->next = new;		
	}
	q->tail = new;
	q->nitems++;
}

// remove item on head of Queue
int   leaveQueue(Queue q)
{
   assert(q != NULL);
	QueueNode *n;
   int n1 = 0;
	if(q->head != NULL){
		if(q->head == q->tail){ // only one item
			q->tail = NULL;	
		}
		n = q->head;
		n1 = n->jobid;
		q->head = q->head->next;
		free(n);
		q->nitems--;
	}
	if(q->head == NULL){
		q->tail = NULL;
	}
   return n1; // replace this statement
}

// count # items in Queue
int   lengthQueue(Queue q)
{
   assert(q != NULL);
   return q->nitems;
}

// return total size in all Queue items
int   volumeQueue(Queue q)
{
   assert(q != NULL);
   int sum = 0;
	QueueNode *n = q->head;
	while(n != NULL){
		sum = sum + n->size;
		n = n->next;

	}	
   return sum; // replace this statement
}

// return size/duration of first job in Queue
int   nextDurationQueue(Queue q)
{
   assert(q != NULL);
   QueueNode *n = q->head;
	int n1;

	if(n == NULL){
		return 0;
	}else{
		n1 = n->size;
		return n1;	
	}
}


// display jobid's in Queue
void showQueue(Queue q)
{
   QueueNode *curr;
   curr = q->head;
   while (curr != NULL) {
      printf(" (%d,%d)", curr->jobid, curr->size);
      curr = curr->next;
   }
}
