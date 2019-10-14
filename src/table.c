#include "./includes/main.h"

int getdeslc(void) {
	unsigned deslc;
	unsigned shift = g_config.pagsize;
	for (deslc=0; shift > 1; deslc++)
		shift >>= 1;
	return deslc;
}

int getPaddr(unsigned addr) {
	return addr >> g_config.pgdeslc;
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