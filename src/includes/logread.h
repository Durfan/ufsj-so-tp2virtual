#ifndef _LOGREAD_H
#define _LOGREAD_H

void readlog(char *file, Queue *queue);
bool valdata(Data data, char *line, size_t lcount);

#endif // _LOGREAD_H