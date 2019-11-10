#ifndef INCLUDE_VMEM_H
#define INCLUDE_VMEM_H

int getframe(Pagtab *table);
int algLRU(Pagtab *table);
int algNRU(Pagtab *table);
int clssNRU(Pnode *pnode);

//#pragma message __FILE__
#endif // INCLUDE_VMEM_H