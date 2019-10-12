#include "./includes/main.h"

Registro *iniQueue(int naccess) {
	Registro *registro = malloc(sizeof(Registro));
	if (registro == NULL) {
		perror(PROGRAM);
		exit(EXIT_FAILURE);
	}

	registro->naccess = naccess;
	registro->access = malloc(naccess * sizeof(Access));
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

		if (!barran)
			printf(" \u2502");

		printf(" %08x %c \u2502", access[i].addr, access[i].rw);
		barran++;

		if (barran > 4) {
			printf("\n");
			barran = 0;
		}
	}
}

void clrReg(Registro *registro) {
	free(registro->access);
	free(registro);
}