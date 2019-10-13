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

void setCfg(char **argv) {
	int pagsize = atoi(argv[3]);
	valSize(pagsize,2,64);
	int memsize = atoi(argv[4]);
	valSize(memsize,128,16384);

	g_config.salg = str2enum(argv[1]);
	g_config.file = argv[2];
	g_config.pagsize = pagsize << 0x00A;
	g_config.memsize = memsize << 0x00A;
	g_config.s = getdeloc();
}

int valSize(int val, int min, int max) {
	if (powrOf2(val) == 0) {
		printf(PROGRAM": tam(%d): Argumento invalido\n", val);
		printf("validos: tam(x) = log\u2082n | ");
		printf("%d \u2265 tam(x) \u2264 %d\n", min, max);
		exit(EXIT_FAILURE);
	}
	else if (val < min || val > max) {
		printf(PROGRAM": tam(%d): Argumento invalido\n", val);
		printf("validos: %d \u2265 tam(x) \u2264 %d\n", min, max);
		exit(EXIT_FAILURE);
	}
	return 0;
}

int powrOf2(int val) {
	return val && !(val & (val - 1));
}