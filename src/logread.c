#include "./includes/main.h"

int countLN(char *file) {
	FILE *fp = fopen(file,"r");
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

void readlog(char *file, Registro *registro) {
	FILE *fp = fopen(file,"r");
	if (fp == NULL) {
		perror(PROGRAM);
		exit(EXIT_FAILURE);
	}

	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	int i = 0;
	Access *access = registro->access;
	while ((read = getline(&line,&len,fp)) != -1) {
		sscanf(line,"%x %c",&access[i].addr,&access[i].rw);
		i++;
	};

	free(line);
	fclose(fp);
}