#include "main.h"

Pagtab *iniTbl(void) {
	Addr frames = g_config.frames;
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
		addr = getPaddr(addr);
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
	Pnode *ptr = list->head;
	while (ptr != NULL) {
		if (ptr->paddr == paddr)
			inlst = true;
		ptr = ptr->next;
	}
	return inlst;
}

void clrTbl(Pagtab *table) {
	unsigned frames = g_config.frames;
	for (unsigned i=0; i < frames; i++)
		clrLst(table[i].lstaddr);
	free(table);
}

unsigned modHsh(Addr addr) {
	return addr % g_config.frames;
}

void pshLst(List *list, Addr paddr) {
	Pnode *pnode = malloc(sizeof(Pnode));
	if (pnode == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}
	pnode->paddr = paddr;
	pnode->frame = -1;
	pnode->bitres = false;
	pnode->bitmod = false;
	pnode->bitref = false;
	pnode->next  = list->head;
	list->head  = pnode;
	list->size++;
}

void clrLst(List *list) {
	if (list->head == NULL) {
		free(list);
		return;
	}
	Pnode *delNode;
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