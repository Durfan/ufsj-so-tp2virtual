#include "main.h"

int main(int argc, char **argv) {

	setlocale(LC_ALL,"");

	if (argc != 5) {
		printf("%s: %s\n", argv[0], strerror(EINVAL));
		printf("USO: %s [polsub] [arquivo] [pagsize] [memsize]", argv[0]);
		exit(EXIT_FAILURE);
	}

	setCfg(argv);
	Registro *registro = readlog();

	system("clear");
	printf("%s [%s]\n", program_invocation_short_name, VERSION);

	printf("Arquivo de entrada: %s\n", g_config.file);
	printf("Tamanho do arquivo: %ld Bytes\n", g_config.filesiz);
	printf("Tamanho da memoria: %ld Bytes", (g_config.memsize << 0x00A) / 8);
	printf(" (%ld KiB/", g_config.memsize);
	printf("%g MiB)\n", (float)g_config.memsize / 1024);
	printf("Tamanho das paginas: %ld Bytes", (g_config.pagsize << 0x00A) / 8);
	printf(" (%ld KiB)\n", g_config.pagsize);
	printf("Tecnica de reposicao: %s\n", g_polstr[g_config.salg].str);

	#ifdef DEBUG
	prtReg(registro);
	prtAddr(registro);
	printf("Deslocamento p: %d\n", g_config.pgdeslc);
	printf("Memoria usada: %ld Kib\n", registro->alocmem / 128);
	#endif

	clrReg(registro);
	return EXIT_SUCCESS;
}