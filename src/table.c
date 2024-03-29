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
	Pnode *pnode;
	unsigned hit = 0, fault = 0;
	unsigned count = 1;
	float percent;
	char btrw;

	printf("\e[?25l");
	for (unsigned i=0; i < registro->naccess; i++) {
		percent = (count*100) / g_config.inlines;
		addr  = registro->acesso[i].addr;
		btrw  = registro->acesso[i].rw ;
		addr  = getPaddr(addr);
		paddr = modHsh(addr);
		list  = table[paddr].lstaddr;
		pnode = schLst(list,addr);

		printf("  Processando Tabela: "CYELL);
		printf("[%03.0f%%] ", percent);
		if (pnode != NULL) {
			pnode->bitmod = btrw == 'W' ? true:false;
			printf("%04d \u2192 %08X : ",paddr,addr);
		}
		else {
			pnode = pshLst(list,addr);
			printf("%04d \u2192 %08X : ",paddr,addr);
		}

		if (pnode->frame == -1) {
			pnode->frame = getframe(table);
			printf("F%04d PF%d",pnode->frame,fault++);
		}
		else {
			hit++;
			pnode->count >>= 1;
		}
		
		printf("\r"CRSET);
		count++;
	}
	printf("\33[2K\r\e[?25h");
	printf("       Hit de Pagina: %d\n",hit);
	printf("     Falta de Pagina: %d\n",fault);
}

int tblSze(Pagtab *table) {
	int size = 0;
	List *list;
	for (unsigned i=0; i < g_config.frames; i++) {
		list = table[i].lstaddr;
		size += list->size;
	}
	return size;
}

Pnode *schLst(List *list, Addr paddr) {
	if (lstnil(list))
		return NULL;
	Pnode *pnode = NULL;
	Pnode *ptr = list->head;
	while (ptr != NULL) {
		if (ptr->paddr == paddr) {
			ptr->count += 0x080;
			ptr->bitref = true;
			pnode = ptr;
		}
		ptr = ptr->next;
	}

	if (pnode)
		return pnode;
	return NULL;
}

Pnode *pshLst(List *list, Addr paddr) {
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
	pnode->count = 0;
	pnode->next = list->head;
	list->head = pnode;
	list->size++;

	return pnode;
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