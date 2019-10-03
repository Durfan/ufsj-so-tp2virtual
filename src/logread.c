#include "./includes/main.h"

void readlog(char *file, Queue *queue) {

	FILE *fp = fopen(file,"r");
	if (fp == NULL) {
		free(queue);
		error(EXIT_FAILURE,errno,"readlog");
	}

	char *line = NULL;
	size_t lcount = 1;
	size_t len = 0;
	ssize_t read;

	Data data;

	while ((read = getline(&line,&len,fp)) != -1) {
		sscanf(line,"%x %c",&data.addr,&data.rw);
		if (valdata(data,line,lcount))
			enqueue(queue,data);
		lcount++;
	};

	free(line);
	fclose(fp);
}

bool valdata(Data data, char *line, size_t lcount) {
	line[strcspn(line, "\n")] = 0;

	if (data.rw != 'R' && data.rw != 'W') {
		printf("%ld: %s%s%s",lcount,CRED,line,CRSET);
		printf(" \u27A1 erro na indicacao do acesso\n");
		return false;
	} else if (strlen(line) > 10) {
		printf("%ld: %s%s%s",lcount,CRED,line,CRSET);
		printf(" \u27A1 erro de leitura\n");
		return false;
	}

	return true;
}