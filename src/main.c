#include "./includes/main.h"

int main(void) {

	char *file = "./logs/testfdfde.log";
	Queue *queue = inique();

	printf("Executando o simulador...\n");
	printf("Arquivo de entrada: %s\n", file);
	readlog(file,queue);

	prtqeue(queue);

	queFree(queue);

	return EXIT_SUCCESS;
}