#include "main.h"
#include <sys/time.h>

void appinfo(void);
void prtFOOclk(struct timeval tv1, struct timeval tv2);
double ftempo(struct timeval tv1, struct timeval tv2);

int main(int argc, char **argv) {

	setlocale(LC_ALL,"");
	struct timeval tv1, tv2;

	if (argc != 5) {
		printf("%s: %s\n", program_invocation_short_name, strerror(EINVAL));
		printf("USO: %s [polsub] [arquivo] [pagsize] [memsize]\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	setCfg(argv);
	system("clear");
	printf(CYELL"%s [%s %s]\n"CRSET,
		program_invocation_short_name,VERSION,TAG);
	Registro *registro = readlog();
	Pagtab *table = iniTbl();
	appinfo();

	gettimeofday(&tv1,NULL);
		execRG(table,registro);
	gettimeofday(&tv2,NULL);

	prtFOOclk(tv1,tv2);
	
	#ifdef DEBUG
	prtTbl(table);
	printf("Deslocamento p: %d\n", g_config.pgdeslc);
	printf("Memoria usada: %d Kib\n", registro->alocmem / 128);
	#endif

	clrReg(registro);
	clrTbl(table);
	return EXIT_SUCCESS;
}

void appinfo(void) {
	printf("  Tamanho da memoria: %d Bytes", (g_config.memsize << 0x00A) / 8);
	printf(" (%d KiB/", g_config.memsize);
	printf("%g MiB)\n", (float)g_config.memsize / 1024);
	printf("  Frames disponiveis: %d\n", g_config.frames);
	printf(" Tamanho das paginas: %d Bytes", (g_config.pagsize << 0x00A) / 8);
	printf(" (%d KiB)\n", g_config.pagsize);
	printf("Tecnica de reposicao: %s\n", g_polstr[g_config.salg].str);
}

void prtFOOclk(struct timeval tv1, struct timeval tv2) {
	printf("      Tempo Execucao: %fs\n", ftempo(tv1,tv2));
}

double ftempo(struct timeval tv1, struct timeval tv2) {
	return (double)(tv2.tv_usec - tv1.tv_usec)/1000000 +
		   (double)(tv2.tv_sec-tv1.tv_sec);
}