#include "main.h"

Pagtab *iniTbl(void) {
	int frames = tblesze();
	Pagtab *table = malloc(frames * sizeof(Pagtab));
	if (table == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}

	for (int i=0; i < frames; i++)
		table[i].lstaddr = iniLst();

	return table;
}

List *iniLst(void) {
	List *list = malloc(sizeof(List));
	if (list == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}
	list->size = 0;
	list->head = NULL;
	return list;
}

void insTbl(Pagtab *table, int addr) {
	int paddr = modHsh(addr);
	pshLst(table[paddr].lstaddr,addr);
}

void prtTbl(Pagtab *table) {
	int frames = tblesze();
	for (int i=0; i < frames; i++)
		prtLst(table[i].lstaddr);
}

void clrTbl(Pagtab *table) {
	int frames = tblesze();
	for (int i=0; i < frames; i++)
		clrLst(table[i].lstaddr);
}

int modHsh(int addr) {
	addr >>= g_config.pgdeslc;
	return addr % tblesze();
}

int tblesze(void) {
	int pgdeslc = g_config.pgdeslc;
	size_t size = g_config.memsize;
	size <<= 0x00A;
	size >>= pgdeslc;
	return size;
}

void pshLst(List *list, int paddr) {
	Node *node = malloc(sizeof(Node));
	if (node == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}
	node->paddr = paddr;
	node->next  = list->head;
	list->head  = node;
	list->size++;
}

void prtLst(List *list) {
	if (lstnil(list)) return;
	Node *ptr = list->head;
	while (ptr != NULL) {
		printf (" %08x", ptr->paddr);
		ptr = ptr->next;
	}
	putchar(0x0A);
}

void clrLst(List *list) {
	if (list->head == NULL) {
		free(list);
		return;
	}
	Node *delNode;
	while (list->head != NULL) {
		delNode = list->head;
		list->head = list->head->next;
		free(delNode);
	}
	free(list);
}

int lstnil(List *list) {
	return (list->head == NULL);
}