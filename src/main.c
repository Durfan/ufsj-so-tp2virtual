#include "./includes/main.h"

int main(void) {

	char *file = "./logs/matriz.log";
	Queue *queue = inique();

	printf("Executando o simulador...\n");
	printf("Arquivo de entrada: %s\n", file);
	readlog(file,queue);

	//prtqeue(queue);

	int s = 2;
	int pread = 0;

	printf("Tamanho das paginas: %d\n", s);
	
	Data page;
	while (!quEmpty(queue)) {
		page = gethead(queue);
		page.addr >>= s;
		//printf(" %08x \u27A1 %08x\n", page.addr, page.addr >> s);
		pread++;
		dequeue(queue);
	}

	printf("Paginas Lidas: %d\n", pread);

	queFree(queue);

	return EXIT_SUCCESS;
}