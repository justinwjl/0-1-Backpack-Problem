#ifndef knapsack_greedy_h
#define knapsack_greedy_h
#include <sys/time.h>
#include <stdio.h>
#include "MyType.h"
#include "MergeSort.h"
double knapsack_greedy(ptr_q pq, ptr_r pr);
void greedy(ptr_q pq, ptr_r pr, int len, int cur_capacity);
#endif /* knapsack_greedy_h */
