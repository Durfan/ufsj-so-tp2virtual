#include "main.h"

void prtReg(Registro *registro) {
	int column = 0;
	Access *acesso = registro->acesso;
	for (unsigned i=0; i < registro->naccess; i++) {
		column += printf(" %08x %c", acesso[i].addr, acesso[i].rw);
		if (column%5 == 0)
			putchar(0x0A);
		else
			printf(" \u2502");
	}
}

void prtTbl(Pagtab *table) {
	int frames = tblesze();
	for (int i=0; i < frames; i++) {
		prtLst(table[i].lstaddr);
	}
	putchar(0x0A);
}

void prtLst(List *list) {
	if (lstnil(list))
		return;
	//Node *ptr = list->head;
	printf("%ld ", list->size);
/* 	while (ptr != NULL) {
		printf (" %08x", ptr->addr);
		ptr = ptr->next;
	} */
}