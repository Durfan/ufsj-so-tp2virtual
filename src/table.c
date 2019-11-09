#include "main.h"

Pagtab *iniTbl(void) {
	Addr frames = tblesze();
	Pagtab *table = malloc(frames * sizeof(Pagtab));
	if (table == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}

	for (unsigned i=0; i < frames; i++)
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

void insTbl(Pagtab *table, Addr addr) {
	Addr paddr = modHsh(addr);
	static unsigned count = 0;
	static float percent;
	percent = (count*100) / (g_config.filesiz/11);
	List *list = table[paddr].lstaddr;
	printf("  Processando Tabela: "CYELL);
	if (schLst(list,addr)) {
		printf("[%03.0f%%] ", percent);
		printf("%04d \u2192 %08X\r", paddr, addr);
	}
	else {
		printf("[%03.0f%%] ", percent);
		printf("%04d \u2192 %08X\r", paddr, addr);
		pshLst(list,addr);
	}
	printf(CRSET);
	count++;
}

bool schLst(List *list, Addr addr) {
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

void clrTbl(Pagtab *table) {
	Addr frames = tblesze();
	for (unsigned i=0; i < frames; i++)
		clrLst(table[i].lstaddr);
	free(table);
}

int modHsh(Addr addr) {
	addr >>= g_config.pgdeslc;
	return addr % tblesze();
}

unsigned tblesze(void) {
	int pgdeslc = g_config.pgdeslc;
	size_t size = g_config.memsize;
	size <<= 0x00A;
	size >>= pgdeslc;
	return size;
}

void pshLst(List *list, Addr addr) {
	Node *node = malloc(sizeof(Node));
	if (node == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}
	node->addr = addr;
	node->frame = -1;
	node->bitres = false;
	node->bitmod = false;
	node->bitref = false;
	node->next  = list->head;
	list->head  = node;
	list->size++;
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