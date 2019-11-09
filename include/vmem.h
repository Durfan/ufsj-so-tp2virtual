#ifndef INCLUDE_VMEM_H
#define INCLUDE_VMEM_H

int *iniMem(void);
int getframe(int *vmem);
int getfreeframe(int *vmem);

//#pragma message __FILE__
#endif // INCLUDE_VMEM_H