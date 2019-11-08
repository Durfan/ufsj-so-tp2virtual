#ifndef INCLUDE_TABLE_H
#define INCLUDE_TABLE_H

typedef struct node_t {
	unsigned addr;
	unsigned frame;
	bool bitres;
	bool bitmod;
	bool bitref;
	struct node_t *next;
} Node;

typedef struct list_t {
	int size;
	struct node_t *head;
} List;

typedef struct pagtab_t {
	struct list_t *lstaddr;
} Pagtab;

Pagtab *iniTbl(void);
List *iniLst(void);

void insTbl(Pagtab *table, unsigned addr);
bool schLst(List *list, unsigned addr);
void clrTbl(Pagtab *table);
int modHsh(unsigned addr);
int tblesze(void);

void pshLst(List *list, unsigned addr);
void clrLst(List *list);
int lstnil(List *list);

//#pragma message __FILE__
#endif // INCLUDE_TABLE_H