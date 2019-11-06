#ifndef INCLUDE_DS_TABLE_H
#define INCLUDE_DS_TABLE_H

typedef struct pagtab_t {
	unsigned frame;
	bool bitres;
	bool bitmod;
	bool bitref;
} Pagtab;

void prtAddr(Registro *registro);

//#pragma message __FILE__
#endif // INCLUDE_DS_TABLE_H