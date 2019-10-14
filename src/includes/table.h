#ifndef _TABLE_H
#define _TABLE_H

typedef struct pagtab_t {
	unsigned frame;
	int bitres;
	int bitmod;
	int bitref;
} Pagtab;

int getdeslc(void);
int getPaddr(unsigned addr);
void prtAddr(Registro *registro);

#endif // _TABLE_H