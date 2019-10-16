#include "includes/main.h"

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

	memset(memory->msim,-1,sizeof(memsize));
	memory->front = -1;
	memory->rear = -1;
	return memory;
}

int enqueue(Memory *mem, int val) {
	if ((mem->rear+1) % mem->frames == mem->front)
		return -1;
	else if (isEmpty(mem)) {
		mem->front =0;
		mem->rear = 0;
	}
	else
		mem->rear = (mem->rear+1) % mem->frames;
	mem->msim[mem->rear] = val;
	return 0;
}

int dequeue(Memory *mem) {
	if (isEmpty(mem))
		return -1;
	else if (mem->front == mem->rear) {
		mem->front = -1;
		mem->rear = -1;
	}
	else
		mem->front = (mem->front+1) % mem->frames;
	return 0;
}

void prtmem(Memory *mem) {
	printf("Memoria:\u2595");
	for (int i=0; i < mem->frames; i++)
		printf("\u2592");
	printf("\u258F\n");
}

int isEmpty(Memory *mem) {
	return (mem->front == -1 && mem->rear == -1) ? 1 : 0;
}