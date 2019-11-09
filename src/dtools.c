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
	int frames = g_config.frames;
	int column = 0;
	unsigned lstsze;
	printf("-DEBUG: Distribuicao\n");
	for (int i=0; i < frames; i++) {
		lstsze = table[i].lstaddr->size;
		printf("L%04d:",i);
		printf("%04d ",lstsze);
		if (column > 5) {
			putchar(0x0A);
			column = 0;
		}
		else
			column++;
	}
	putchar(0x0A);
}