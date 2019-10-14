#include "./includes/main.h"

int main(int argc, char **argv) {

	setlocale(LC_ALL,"");

	if (argc != 5) {
		printf(PROGRAM": %s\n", strerror(EINVAL));
		puts("USO: ./"PROGRAM" [polsub] [arquivo] [pagsize] [memsize]");
		exit(EXIT_FAILURE);
	}

	setCfg(argv);
	int naccess = countLN();
	Registro *registro = iniQueue(naccess);

	puts("Executando o simulador...");
	printf("Arquivo de entrada: %s\n", g_config.file);
	printf("Tamanho da memoria: %ld Bytes", g_config.memsize);
	printf(" (%ld KiB)\n", g_config.memsize >> 0x00A);
	printf("Tamanho das paginas: %ld Bytes", g_config.pagsize);
	printf(" (%ld KiB)\n", g_config.pagsize >> 0x00A);
	printf("Tecnica de reposicao: %s\n", g_polstr[g_config.salg].str);

	readlog(registro);

	#ifdef DEBUG
	prtReg(registro);
	prtAddr(registro);
	printf("Deslocamento p: %d\n", g_config.pgdeslc);
	printf("Memoria usada: %ld Kib\n", registro->alocmem/128);
	#endif

	clrReg(registro);
	return EXIT_SUCCESS;
}