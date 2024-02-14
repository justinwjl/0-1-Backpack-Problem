#ifndef MyType_h
#define MyType_h

#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#ifndef ElemType
#define ElemType int
#endif
#ifndef TIME_LIMIT
#define TIME_LIMIT 10
#endif
#ifndef MAX_WEIGHT
#define MAX_WEIGHT 100
#endif
#ifndef MAX_QLEN
#define MAX_QLEN 10000
#endif

typedef struct Result
{
    char *solution;
    ElemType value;
    ElemType weight;
    int N;
    int C;
} Result, *ptr_r;
typedef struct Question
{
    ElemType *weight;
    ElemType *value;
    ElemType *upper_bound;
    int N;
    int C;
} Question, *ptr_q;
typedef struct GreedyNode
{
    int index;
    double value_per_weight;
} GreedyNode, *ptr_gn;
typedef struct DPNode
{
    char choice; // 在当前容量下，这一物品是否被放入背包
    ElemType value;
} DPNode, *ptr_dp;
typedef struct BNode
{
    int index;
    ElemType upper_bound;
    ElemType value;
    ElemType weight;
    double value_per_weight;
} BNode, *ptr_bn;
typedef struct MontecarloNode
{
    double value_per_weight;
    char select; // 0表示未选中，1表示选中,且只有它需要被改动
} MNode, *ptr_mn;
typedef struct PriorityNode
{
    int level;      // 选取到第几个物品(下一个)
    int value;      // 当前价值(不含本物品)
    int weight;     // 当前重量(不含本物品)
    double bound;   // 当前节点能够达到的最优价值上限
    double density; // 当前节点的价值密度（单位重量价值）
    char selected;
    struct PriorityNode *parent;
} PrNode;
typedef struct PriorityQueue
{
    PrNode *data[MAX_QLEN];
    int size;
} PrQ;
#endif /* MyType_h */
