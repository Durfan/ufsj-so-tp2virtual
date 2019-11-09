#ifndef INCLUDE_TABLE_H
#define INCLUDE_TABLE_H

typedef struct pnode_t {
	Addr paddr;
	int frame;
	bool bitres;
	bool bitmod;
	bool bitref;
	unsigned count;
	struct pnode_t *next;
} Pnode;

typedef struct list_t {
	unsigned size;
	struct pnode_t *head;
} List;

typedef struct pagtab_t {
	struct list_t *lstaddr;
} Pagtab;

Pagtab *iniTbl(void);
List *iniLst(void);

void execRG(Pagtab *table, Registro *registro, int *vmem);
Pnode *schLst(List *list, Addr paddr);
Pnode *pshLst(List *list, Addr paddr);
void clrTbl(Pagtab *table);
unsigned modHsh(Addr addr);

void clrLst(List *list);
int lstnil(List *list);

//#pragma message __FILE__
#endif // INCLUDE_TABLE_H