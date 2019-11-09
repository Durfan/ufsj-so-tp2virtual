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
	unsigned filesiz;
	unsigned naccess;
	unsigned pagsize;
	unsigned memsize;
	unsigned pgdeslc;
	unsigned frames;
} g_config;

Subalg str2enum(const char *str);
void setCfg(char **argv);
unsigned getdeslc(unsigned size);
unsigned tablesze(unsigned pgdeslc, unsigned memsize);
unsigned getPaddr(unsigned addr);
unsigned valSize(unsigned val, unsigned min, unsigned max);
unsigned powrOf2(unsigned val);

//#pragma message __FILE__
#endif // INCLUDE_CONFIG_H