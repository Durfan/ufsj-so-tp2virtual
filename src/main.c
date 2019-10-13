#include "./includes/main.h"

int main(void) {

	setlocale(LC_ALL,NULL);

	char *file = "./logs/matriz.log";
	int naccess = countLN(file);
	Registro *registro = iniQueue(naccess);

	puts("Executando o simulador...");
	printf("Arquivo de entrada: %s\n", file);

	readlog(file,registro);

	#ifdef DEBUG
	prtReg(registro);
	printf("Memoria usada: %ld Kib\n", registro->alocmem/128);
	#endif

	clrReg(registro);
	return EXIT_SUCCESS;
}