#include "main.h"

Registro *iniRgtr(int naccess) {
	Registro *registro = malloc(sizeof(Registro));
	if (registro == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}

	registro->naccess = naccess;
	registro->alocmem = naccess * sizeof(Access);
	registro->acesso  = malloc(registro->alocmem);
	if (registro->acesso == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}

	return registro;
}

Registro *readlog(void) {
	FILE *fp = fopen(g_config.file,"r");
	if (fp == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}

	int i = 0;
	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fseek(fp,0L,SEEK_END);
	g_config.filesiz = ftell(fp);
	rewind(fp);

	Registro *registro = iniRgtr(g_config.filesiz/11);
	Access *acesso = registro->acesso;

	while ((read = getline(&line,&len,fp)) != -1) {
		sscanf(line,"%x %c", &acesso[i].addr, &acesso[i].rw);
		i++;
	};

	free(line);
	fclose(fp);

	return registro;
}

void prtReg(Registro *registro) {
	int barran = 0;
	Access *acesso = registro->acesso;
	for (int i=0; i < registro->naccess; i++) {
		printf(" %08x %c", acesso[i].addr, acesso[i].rw);
		barran++;
		if (barran > 5) {
			putchar(0x0A);
			barran = 0;
		}
		else
			printf(" \u2502");
	}
	putchar(0x0A);
}

void clrReg(Registro *registro) {
	free(registro->acesso);
	free(registro);
}