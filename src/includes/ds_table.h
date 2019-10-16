#ifndef INCLUDE_DS_TABLE_H
#define INCLUDE_DS_TABLE_H

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
	size_t pagsize;
	size_t memsize;
	unsigned pgdeslc;
} g_config;

typedef struct pagtab_t {
	unsigned frame;
	bool bitres;
	bool bitmod;
	bool bitref;
} Pagtab;

Subalg str2enum(const char *str);
void setCfg(char **argv);
int getdeslc(unsigned size);
int getPaddr(unsigned addr);
void prtAddr(Registro *registro);

int valSize(int val, int min, int max);
int powrOf2(int val);

//#pragma message __FILE__
#endif // INCLUDE_DS_TABLE_H