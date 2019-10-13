#include "./includes/main.h"

Subalg str2enum(const char *str) {
	for (int i=0; i < (int)(sizeof(g_polstr)/sizeof(g_polstr[0])); ++i)
		if (strcmp (str,g_polstr[i].str) == 0)
			return g_polstr[i].val;
	printf(PROGRAM": Politica de substituicao invalida\n");
	puts("USO: ./"PROGRAM" [polsub] [arquivo] [pagsize] [memsize]");
	printf("[polsub]: ");
	for (int i=0; i < (int)(sizeof(g_polstr)/sizeof(g_polstr[0])); ++i)
		printf("%s ", g_polstr[i].str);
	putchar(0x0A);
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

int valSize(int val, int min, int max) {
	if (powrOf2(val) == 0) {
		printf(PROGRAM": '%d' Tamanho invalido\n", val);
		puts("Tamanhos validos: 2^x | x > 0");
		exit(EXIT_FAILURE);
	}
	else if (val < min || val > max) {
		printf(PROGRAM": '%d' Tamanho invalido\n", val);
		printf("Tamanhos validos: x | x >= %d, x <= %d\n", min, max);
		exit(EXIT_FAILURE);
	}
	return 0;
}

int powrOf2(int val) {
	return val && !(val & (val - 1));
}