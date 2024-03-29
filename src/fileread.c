#include "main.h"

Registro *iniRgtr(int naccess) {
	Registro *registro = malloc(sizeof(Registro));
	if (registro == NULL) {
		perror(program_invocation_short_name);
		exit(EXIT_FAILURE);
	}

	g_config.naccess  = naccess;
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

	char *line = NULL;
	size_t len = 0;
	ssize_t read;

	fseek(fp,0L,SEEK_END);
	g_config.filesiz = ftell(fp);
	rewind(fp);

	float percent;
	int i = 0, count = 1;
	int lines = nofloat((double)g_config.filesiz/11);
	g_config.inlines = lines;
	// nofloat: corrige entrada com linhas impares

	Registro *registro = iniRgtr(lines);
	Access *acesso = registro->acesso;
	printf("  Arquivo de entrada: %s\n", g_config.file);
	printf("  Tamanho do arquivo: %d Bytes\n", g_config.filesiz);

	printf("\e[?25l");
	while ((read = getline(&line,&len,fp)) != -1) {
		percent = (count * 100) / lines;
		sscanf(line,"%x %c", &acesso[i].addr, &acesso[i].rw);
		printf("               Lendo: ");
		printf(CYELL"[%03.0f%%] ", percent);
		printf("%08X %c\r"CRSET, acesso[i].addr, acesso[i].rw);
		count++;
		i++;
	};
	printf("\33[2K\r\e[?25h");

	free(line);
	fclose(fp);

	return registro;
}

void clrReg(Registro *registro) {
	free(registro->acesso);
	free(registro);
}