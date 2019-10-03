#include "./includes/main.h"

int main(void) {

	char *file = "./logs/teste.log";
	Queue *queue = inique();

	readlog(file,queue);
	prtqeue(queue);

	return 0;
}