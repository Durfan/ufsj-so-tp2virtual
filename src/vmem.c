#include "main.h"

int *iniMem(void) {
	int *vmem = calloc(g_config.frames,sizeof(int));
	if (vmem == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}
	return vmem;
}

int getframe(int *vmem) {
	int frame = getfreeframe(vmem);
	if (frame != -1)
		return frame;

	switch (g_config.salg) {
	case lru:
		/* code */
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

	return 0;
}

int getfreeframe(int *vmem) {
	unsigned frames = g_config.frames;
	for (unsigned i=0; i < frames/2; i++) {
		if (vmem[i] == 0)
			return i;
		if (vmem[(frames-1)-i] == 0)
			return (frames-1)-i;
	}
	return -1;
}

void algLRU(Pagtab *table) {

}