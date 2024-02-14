#include "knapsack_dp.h"

void dp(ptr_q pq, ptr_r pr, double start)
{
    int N = pq->N;
    // 初始化时间参数
    struct timeval cur_time;
    // -------------------------------------
    // 初始化动态规划表
    DPNode **dp_table = (DPNode **)malloc(sizeof(DPNode *) * N);
    for (int i = 0; i < N; i++)
        dp_table[i] = (DPNode *)malloc(sizeof(DPNode) * (pq->C + 1));
    for (int i = 0; i < N; i++)
        for (int j = 0; j <= pq->C; j++)
        {
            dp_table[i][j].value = 0;
            dp_table[i][j].choice = 0;
        }
    // -------------------------------------
    // 边界条件限制
    for (int i = pq->weight[N - 1]; i <= pq->C; i++)
    {
        dp_table[N - 1][i].value = pq->value[N - 1];
        dp_table[N - 1][i].choice = 1;
    }
    //-------------------------------------
    int cur_item = 0;
    int exit_c = 0;
    // 逆序递推
    for (int cur_item = N - 2; cur_item >= 0; cur_item--)
    {
        for (int cur_c = 0; cur_c <= pq->C; cur_c++)
        {
            // 当前物品能放入背包
            if (pq->weight[cur_item] <= cur_c)
            {
                if (dp_table[cur_item + 1][cur_c].value > dp_table[cur_item + 1][cur_c - pq->weight[cur_item]].value + pq->value[cur_item])
                {
                    // 当前物品放入背包后价值反而减少
                    dp_table[cur_item][cur_c].value = dp_table[cur_item + 1][cur_c].value;
                    dp_table[cur_item][cur_c].choice = 0;
                }
                else
                {
                    // 当前物品放入背包后价值增加
                    dp_table[cur_item][cur_c].value = dp_table[cur_item + 1][cur_c - pq->weight[cur_item]].value + pq->value[cur_item];
                    dp_table[cur_item][cur_c].choice = 1;
                }
            }
            // 当前物品无法放入背包
            else
            {
                dp_table[cur_item][cur_c].value = dp_table[cur_item + 1][cur_c].value;
                dp_table[cur_item][cur_c].choice = 0;
            }
        }
        gettimeofday(&cur_time, NULL);
        if (cur_time.tv_sec - start > TIME_LIMIT)
        {
            // 找到退出时最大取值的背包容量(该物品已被考察过)
            int cur_max_value = 0;
            for (int i = 0; i <= pq->C; i++)
            {
                if (dp_table[cur_item][i].value > cur_max_value)
                {
                    cur_max_value = dp_table[cur_item][i].value;
                    exit_c = i; // 对后面这几个物品分配的背包容量
                }
            }
            break;
        }
    }
    // -------------------------------------
    // 如果退出时的物品下标不为0，则表明是由于超时而退出循环
    if (cur_item > 0)
    {
        int cur_c = exit_c;
        pr->value = dp_table[cur_item][cur_c].value;
        // 记录目前最大值相应的路径
        for (int item = cur_item; item < N; item++)
        {
            if (dp_table[item][cur_c].choice == 1)
            {
                // item被放入了背包
                pr->solution[item] = 1;
                cur_c -= pq->weight[item];
            }
            else
            {
                pr->solution[item] = 0;
            }
        }
        // 利用贪心算法求解0～cur_item-1
        // 分配到前面物品的背包容量为pq->C - exit_c
        greedy(pq, pr, cur_item, pq->C - exit_c);
    }
    // -------------------------------------
    // 未超时，动态规划表格完整,则由回溯得到最优解
    else
    {
        int i = 0;
        int j = pq->C;
        while (i < N && j > 0) // 当物品未被考察完且背包中仍有空间时
        {
            if (dp_table[i][j].choice == 1)
            {
                // i被放入了背包
                pr->solution[i] = 1;
                j -= pq->weight[i];
            }
            else
            {
                pr->solution[i] = 0;
            }
            i++;
        }
        pr->value = dp_table[0][pq->C].value;
    }
    for (int i = 0; i < N; i++)
        free(dp_table[i]);
    free(dp_table);
}
double knapsack_dp(ptr_q pq, ptr_r pr)
{
    /*
    用动态规划法求解01背包问题
    */

    struct timeval start, end;
    gettimeofday(&start, NULL);
    dp(pq, pr, start.tv_sec);
    gettimeofday(&end, NULL);
    double timeuse = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    return timeuse;
}
