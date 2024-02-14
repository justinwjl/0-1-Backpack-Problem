
#include "knapsack_divide.h"

void divide(ptr_q pq, ptr_r pr, ptr_r temp, char *flag, int index, double start, int C, struct timeval *cur)
{
    if (*flag == 1)
        return;
    // 初始化时间参数，并关注是否超过时间限制
    gettimeofday(cur, NULL);
    if (cur->tv_sec - start > TIME_LIMIT)
        *flag = 1;
    // -------------------------------------
    // 判断是否到达叶子节点
    if ((index == pq->N) || (C == 0))
    {
        if (temp->value > pr->value)
        {
            pr->value = temp->value;
            my_strcpy(pr->solution, temp->solution, pq->N);
        }
        return;
    }
    if (*flag == 1)
        return;
    int ori_value = temp->value;
    // -------------------------------------
    // 当前物体放不进背包或不放入背包
    temp->solution[index] = 0;
    divide(pq, pr, temp, flag, index + 1, start, C, cur);
    int exclude = temp->value;
    if (*flag == 1)
        return;
    // -------------------------------------
    // 当前物品放入背包
    if (C >= pq->weight[index])
    {
        temp->solution[index] = 1;
        temp->value = ori_value + pq->value[index];
        divide(pq, pr, temp, flag, index + 1, start, C - pq->weight[index], cur);
        if (exclude > temp->value)
        {
            temp->solution[index] = 0;
            temp->value = exclude;
        }
    }
}

double knapsack_divide(ptr_q pq, ptr_r pr)
{
    /*
    用分治法求解01背包问题
    */
    // 初始化临时结果变量
    long int N = pq->N;
    Result temp_result;
    temp_result.value = 0;
    temp_result.solution = (char *)malloc(sizeof(char) * N);
    char flag = 0;
    // ------------------------------------------------------
    struct timeval start, end;
    struct timeval cur;
    gettimeofday(&start, NULL);
    divide(pq, pr, &temp_result, &flag, 0, start.tv_sec, pq->C, &cur);
    gettimeofday(&end, NULL);
    double timeuse = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    free(temp_result.solution);
    return timeuse;
}
