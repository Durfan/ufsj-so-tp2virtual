#include "./includes/main.h"

Subalg str2enum(const char *str) {
	for (int i=0; i < (int)(sizeof(g_polstr)/sizeof(g_polstr[0])); ++i)
		if (strcmp (str,g_polstr[i].str) == 0)
			return g_polstr[i].val;
	puts("Politica de substituicao invalida.");
	exit(EXIT_FAILURE);
}

Registro *iniQueue(int naccess) {
	Registro *registro = malloc(sizeof(Registro));
	if (registro == NULL) {
		perror(PROGRAM);
		exit(EXIT_FAILURE);
	}

	registro->naccess = naccess;
	registro->alocmem = naccess * sizeof(Access);
	registro->access = malloc(registro->alocmem);
	if (registro->access == NULL) {
		perror(PROGRAM);
		exit(EXIT_FAILURE);
	}

	return registro;
}

void prtReg(Registro *registro) {
	int barran = 0;
	Access *access = registro->access;
	for (int i=0; i < registro->naccess; i++) {
		printf(" %08x %c", access[i].addr, access[i].rw);
		barran++;
		if (barran > 5) {
			putchar(0x0A);
			barran = 0;
		}
		else
			printf(" \u2502");
	}
	putchar(0x0A);
}

void clrReg(Registro *registro) {
	free(registro->access);
	free(registro);
}

int powerOf2(int x) {
	return x && !(x & (x - 1));
}