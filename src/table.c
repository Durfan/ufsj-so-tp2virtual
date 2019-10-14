#include "./includes/main.h"

int getdeloc(void) {
	unsigned s=0;
	unsigned desloc = g_config.pagsize;

	while (desloc > 1) {
		desloc >>= 1;
		s++;
	}

	return s;
}

int getPaddr(unsigned addr) {
	return addr >> g_config.s;
}

int getFaddr(unsigned addr) {
}

void prtAddr(Registro *registro) {
	int barran = 0;
	Access *access = registro->access;
	for (int i=0; i < registro->naccess; i++) {
		printf(" %08x \u2192", access[i].addr);
		printf(" %08x", getPaddr(access[i].addr));
		barran++;
		if (barran > 2) {
			putchar(0x0A);
			barran = 0;
		}
		else
			printf(" \u2502");
	}
	putchar(0x0A);
}