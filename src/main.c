#include "main.h"

void appinfo(void);

int main(int argc, char **argv) {

	setlocale(LC_ALL,"");

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

	execRG(table,registro);
	//prtTbl(table);
	
	#ifdef DEBUG
	prtReg(registro);
	printf("Deslocamento p: %d\n", g_config.pgdeslc);
	printf("Memoria usada: %ld Kib\n", registro->alocmem / 128);
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