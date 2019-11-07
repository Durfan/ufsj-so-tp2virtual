#ifndef INCLUDE_DS_TABLE_H
#define INCLUDE_DS_TABLE_H

typedef struct pagtab_t {
	unsigned paddr;
	bool bitres;
	bool bitmod;
	bool bitref;
} Pagtab;

int tblesze(void);

//#pragma message __FILE__
#endif // INCLUDE_DS_TABLE_H