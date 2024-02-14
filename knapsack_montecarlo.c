
#include "knapsack_montecarlo.h"
void montecarlo(ptr_q pq, ptr_r pr, ptr_r cur, ptr_mn mlist, double start)
{
    ptr_gn glist = (ptr_gn)malloc(sizeof(GreedyNode) * pq->N);
    // 获取当前时间
    struct timeval cur_time;
    gettimeofday(&cur_time, NULL);
    // -------------------------------------
    // 确定生成几个随机数
    int rand_len = pr->C / (MAX_WEIGHT / 2) + 5;
    // -------------------------------------
    // 在达到时间限制前随机生成解
    while (cur_time.tv_sec - start <= TIME_LIMIT)
    {
        // 初始化当前解
        cur->value = 0;
        memset(cur->solution, 0, sizeof(char) * pr->N);
        int cur_capacity = pq->C;
        // -------------------------------------
        // 记录通过随机真正放入背包的物品数量
        int rand_real_len;
        rand_real_len = 0;
        // -------------------------------------
        // 随机选择物品
        for (int i = 0; i < rand_len; i++)
        {
            int rand_index = myrand(0, pr->N - 1);
            // 背包空间足够且未放入背包过
            if (cur_capacity >= pq->weight[rand_index] && mlist[rand_index].select == 0)
            {
                cur_capacity -= pq->weight[rand_index];
                cur->value += pq->value[rand_index];
                cur->solution[rand_index] = 1;
                mlist[rand_index].select = 1;
                rand_real_len++;
            }
        }
        // -------------------------------------
        // 剩余物品数量，新建列表存储剩余物品
        int rest_len = pr->N - rand_real_len;
        glist = realloc(glist, sizeof(GreedyNode) * rest_len);
        memset(glist, 0, sizeof(GreedyNode) * rest_len);
        int gi = 0;
        // -------------------------------------
        // 将剩余物品放入剩余列表中
        for (int i = 0; i < pr->N; i++)
        {
            if (mlist[i].select == 0)
            {
                glist[gi].index = i;
                glist[gi].value_per_weight = mlist[i].value_per_weight;
                gi++;
            }
            else
            {
                mlist[i].select = 0;
            }
        }
        // -------------------------------------
        // 对剩余物品按照价值率进行排序
        merge_sort_for_greedy(glist, rest_len, 0, rest_len - 1);
        // -------------------------------------
        // 贪心算法求解剩余物品
        gi = rest_len - 1; // 从最大价值率的物品开始
        // GreedyNode cur_gnode;
        while ((gi >= 0) && (cur_capacity > 0)) // 当物品未被考察完且背包中仍有空间时
        {
            int ori_index = glist[gi].index;           // 当前物品在原数组中的下标
            if (cur_capacity >= pq->weight[ori_index]) // 当前物品可以放入背包
            {
                cur->solution[ori_index] = 1;
                cur->value += pq->value[ori_index];
                cur_capacity -= pq->weight[ori_index];
            }
            else
            {
                cur->solution[ori_index] = 0;
            }
            gi--;
        }
        // -------------------------------------
        // 更新最优解
        if (cur->value > pr->value)
        {
            pr->value = cur->value;
            my_strcpy(pr->solution, cur->solution, pr->N);
        }
        // -------------------------------------
        // 获取当前时间
        gettimeofday(&cur_time, NULL);
    }
}
double knapsack_montecarlo(ptr_q pq, ptr_r pr)
{
    /*
    用Monte Carlo法求解01背包问题
    */
    struct timeval start, end;
    int N = pq->N;
    // 初始化当前解
    Result temp_result;
    temp_result.value = 0;
    temp_result.weight = 0;
    temp_result.solution = (char *)malloc(sizeof(char) * N);
    memset(temp_result.solution, 0, sizeof(char) * N);
    // -------------------------------------
    // 获取当前时间
    gettimeofday(&start, NULL);
    // -------------------------------------
    // 初始化物品列表
    ptr_mn list = (ptr_mn)malloc(sizeof(MNode) * N);
    for (int i = 0; i < N; i++)
    {
        list[i].value_per_weight = (double)pq->value[i] / (double)pq->weight[i];
        list[i].select = 0;
    }
    // -------------------------------------
    montecarlo(pq, pr, &temp_result, list, start.tv_sec);
    gettimeofday(&end, NULL);
    free(temp_result.solution);
    free(list);
    double timeuse = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    return timeuse;
}
