#ifndef _QUEUE_H
#define _QUEUE_H

typedef struct data_t {
	unsigned addr;
	char rw;
} Data;

typedef struct node_t {
	struct data_t data;
	struct node_t *next;
} Node;

typedef struct queue_t {
	struct node_t *head;
	struct node_t *tail;
	size_t size;
} Queue;

Queue *inique(void);
Data gethead(Queue *queue);
void prtqeue(Queue *queue);
void enqueue(Queue *queue, Data data);
void dequeue(Queue *queue);
void queFree(Queue *queue);
bool quEmpty(Queue *queue);

#endif // _QUEUE_H