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

void execRG(Pagtab *table, Registro *registro) {
	Addr addr,paddr;
	List *list;
	unsigned count = 1;
	float percent;

	printf("\e[?25l");
	for (unsigned i=0; i < registro->naccess; i++) {
		percent = (count*100) / (g_config.filesiz/11);
		addr = registro->acesso[i].addr;
		addr >>= g_config.pgdeslc;
		paddr = modHsh(addr);
		list = table[paddr].lstaddr;

		printf("  Processando Tabela: "CYELL);
		if (schLst(list,addr)) {
			printf("[%03.0f%%] ",percent);
			printf("%04d \u2192 %08X\r",paddr,addr);
		}
		else {
			printf("[%03.0f%%] ",percent);
			printf("%04d \u2192 %08X\r",paddr,addr);
			pshLst(list,addr);
		}
		printf(CRSET);
		count++;
	}
	printf("\33[2K\r\e[?25h");
}

bool schLst(List *list, Addr paddr) {
	if (lstnil(list))
		return false;
	bool inlst = false;
	Node *ptr = list->head;
	while (ptr != NULL) {
		if (ptr->paddr == paddr)
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
	return addr % tblesze();
}

unsigned tblesze(void) {
	int pgdeslc = g_config.pgdeslc;
	size_t size = g_config.memsize;
	size <<= 0x00A;
	size >>= pgdeslc;
	return size;
}

void pshLst(List *list, Addr paddr) {
	Node *node = malloc(sizeof(Node));
	if (node == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}
	node->paddr = paddr;
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