#include "./includes/main.h"

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
			printf("\n");
			barran = 0;
		}
		else
			printf(" \u2502");
	}
	printf("\n");
}

void clrReg(Registro *registro) {
	free(registro->access);
	free(registro);
}