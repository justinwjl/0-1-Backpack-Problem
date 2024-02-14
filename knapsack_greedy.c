
#include "knapsack_greedy.h"

void greedy(ptr_q pq, ptr_r pr, int len, int cur_capacity)
{
    // 初始化价值率列表，然后对列表从小到大排序
    pr->value = 0;
    ptr_gn list = (ptr_gn)malloc(sizeof(GreedyNode) * len);
    for (int i = 0; i < len; i++)
    {
        list[i].index = i;
        list[i].value_per_weight = (double)pq->value[i] / (double)pq->weight[i];
    }
    merge_sort_for_greedy(list, len, 0, len - 1);
    // -------------------------------------
    // 贪心法求解
    int list_index = len - 1; // 从最大价值率的物品开始
    GreedyNode cur_node;
    while ((list_index >= 0) && (cur_capacity > 0)) // 当物品未被考察完且背包中仍有空间时
    {
        cur_node = list[list_index];                    // 当前物品
        if (pq->weight[cur_node.index] <= cur_capacity) // 当前物品可以放入背包
        {
            pr->solution[cur_node.index] = 1;
            pr->value += pq->value[cur_node.index];
            cur_capacity -= pq->weight[cur_node.index];
        }
        else
        {
            pr->solution[cur_node.index] = 0;
        }
        list_index--;
    }
}

double knapsack_greedy(ptr_q pq, ptr_r pr)
{
    /*
    用贪心法求解01背包问题
    */
    struct timeval start, end;
    gettimeofday(&start, NULL);
    greedy(pq, pr, pq->N, pq->C);
    gettimeofday(&end, NULL);
    double timeuse = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    return timeuse;
}
