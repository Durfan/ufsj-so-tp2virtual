#ifndef INCLUDE_DEQUE_H
#define INCLUDE_DEQUE_H

typedef struct dqnode_t {
	Pnode *pnode;
	struct dqnode_t *next;
	struct dqnode_t *prev;
} DQnode;

typedef struct deque_t {
	unsigned size;
	struct dqnode_t *head;
	struct dqnode_t *tail;
} Deque;

Deque *dqcreate(void);
void dqpshHead(Deque *deque, Pnode *pnode);
void dqpshTail(Deque *deque, Pnode *pnode);
Pnode *dqpopHead(Deque *deque);
Pnode *dqpopTail(Deque *deque);
Pnode *dqpekHead(Deque *deque);
Pnode *dqpekTail(Deque *deque);
void dqprt(Deque *deque);
void dqclr(Deque *deque);
bool dqEmpty(Deque *deque);

//#pragma message __FILE__
#endif // INCLUDE_DEQUE_H 