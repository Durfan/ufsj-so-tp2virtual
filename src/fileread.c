#include "main.h"

int countLN(void) {
	FILE *fp = fopen(g_config.file,"r");
	if (fp == NULL) {
		perror(PROGRAM);
		exit(EXIT_FAILURE);
	}

	int lines = 0;
	while (EOF != (fscanf(fp, "%*[^\n]"), fscanf(fp,"%*c")))
		++lines;

	fclose(fp);
	return lines;
}

void readlog(Registro *registro) {
	FILE *fp = fopen(g_config.file,"r");
	if (fp == NULL) {
		perror(PROGRAM);
		exit(EXIT_FAILURE);
	}

	int i = 0;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	Access *access = registro->access;
	while ((read = getline(&line,&len,fp)) != -1) {
		sscanf(line,"%x %c", &access[i].addr, &access[i].rw);
		i++;
	};

	free(line);
	fclose(fp);
}