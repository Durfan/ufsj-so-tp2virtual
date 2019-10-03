#include "./includes/main.h"

void readlog(char *file, Queue *queue) {

	FILE *fp = fopen(file,"r");
	if (!fp)
		error(1,2,file);

	char *line = NULL;
	size_t lcount = 1;
	size_t len = 0;
	ssize_t read;

	Data data;
	bool valid = true;

	while ((read = getline(&line,&len,fp)) != -1) {
		sscanf(line,"%x %c",&data.addr,&data.rw);
		valid = valdata(data,lcount);
		enqueue(queue,data);
		lcount++;
	}

	if (!valid)
		error(1,5,file);

	free(line);
	fclose(fp);
}

bool valdata(Data data, size_t line) {
	bool valid;

	if (data.addr == UINT_MAX) {
		printf("%ld: %s%08x%s %c\n",line,CRED,data.addr,CRSET,data.rw);
		valid = false;
	}
/* 	else if (data.rw != 'R' || data.rw != 'W') {
		printf("%ld: %08x %s%c%s\n",line,data.addr,CRED,data.rw,CRSET);
		valid = false;
	} */

	return valid;
}