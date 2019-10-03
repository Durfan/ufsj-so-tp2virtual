#include "./includes/main.h"

Queue *inique(void) {
	Queue *queue = malloc(sizeof(Queue));
	assert(queue);

	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;

	return queue;
}

void prtqeue(Queue *queue) {
	if (quEmpty(queue))
		return;

	int line = 0;
	Node *node = queue->head;
	while (node) {
		if (!line)
			printf(" \u2502");
		printf(" %08x %c \u2502", node->data.addr, node->data.rw);
		line++;
		if (line > 4) {
			printf("\n");
			line = 0;
		}
		node = node->next;
	}
	printf(" \u2514 Queue Size: %ld\n", queue->size);
}

void enqueue(Queue *queue, Data data) {
	Node *node = malloc(sizeof(Node));
	assert(node);

	node->data = data;
	node->next = NULL;

	if (!queue->head && !queue->tail) {
		queue->head = queue->tail = node;
		queue->size++;
		return;
	}

	queue->tail->next = node;
	queue->tail = node;
	queue->size++;
}

void dequeue(Queue *queue) {
	if (quEmpty(queue))
		error(1,1,"Fila vazia");

	Node *node = queue->head;

	if (queue->head == queue->tail)
		queue->head = queue->tail = NULL;
	else
		queue->head = queue->head->next;

	queue->size--;
	free(node);
}

Data gethead(Queue *queue) {
	if (quEmpty(queue))
		error(1,1,"Fila vazia");

	Data data = queue->head->data;
	return data;
}

bool quEmpty(Queue *queue) {
	return queue->head == NULL;
}