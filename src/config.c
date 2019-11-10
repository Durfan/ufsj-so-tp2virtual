#include "main.h"

Subalg str2enum(const char *str) {
	char *app = program_invocation_short_name;
	for (int i=0; i < (int)(sizeof(g_polstr)/sizeof(g_polstr[0])); ++i)
		if (strcmp(str,g_polstr[i].str) == 0)
			return g_polstr[i].val;
	printf("%s: Politica de substituicao invalida\n", app);
	printf("USO: ./%s [polsub] [arquivo] [pagsize] [memsize]", app);
	printf("[polsub]: ");
	for (int i=0; i < (int)(sizeof(g_polstr)/sizeof(g_polstr[0])); ++i)
		printf("%s ", g_polstr[i].str);
	putchar(0x0A);
	exit(EXIT_FAILURE);
}

void setCfg(char **argv) {
	unsigned pagsize = atoi(argv[3]);
	valSize(pagsize,2,64);
	unsigned memsize = atoi(argv[4]);
	valSize(memsize,128,16384);
	unsigned desloc = getdeslc(pagsize);
	unsigned frames = tablesze(desloc,memsize);

	g_config.salg = str2enum(argv[1]);
	g_config.file = argv[2];
	g_config.filesiz = 0;
	g_config.pagsize = pagsize;
	g_config.memsize = memsize;
	g_config.pgdeslc = desloc;
	g_config.frames  = frames;
}

unsigned getdeslc(unsigned size) {
	unsigned deslc;
	unsigned shift = size << 0x00A;
	for (deslc=0; shift > 1; deslc++)
		shift >>= 1;
	return deslc;
}

unsigned tablesze(unsigned pgdeslc, unsigned memsize) {
	unsigned frames = memsize;
	frames <<= 0x00A;
	frames >>= pgdeslc;
	return frames;
}

unsigned getPaddr(Addr addr) {
	return addr >> g_config.pgdeslc;
}

unsigned valSize(unsigned val, unsigned min, unsigned max) {
	char *app = program_invocation_short_name;
	if (powrOf2(val) == 0) {
		printf("%s: tam(%d): Argumento invalido\n", app, val);
		printf("validos: tam(x) = log\u2082n | ");
		printf("%d \u2265 tam(x) \u2264 %d\n", min, max);
		exit(EXIT_FAILURE);
	}
	else if (val < min || val > max) {
		printf("%s: tam(%d): Argumento invalido\n", app, val);
		printf("validos: %d \u2265 tam(x) \u2264 %d\n", min, max);
		exit(EXIT_FAILURE);
	}
	return 0;
}

// n e potencia de 2 ? sim:nao
unsigned powrOf2(unsigned n) {
	return n && !(n & (n - 1));
}

// round() math.h, mas sem a math.h
int nofloat(double n) {
	return (n >= 0) ? (int)(n + 0.5) : (int)(n - 0.5);
}