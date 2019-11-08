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

void insTbl(Pagtab *table, unsigned addr) {
	int paddr = modHsh(addr);
	static int count = 0;
	List *list = table[paddr].lstaddr;
	if (schLst(list,addr)) {
		// hit,sub,etc
	}
	else {
		printf("%05d -> %04d:%08x\n", count++, paddr, addr);
		pshLst(list,addr);
	}
}

bool schLst(List *list, unsigned addr) {
	if (lstnil(list))
		return false;
	bool inlst = false;
	Node *ptr = list->head;
	while (ptr != NULL) {
		if (ptr->addr == addr)
			inlst = true;
		ptr = ptr->next;
	}
	return inlst;
}

void prtTbl(Pagtab *table) {
	int frames = tblesze();
	for (int i=0; i < frames; i++) {
		prtLst(table[i].lstaddr);
	}
	putchar(0x0A);
}

void clrTbl(Pagtab *table) {
	int frames = tblesze();
	for (int i=0; i < frames; i++)
		clrLst(table[i].lstaddr);
	free(table);
}

int modHsh(unsigned addr) {
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

void pshLst(List *list, unsigned addr) {
	Node *node = malloc(sizeof(Node));
	if (node == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}
	node->addr = addr;
	node->next  = list->head;
	list->head  = node;
	list->size++;
}

void prtLst(List *list) {
	if (lstnil(list))
		return;
	//Node *ptr = list->head;
	printf("%d ", list->size);
/* 	while (ptr != NULL) {
		printf (" %08x", ptr->addr);
		ptr = ptr->next;
	} */
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