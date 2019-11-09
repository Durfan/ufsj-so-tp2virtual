#ifndef INCLUDE_CONFIG_H
#define INCLUDE_CONFIG_H

typedef enum subalg_t { 
	lru, nru, segunda_chance } Subalg;

typedef unsigned int Addr;

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
	size_t filesiz;
	size_t pagsize;
	size_t memsize;
	unsigned pgdeslc;
} g_config;

Subalg str2enum(const char *str);
void setCfg(char **argv);
int getdeslc(unsigned size);
int getPaddr(unsigned addr);
int valSize(int val, int min, int max);
int powrOf2(int val);

//#pragma message __FILE__
#endif // INCLUDE_CONFIG_H