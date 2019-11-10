#include "main.h"

Deque *dqcreate(void) {
	Deque *deque = malloc(sizeof(Deque));
	if (deque == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}

	deque->head = deque->tail = NULL;
	deque->size = 0;
	return deque;
}

void dqpshHead(Deque *deque, Pnode *pnode) {
	DQnode *dqnode = malloc(sizeof(DQnode));
	if (dqnode == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}

	dqnode->pnode = pnode;
	dqnode->next = deque->head;
	dqnode->prev = NULL;
	if (deque->tail == NULL) {
		deque->head = deque->tail = dqnode;
	} else {
		deque->head->prev = dqnode;
		deque->head = dqnode;
	}
	deque->size++;
}

void dqpshTail(Deque *deque, Pnode *pnode) {
	DQnode *dqnode = malloc(sizeof(DQnode));
	if (dqnode == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}

	dqnode->pnode = pnode;
	dqnode->prev = deque->tail;
	dqnode->next = NULL;
	if (deque->head == NULL) {
		deque->head = deque->tail = dqnode;
	} else {
		deque->tail->next = dqnode;
		deque->tail = dqnode;
	}
	deque->size++;
}

Pnode *dqpopHead(Deque *deque) {
	Pnode *pnode = deque->head->pnode;
	DQnode *dqnode = deque->head;

	if (deque->head == deque->tail)
		deque->head = deque->tail = NULL;
	else
		deque->head = dqnode->next;

	deque->size--;
	free(dqnode);
	return pnode;
}

Pnode *dqpopTail(Deque *deque) {
	Pnode *pnode = deque->tail->pnode;
	DQnode *dqnode = deque->tail;

	if (deque->head == deque->tail)
		deque->head = deque->tail = NULL;
	else {
		deque->tail = dqnode->prev;
		deque->tail->next = NULL;
	}

	deque->size--;
	free(dqnode);
	return pnode;
}

Pnode *dqpekHead(Deque *deque) {
	return deque->head ? deque->head->pnode : NULL;
}

Pnode *dqpekTail(Deque *deque) {
	return deque->tail ? deque->tail->pnode : NULL;
}

void dqprt(Deque *deque) {
	if (dqEmpty(deque))
		return;

	DQnode *dqnode = deque->head;
	printf(" S{%04d}:", deque->size);
	while (dqnode != NULL) {
		printf(" %08X", dqnode->pnode->paddr);
		dqnode = dqnode->next;
	}
	putchar(0x0A);
}

void dqclr(Deque *deque) {
	if (dqEmpty(deque)) {
		free(deque);
		return;
	}

	DQnode *delete;
	while (deque->head != NULL) {
		delete = deque->head;
		deque->head = deque->head->next;
		free(delete);
	}

	free(deque);
}

bool dqEmpty(Deque *deque) {
	return deque->head == NULL;
}