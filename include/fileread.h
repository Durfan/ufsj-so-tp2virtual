#ifndef INCLUDE_FILEREAD_H
#define INCLUDE_FILEREAD_H

typedef struct access_t {
	unsigned addr;
	char rw;
} Access;

typedef struct registro_t {
	Access *acesso;
	int naccess;
	size_t alocmem;
} Registro;

Registro *iniRgtr(int naccess);
Registro *readlog(void);
void prtReg(Registro *registro);
void clrReg(Registro *registro);

//#pragma message __FILE__
#endif // INCLUDE_FILEREAD_H