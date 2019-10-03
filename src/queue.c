#include "./includes/main.h"

Queue *inique(void) {
	Queue *queue = malloc(sizeof(Queue));
	if (queue == NULL) {
		perror("inique");
		exit(EXIT_FAILURE);
	}

	queue->head = NULL;
	queue->tail = NULL;
	queue->size = 0;

	return queue;
}

Data gethead(Queue *queue) {
	if (quEmpty(queue)) {
		perror("gethead");
		free(queue);
		exit(EXIT_FAILURE);
	}

	Data data = queue->head->data;
	return data;
}

void prtqeue(Queue *queue) {
	if (quEmpty(queue)) {
		perror("prtqeue");
		return;
	}

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
	if (node == NULL) {
		perror("enqueue");
		queFree(queue);
		exit(EXIT_FAILURE);
	}

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
	if (quEmpty(queue)) {
		perror("dequeue");
		free(queue);
		exit(EXIT_FAILURE);
	}

	Node *node = queue->head;

	if (queue->head == queue->tail)
		queue->head = queue->tail = NULL;
	else
		queue->head = queue->head->next;

	queue->size--;
	free(node);
}

void queFree(Queue *queue) {

	while (!quEmpty(queue)) {
		dequeue(queue);
	}

	free(queue);
}

bool quEmpty(Queue *queue) {
	if (queue->head == NULL) {
		errno = EFAULT;
		return true;
	}
	return false;
}