#ifndef _DSTRUCT_H
#define _DSTRUCT_H

enum subalg_t { lru, nru, segunda_chance };
typedef enum subalg_t Subalg;

static const struct {
	Subalg val;
	const char *str;
} g_polstr[] = {
	{lru, "lru"},
	{nru, "nru"},
	{segunda_chance, "segunda_chance"},
};

struct {
	Subalg salg;
	char *file;
	unsigned pagsize;
	unsigned memsize;
} g_config;

typedef struct access_t {
	unsigned addr;
	char rw;
} Access;

typedef struct registro_t {
	int naccess;
	size_t alocmem;
	Access *access;
} Registro;

Subalg str2enum(const char *str);
Registro *iniQueue(int naccess);
void prtReg(Registro *registro);
void clrReg(Registro *registro);
int valSize(int val, int min, int max);
int powrOf2(int val);

#endif // _DSTRUCT_H