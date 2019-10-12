#ifndef _DSTRUCT_H
#define _DSTRUCT_H

typedef struct access_t {
	unsigned addr;
	char rw;
} Access;

typedef struct registro_t {
	int naccess;
	Access *access;
} Registro;

Registro *iniQueue(int naccess);
void prtReg(Registro *registro);
void clrReg(Registro *registro);

#endif // _DSTRUCT_H