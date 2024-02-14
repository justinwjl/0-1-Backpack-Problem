#ifndef MergeSort_h
#define MergeSort_h
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include "MyType.h"
void merge_for_greedy(GreedyNode *array, long int l, long int m, long int r);
void merge_sort_for_greedy(GreedyNode *array, long int len, long int l, long int r);
void merge_sort_for_B(BNode *array, long int len, long int l, long int r);
#endif /* MergeSort_h */
