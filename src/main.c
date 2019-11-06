#include "main.h"

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

	system("clear");
	puts("Executando o simulador...");
	readlog(registro);

	Memory *memory = simmem();

	enqueue(memory,0);
	enqueue(memory,1);
	enqueue(memory,2);
	enqueue(memory,3);
	enqueue(memory,4);
	enqueue(memory,5);
	enqueue(memory,6);

	prtmem(memory);

	
	printf("%d", dequeue(memory));
	printf("%d", dequeue(memory));
	printf("%d", dequeue(memory));
	printf("%d", dequeue(memory));
	printf("%d", dequeue(memory));

	prtmem(memory);

	printf("Arquivo de entrada: %s\n", g_config.file);
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