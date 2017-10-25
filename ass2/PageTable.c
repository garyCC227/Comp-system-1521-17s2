// PageTable.c ... implementation of Page Table operations
// COMP1521 17s2 Assignment 2
// Written by John Shepherd, September 2017
// Linchen chen, 15/10/2017

#include <stdlib.h>
#include <stdio.h>
#include<assert.h>
#include "Memory.h"
#include "Stats.h"
#include "PageTable.h"

// Symbolic constants

#define NOT_USED 0
#define IN_MEMORY 1
#define ON_DISK 2

// PTE = Page Table Entry

typedef struct {
    char status;      // NOT_USED, IN_MEMORY, ON_DISK
    char modified;    // boolean: changed since loaded
    int  frame;       // memory frame holding this page
    int  accessTime;  // clock tick for last access
    int  loadTime;    // clock tick for last time loaded
    int  nPeeks;      // total number times this page read
    int  nPokes;      // total number times this page modified
    // TODO: add more fields here, if needed ...
} PTE;

// The virtual address space of the process is managed
//  by an array of Page Table Entries (PTEs)
// The Page Table is not directly accessible outside
//  this file (hence the static declaration)

static PTE *PageTable;      // array of page table entries
static int  nPages;         // # entries in page table
static int  replacePolicy;  // how to do page replacement
static int  fifoList;       // index of first PTE in FIFO list
static int  fifoLast;       // index of last PTE in FIFO list


// Forward refs for private functions


// initPageTable: create/initialise Page Table data structures

//personal add
//implement Queue with double links list
typedef struct QueueNode{
    int pageno; //page number
    struct QueueNode *next;
    struct QueueNode *prev;
}QueueNode;

typedef struct QueueRep{
    QueueNode *head; // ptr to first node
    QueueNode *tail;//ptr to last node
}QueueRep;

typedef struct QueueRep *Queue;
Queue newQueue();
void QueueJoin(Queue Q, int pageno);
int QueueLeave(Queue Q);
static int findVictim(int,Queue Q);
void showQueue(Queue Q);
void QueueMove(Queue Q, int pageno);


//static varible
static Queue q;
//

void initPageTable(int policy, int np)
{
    PageTable = malloc(np * sizeof(PTE));
    if (PageTable == NULL) {
        fprintf(stderr, "Can't initialise Memory\n");
        exit(EXIT_FAILURE);
    }
    replacePolicy = policy;
    nPages = np;
    fifoList = 0;
    fifoLast = nPages-1;
    q = newQueue();
    for (int i = 0; i < nPages; i++) {
        PTE *p = &PageTable[i];
        p->status = NOT_USED;
        p->modified = 0;
        p->frame = NONE;
        p->accessTime = NONE;
        p->loadTime = NONE;
        p->nPeeks = p->nPokes = 0;
   }
}

// requestPage: request access to page pno in mode
// returns memory frame holding this page
// page may have to be loaded
// PTE(status,modified,frame,accessTime,nextPage,nPeeks,nWrites)

int requestPage(int pno, char mode, int time)
{
    if (pno < 0 || pno >= nPages) {
        fprintf(stderr,"Invalid page reference\n");
        exit(EXIT_FAILURE);
    }
    
    PTE *p = &PageTable[pno];
    int fno; // frame number
    switch (p->status) {
    case NOT_USED:
    case ON_DISK:
        // TODO: add stats collection

        //when the page loaded, make the page to join into Queue, order by
        //loaded time, the Queue contain page number 
        //e.g. 5(1st loaded) 2(2nd) 3(3rd) 1(4th)
        //therefore(when no free frame): 2(2nd loaded) 3(3rd) 1(4th) 6(5th)
        //this Queue take NOT_used and on_disk page add to the end of Queue
        //we can assume this time in the Queue there are not duplicate page since
        //page is NOT_used and on_disk
        //can use for both strategrary IRU and FIFO
        QueueJoin(q,pno);
        
        countPageFault();
        fno = findFreeFrame();
        if (fno == NONE) {
            int vno = findVictim(time,q);
    #ifdef DBUG
    		
            printf("Evict page %d\n",vno);
    #endif
            // TODO:
            // if victim page modified, save its frame
            // collect frame# (fno) for victim page
            // update PTE for victim page
            // - new status
            // - no longer modified
            // - no frame mapping
            // - not accessed, not loaded
            PTE *p1 = &PageTable[vno];
            if(p1->modified == 1){
                saveFrame(vno);
            }
            fno = p1->frame;
            p1->status=ON_DISK;
            p1->modified = 0;
            p1->frame = NONE;
            //no frame mapping
            p1->accessTime = NONE;
            p1->loadTime = NONE;

        }
        printf("Page %d given frame %d\n",pno,fno);
        // TODO:
        // load page pno into frame fno
        // update PTE for page
        // - new status
        // - not yet modified
        // - associated with frame fno
        // - just loaded
        loadFrame(fno,pno,time);
        p->status=IN_MEMORY;
        //updata loadTime and frame number
        p->loadTime = time;
        p->frame = fno;
        break;
    case IN_MEMORY:
        // TODO: add stats collection
        // if already in memory, updata accesseTime
        p->accessTime = time;
        countPageHit();
        // if strategray is LRU, updata access time to the queue
        if(replacePolicy== REPL_LRU){
           //remove duplicate pageno in queue
            QueueMove(q,pno);
            //join agin in to queue at the tail
            QueueJoin(q,pno);
        }
        break;
    default:
        fprintf(stderr,"Invalid page status\n");
        exit(EXIT_FAILURE);
    }
    if (mode == 'r')
        p->nPeeks++;
    else if (mode == 'w') {
        p->nPokes++;
        p->modified = 1;
    }
    p->accessTime = time;
    return p->frame;
}

// findVictim: find a page to be replaced
// uses the configured replacement policy

static int findVictim(int time,Queue q)
{
    int victim = 0;
    switch (replacePolicy) {
    case REPL_LRU:
        victim = QueueLeave(q);
        break;
    case REPL_FIFO:
        victim = QueueLeave(q);
        break;
    case REPL_CLOCK:
        return 0;
    }
    return victim;
}

// showPageTableStatus: dump page table
// PTE(status,modified,frame,accessTime,nextPage,nPeeks,nWrites)

void showPageTableStatus(void)
{
    char *s;
    printf("%4s %6s %4s %6s %7s %7s %7s %7s\n",
            "Page","Status","Mod?","Frame","Acc(t)","Load(t)","#Peeks","#Pokes");
    for (int i = 0; i < nPages; i++) {
        PTE *p = &PageTable[i];
        printf("[%02d]", i);
        switch (p->status) {
        case NOT_USED:  s = "-"; break;
        case IN_MEMORY: s = "mem"; break;
        case ON_DISK:   s = "disk"; break;
        }
        printf(" %6s", s);
        printf(" %4s", p->modified ? "yes" : "no");
        if (p->frame == NONE)
            printf(" %6s", "-");
        else
            printf(" %6d", p->frame);
        if (p->accessTime == NONE)
            printf(" %7s", "-");
        else
            printf(" %7d", p->accessTime);
        if (p->loadTime == NONE)
            printf(" %7s", "-");
        else
            printf(" %7d", p->loadTime);
        printf(" %7d", p->nPeeks);
        printf(" %7d", p->nPokes);
        printf("\n");
    }
}


//function for fifo
//Queue for fifo
Queue newQueue()
{
	Queue q;
	q = malloc(sizeof(QueueRep));
	assert(q != NULL);
	q->head = NULL;
	q->tail = NULL;
	return q;
}
// add item at end of Queue 
void QueueJoin(Queue Q, int pageno)
{
	assert(Q != NULL);
	QueueNode *new = malloc(sizeof(QueueNode));
	assert(new != NULL);
	new->pageno = pageno;
    new->next = NULL;
    new->prev = NULL;


    //insertion
	if (Q->head == NULL){
        Q->head = new;
    }    
	if (Q->tail != NULL){
        Q->tail->next = new;
        new->prev = Q->tail;
    }
    Q->tail = new;
    
}
// remove item from front of Queue
int QueueLeave(Queue Q)
{
	assert(Q != NULL);
	assert(Q->head != NULL);
	int pageno = Q->head->pageno;
	QueueNode *old = Q->head;
    Q->head = old->next;
    if (Q->head == NULL){
        Q->tail = NULL;
    }else{
        //if q->head != NULL, updata q->head->prev
        Q->head->prev = NULL;
    }
    free(old);
	return pageno;
}
void showQueue(Queue Q)
{
	QueueNode *curr;
	assert(Q != NULL);
	// free list nodes
	curr = Q->head;
	while (curr != NULL) {
		fprintf(stderr,"%d",curr->pageno);
		if (curr->next != NULL)
			fprintf(stderr,">");
		curr = curr->next;
	}
	fprintf(stderr,"i have nothing\n");
}

//if the require page is in memory, remove the page from mmemory queue
void QueueMove(Queue Q, int pageno){
    
    assert(Q != NULL);
    //fprintf(stderr,"%d**************\n",Q->head->pageno);
    //case 1:require page at head
    assert(Q->head != NULL);
    if(Q->head->pageno == pageno){
        QueueNode *old = Q->head;
        Q->head = old->next;
        if (Q->head == NULL){
            Q->tail = NULL;
        }else{
            //if q->head != NULL, updata q->head->prev
            Q->head->prev = NULL;
        }
        free(old);
        return;
    }else if(Q->tail->pageno == pageno){
        //case 2:require page at tail
        QueueNode *old = Q->tail;
        Q->tail = Q->tail->prev;
        Q->tail->next = NULL;
        free(old);
        return;
    }

    //require page at middle
    QueueNode *curr;
    curr = Q->head->next;
    //avoid tail case
    while(curr->next != NULL){
        if(curr->pageno == pageno){
            QueueNode *old = curr;
            curr = curr->next;
            old->prev->next = curr;
            curr->prev = old->prev;
            free(old);
            break;
         }
        curr = curr->next;
    }
}
//end for function fifo


