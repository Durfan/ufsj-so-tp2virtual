#ifndef INCLUDE_FILEREAD_H
#define INCLUDE_FILEREAD_H

typedef struct access_t {
	Addr addr;
	char rw;
} Access;

typedef struct registro_t {
	Access *acesso;
	unsigned naccess;
	unsigned alocmem;
} Registro;

Registro *iniRgtr(int naccess);
Registro *readlog(void);
void clrReg(Registro *registro);

//#pragma message __FILE__
#endif // INCLUDE_FILEREAD_H