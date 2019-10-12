#include "./includes/main.h"

int main(void) {

	char *file = "./logs/matriz.log";
	int naccess = countLN(file);
	Registro *registro = iniQueue(naccess);

	printf("Executando o simulador...\n");
	printf("Arquivo de entrada: %s\n", file);

	readlog(file,registro);

	#ifdef DEBUG
	prtReg(registro);
	printf("Memoria usada: %ld Kib\n", registro->alocmem/128);
	#endif

	clrReg(registro);
	return EXIT_SUCCESS;
}