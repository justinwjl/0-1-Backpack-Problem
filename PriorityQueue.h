
#ifndef PriorityQueue_h
#define PriorityQueue_h

#include <stdio.h>
#include "MyType.h"
#include "basic_function.h"
short cmp_by_density(const void *a, const void *b);
double calc_bound(int level, int weight, int value, ptr_q pq, ptr_bn list);
void pq_init(PrQ *pri_que);
void pq_push(PrQ *pri_que, PrNode *node);
PrNode *pq_pop(PrQ *pri_que);
#endif /* PriorityQueue_h */
