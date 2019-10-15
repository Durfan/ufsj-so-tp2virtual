#include "includes/main.h"

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

void setCfg(char **argv) {
	int pagsize = atoi(argv[3]);
	valSize(pagsize,2,64);
	int memsize = atoi(argv[4]);
	valSize(memsize,128,16384);

	g_config.salg = str2enum(argv[1]);
	g_config.file = argv[2];
	g_config.pagsize = pagsize << 0x00A;
	g_config.memsize = memsize << 0x00A;
	g_config.pgdeslc = getdeslc();
}

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