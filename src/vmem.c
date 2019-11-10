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
			if (count < min && pnode->frame != -1) {
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
	int frame,class;
	List *list;
	Pnode *pnode,*fnode;
	bool getfrm = false;
	
	for (unsigned i=0; i < g_config.frames; i++) {
		list = table[i].lstaddr;
		pnode = list->head;
		while (pnode != NULL) {
			if (ciclo == reset)
				pnode->bitref = false;

			class = clssNRU(pnode);
			if (!getfrm && pnode->frame != -1) {
				switch (class) {
				case 0:
					getfrm = true;
					fnode = pnode;
					break;

				case 1:
					getfrm = true;
					fnode = pnode;
					break;

				case 2:
					getfrm = true;
					fnode = pnode;
					break;

				case 3:
					getfrm = true;
					fnode = pnode;
					break;

				default:
					exit(EXIT_FAILURE);
				}
				
			}
			pnode = pnode->next;
		}
	}

	class = clssNRU(fnode);
	printf("Classe %d ", class);
	frame = fnode->frame;
	fnode->frame = -1;

	if (ciclo == reset)
		ciclo = 0;
	else
		ciclo++;

	return frame;
}

int clssNRU(Pnode *pnode) {
	int class;
	if (!pnode->bitref && !pnode->bitmod)
		class = 0;
	else if (!pnode->bitref &&  pnode->bitmod)
		class = 1;
	else if (pnode->bitref && !pnode->bitmod)
		class = 2;
	else if (pnode->bitref &&  pnode->bitmod)
		class = 3;
	else class = -1;
	return class;
}