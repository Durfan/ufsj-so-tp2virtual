#ifndef INCLUDE_VMEM_H
#define INCLUDE_VMEM_H

int getframe(Pagtab *table, Deque *deque);
int algLRU(Pagtab *table);
int algNRU(Pagtab *table);
int algSC(Deque *deque);
int clssNRU(Pnode *pnode);
void prtCLS(int class);

//#pragma message __FILE__
#endif // INCLUDE_VMEM_H