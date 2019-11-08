#ifndef INCLUDE_DS_TABLE_H
#define INCLUDE_DS_TABLE_H

typedef struct node_t {
	int paddr;
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

void insTbl(Pagtab *table, int addr);
void prtTbl(Pagtab *table);
void clrTbl(Pagtab *table);
int modHsh(int addr);
int tblesze(void);

void pshLst(List *list, int key);
void prtLst(List *list);
void clrLst(List *list);
int lstnil(List *list);

//#pragma message __FILE__
#endif // INCLUDE_DS_TABLE_H