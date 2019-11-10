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
		/* code */
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