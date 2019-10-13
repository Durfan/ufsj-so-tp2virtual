#include "./includes/main.h"

int main(int argc, char **argv) {

	setlocale(LC_ALL,NULL);

	g_config.salg = str2enum(argv[1]);
	g_config.file = argv[2];
	g_config.pagsize = atoi(argv[3]) << 0x00A;
	g_config.memsize = atoi(argv[4]) << 0x00A;

	int naccess = countLN();
	Registro *registro = iniQueue(naccess);

	puts("Executando o simulador...");
	printf("Arquivo de entrada: %s\n", g_config.file);
	printf("Tamanho da memoria: %d Bytes", g_config.memsize);
	printf(" (%d KiB)\n", g_config.memsize >> 0x00A);
	printf("Tamanho das paginas: %d Bytes", g_config.pagsize);
	printf(" (%d KiB)\n", g_config.pagsize >> 0x00A);
	printf("Tecnica de reposicao: %s\n", g_polstr[g_config.salg].str);

	readlog(registro);

	#ifdef DEBUG
	prtReg(registro);
	printf("Memoria usada: %ld Kib\n", registro->alocmem/128);
	#endif

	clrReg(registro);
	return EXIT_SUCCESS;
}