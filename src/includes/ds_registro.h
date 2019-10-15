#ifndef _DS_REGISTRO_H
#define _DS_REGISTRO_H

typedef struct access_t {
	unsigned addr;
	char rw;
} Access;

typedef struct registro_t {
	int naccess;
	size_t alocmem;
	Access *access;
} Registro;

Registro *iniQueue(int naccess);
void prtReg(Registro *registro);
void clrReg(Registro *registro);

#endif // _DS_REGISTRO_H