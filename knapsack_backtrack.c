
#include "knapsack_backtrack.h"
void backtrack(ptr_bn list, ptr_q pq, ptr_r pr, ptr_r cur, char *flag, int index, double start, int C, struct timeval *cur_time)
{
    if (*flag == 1)
        return;
    // 初始化时间参数，并关注是否超过时间限制
    gettimeofday(cur_time, NULL);
    if (cur_time->tv_sec - start > TIME_LIMIT)
        *flag = 1;
    // -------------------------------------
    // 判断是否找到可行解
    if ((index == pq->N) || (C == 0))
    {
        if (cur->value > pr->value)
        {
            pr->value = cur->value;
            my_strcpy(pr->solution, cur->solution, pq->N);
        }
        return;
    }
    if (*flag == 1)
        return;
    // -------------------------------------
    // 当前物品放入背包
    int ori_index = list[index].index;
    if (C >= pq->weight[ori_index] && cur->value + list[index].upper_bound > pr->value)
    {
        cur->solution[ori_index] = 1;
        cur->value += pq->value[ori_index];
        backtrack(list, pq, pr, cur, flag, index + 1, start, C - pq->weight[ori_index], cur_time);
        cur->value -= pq->value[ori_index];
    }
    if (*flag == 1)
        return;
    // -------------------------------------
    // 当前物体放不进背包或不放入背包
    if (cur->value + list[index + 1].upper_bound > pr->value)
        cur->solution[ori_index] = 0;
    backtrack(list, pq, pr, cur, flag, index + 1, start, C, cur_time);
}
double knapsack_backtrack(ptr_q pq, ptr_r pr)
{
    /*
    用回溯法求解01背包问题
    */
    long int N = pq->N;
    // 初始化当前解
    Result temp_result;
    temp_result.value = 0;
    temp_result.weight = 0;
    temp_result.solution = (char *)malloc(sizeof(char) * N);
    memset(temp_result.solution, 0, sizeof(char) * N);
    // -------------------------------------
    // 初始化时间有关变量
    char flag = 0;
    struct timeval start, end, cur_time;
    gettimeofday(&start, NULL);
    // -------------------------------------
    // 初始化列表，用于按照价值率倒序排序
    ptr_bn list = (ptr_bn)malloc(sizeof(BNode) * (N + 1));
    for (int i = 0; i < N; i++)
    {
        list[i].index = i;
        list[i].value_per_weight = (double)pq->value[i] / (double)pq->weight[i];
    }
    merge_sort_for_B(list, N, 0, N - 1);
    list[N].upper_bound = 0;
    for (long int i = N - 1; i >= 0; i--)
        list[i].upper_bound = list[i + 1].upper_bound + pq->value[list[i].index];
    // -------------------------------------
    backtrack(list, pq, pr, &temp_result, &flag, 0, start.tv_sec, pq->C, &cur_time);
    gettimeofday(&end, NULL);
    free(temp_result.solution);
    free(list);
    double timeuse = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    return timeuse;
}
