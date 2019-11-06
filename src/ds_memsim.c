#include "main.h"

Memory *simmem(void) {
	Memory *memory = malloc(sizeof(Memory));
	if (memory == NULL) {
		perror(PROGRAM);
		exit(EXIT_FAILURE);
	}

	memory->frames = g_config.memsize << 0x00A;
	memory->frames >>= g_config.pgdeslc;
	size_t memsize = memory->frames * sizeof(int);

	memory->msim = malloc(memsize);
	if (memory->msim == NULL) {
		perror(PROGRAM);
		exit(EXIT_FAILURE);
	}

	memset(memory->msim,-1,memsize);
	memory->first = 0;
	memory->last = 0;
	return memory;
}

int enqueue(Memory *mem, int val) {
	if ((mem->last+1) % mem->frames == mem->first)
		return -1;
	else {
		int next = (mem->last + 1) % mem->frames;
		mem->msim[mem->last] = val;
		mem->last = next;
	}

	return 0;
}

int dequeue(Memory *mem) {
	if (isEmpty(mem))
		return -1;
	
	int pickn = mem->msim[mem->first];
	
	if (mem->first == mem->last) {
		mem->first = 0;
		mem->last = 0;
	}
	else {
		int next = (mem->first + 1) % mem->frames;
		mem->first = next;
	}

	return pickn;
}

void prtmem(Memory *mem) {
	printf("Memoria:\u2595");
	for (int i=0; i < mem->frames; i++)
		printf("\u2592");
	printf("\u258F\n");

	for (int i=0; i < mem->frames; i++)
		printf("%d ", mem->msim[i]);
	printf("\u258F\n");
}

int isEmpty(Memory *mem) {
	return (mem->first == -1 && mem->last == -1) ? 1 : 0;
}