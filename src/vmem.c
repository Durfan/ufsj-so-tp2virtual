#include "main.h"

int *iniMem(void) {
	int *vmem = calloc(g_config.frames,sizeof(int));
	if (vmem == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}
	return vmem;
}

int getfreeframe(int *mem){
	unsigned frames = g_config.frames;
	for (unsigned i=0; i < frames/2; i++) {
		if (mem[i] == 0)
			return i;
		if (mem[(frames-1)-i] == 0)
			return (frames-1)-i;
	}
	return -1;
}