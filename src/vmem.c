#include "main.h"

int *iniMem(void) {
	int *vmem = calloc(g_config.frames,sizeof(int));
	if (vmem == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}
	return vmem;
}

int getframe(Pagtab *table, int *vmem) {
	int frame = getfreeframe(vmem);
	if (frame != -1)
		return frame;

	switch (g_config.salg) {
	case lru:
		frame = algLRU(table,vmem);
		break;

	case nru:
		/* code */
		break;

	case segunda_chance:
		/* code */
		break;
	
	default:
		break;
	}

	return frame;
}

int getfreeframe(int *vmem) {
	unsigned frames = g_config.frames;
	for (unsigned i=0; i < frames; i++) {
		if (vmem[i] == 0) {
			vmem[i] = 1;
			return i;
		}
	}
	return -1;
}

int algLRU(Pagtab *table, int *vmem) {
	unsigned frames = g_config.frames;
	int min = INT_MAX;
	int frame,count;
	List *list;
	Pnode *pnode,*fnode;

	for (unsigned i=0; i < frames; i++) {
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