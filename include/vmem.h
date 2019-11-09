#ifndef INCLUDE_VMEM_H
#define INCLUDE_VMEM_H

int *iniMem(void);
int getframe(Pagtab *table, int *vmem);
int getfreeframe(int *vmem);

int algLRU(Pagtab *table, int *vmem);

//#pragma message __FILE__
#endif // INCLUDE_VMEM_H