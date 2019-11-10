#include "main.h"

int getframe(Pagtab *table) {
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
		/* code */
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
	printf("Classe %d ", cls);
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