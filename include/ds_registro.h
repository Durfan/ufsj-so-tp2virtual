#ifndef INCLUDE_DS_REGISTRO_H
#define INCLUDE_DS_REGISTRO_H

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

//#pragma message __FILE__
#endif // INCLUDE_DS_REGISTRO_H