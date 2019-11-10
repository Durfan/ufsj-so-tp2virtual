#include "main.h"

int getframe(Pagtab *table, Deque *deque) {
	int frame;
	static unsigned mem;
	if (mem < g_config.frames) {
		frame = mem++;
		return frame;
	}

	switch (g_config.salg) {
	case lru:
		frame = algLRU(table);
		break;

	case nru:
		frame = algNRU(table);
		break;

	case segunda_chance:
		frame = algSC(deque);
		break;
	
	default:
		exit(EXIT_FAILURE);
	}
	return frame;
}

int algLRU(Pagtab *table) {
	int min = INT_MAX;
	int frame, count;
	List *list;
	Pnode *pnode,*fnode;

	for (unsigned i=0; i < g_config.frames; i++) {
		list = table[i].lstaddr;
		pnode = list->head;
		while (pnode != NULL) {
			count = pnode->count;
			frame = pnode->frame;
			if (count < min && frame != -1) {
				min = count;
				fnode = pnode;
			}
			pnode = pnode->next;
		}
	}

	frame = fnode->frame;
	fnode->frame = -1;
	return frame;
}

int algNRU(Pagtab *table) {
	static unsigned ciclo;
	unsigned reset = 20;
	int frame, cls;
	List *list;
	Pnode *pnode,*fnode;
	Deque *cls01 = dqcreate();
	Deque *cls23 = dqcreate();
	
	for (unsigned i=0; i < g_config.frames; i++) {
		list = table[i].lstaddr;
		pnode = list->head;
		while (pnode != NULL) {
			frame = pnode->frame;
			if (ciclo == reset)
				pnode->bitref = false;
			cls = clssNRU(pnode);
			if (cls == 0 && frame != -1)
				dqpshHead(cls01,pnode);
			else if (cls == 1 && frame != -1) 
				dqpshTail(cls01,pnode);
			else if (cls == 2 && frame != -1)
				dqpshHead(cls23,pnode);
			else if (cls == 3 && frame != -1)
				dqpshTail(cls23,pnode);
			pnode = pnode->next;
		}
	}

	if (dqEmpty(cls01) == 0)
		fnode = dqpopHead(cls01);
	else
		fnode = dqpopHead(cls23);

	cls = clssNRU(fnode);
	prtCLS(cls);
	frame = fnode->frame;
	fnode->frame = -1;

	if (ciclo == reset)
		ciclo = 0;
	else
		ciclo++;

	dqclr(cls01);
	dqclr(cls23);
	return frame;
}

int clssNRU(Pnode *pnode) {
	int class;
	if (!pnode->bitref && !pnode->bitmod)
		class = 0;
	else if (!pnode->bitref && pnode->bitmod)
		class = 1;
	else if (pnode->bitref && !pnode->bitmod)
		class = 2;
	else if (pnode->bitref && pnode->bitmod)
		class = 3;
	else class = -1;
	return class;
}

void prtCLS(int class) {
	printf("CLS");
	switch (class) {
	case 0:
		printf("0\u25CF\u25CF\u25CF ");
		break;
	case 1:
		printf("\u25CF1\u25CF\u25CF ");
		break;
	case 2:
		printf("\u25CF\u25CF2\u25CF ");
		break;
	case 3:
		printf("\u25CF\u25CF\u25CF3 ");
		break;
	default:
		break;
	}
}


int algSC(Deque *deque) {
    DQnode *dqnode = deque->head;
	Pnode *node;
	int frame;
	int control = 0;
	if(deque->head == NULL)
		printf("falha total\n");
    while(dqnode!=NULL && control == 0){
        if(dqnode->pnode->bitref == 1){
			node = dqnode->pnode;
			dqpopHead(deque);
			dqpshTail(deque, node);
			deque->tail->pnode->bitref = 0;
			dqnode = deque->head;
        }
        else if(dqnode->pnode->bitref == 0){
			frame = dqnode->pnode->frame;
			dqnode->pnode->frame = -1;
			dqpopHead(deque);
			control = 1;
		}
		else if(dqnode == deque->tail){
			frame = deque->head->pnode->frame;
			deque->head->pnode->frame = -1;
			dqpopHead(deque);
		}			
        dqnode = dqnode->next;
    }
    return frame;
}