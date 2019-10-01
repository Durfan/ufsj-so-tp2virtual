#include "./includes/main.h"

void readlog(char *file) {

	FILE *fp = fopen(file,"r");
	assert(fp);

	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	while ((read = getline(&line,&len,fp)) != -1) {

	}

	if (line)
		free(line);
	fclose(fp);
}