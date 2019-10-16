#ifndef INCLUDE_DS_MEMSIM_H
#define INCLUDE_DS_MEMSIM_H

typedef struct mem_t {
	int *msim;
	int frames;
	int front;
	int rear;
} Memory;

Memory *simmem(void);
int enqueue(Memory *mem, int val);
int dequeue(Memory *mem);
void prtmem(Memory *mem);
int isEmpty(Memory *mem);

//#pragma message __FILE__
#endif // INCLUDE_DS_MEMSIM_H