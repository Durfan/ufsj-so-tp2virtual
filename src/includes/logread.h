#ifndef _LOGREAD_H
#define _LOGREAD_H

void readlog(char *file, Queue *queue);
bool valdata(Data data, size_t line);

#endif // _LOGREAD_H