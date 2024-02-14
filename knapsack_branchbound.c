#include "knapsack_branchbound.h"
void branchbound(ptr_bn list, ptr_q pq, ptr_r pr, double start_time)
{
    // 初始化最优价值
    pr->value = 0;
    // -----------------------------------
    // 初始化优先队列
    PrQ queue;
    pq_init(&queue);
    // -----------------------------------
    // 初始化根节点
    PrNode root = {0, 0, 0, 0, 0, 0}; // 根节点
    root.selected = 0;
    root.density = 0;
    root.bound = calc_bound(0, 0, 0, pq, list); // 计算根节点的上界
    pq_push(&queue, &root);                     // 将根节点放入优先队列
    // -----------------------------------
    // 初始化时间变量
    struct timeval cur_time;
    char flag = 0; // 用于记录是否超时
    // -----------------------------------
    // 维护栈，记录最近访问完毕的一条路径
    PrNode *stack[MAX_QLEN];
    int top = 0;
    // -----------------------------------
    // 开始搜索
    int quit_index = 0;
    int quit_weight = 0;
    while (queue.size > 0 && (flag == 0))
    {                                  // 队列不为空且未超时
        PrNode *node = pq_pop(&queue); // 取出队首节点
        if (node->bound <= pr->value)
        { // 如果该节点的价值上界小于等于当前最优解，直接跳过
            continue;
        }
        if (node->level == pq->N)
        { // 如果到达叶子节点
            // 如果叶子节点对应的值大于当前最优解值，则更新当前最优解
            if (node->value > pr->value)
            {
                pr->value = node->value;
                memset(pr->solution, 0, sizeof(char) * pr->N);
                // 利用stack和父指针记录最近访问完毕的一条路径
                top = 0;
                while (node && node->level > 0)
                {
                    stack[top++] = node;
                    node = node->parent;
                }
                top--;
                //-----------------------------------
                PrNode *stack_pointer = NULL;
                while (top >= 0)
                {
                    stack_pointer = stack[top--];
                    BNode cur_list_node = list[stack_pointer->level - 1];
                    if (stack_pointer->selected == 1)
                        pr->solution[cur_list_node.index] = 1;
                    else
                        pr->solution[cur_list_node.index] = 0;
                }
            }
            continue;
        }
        // 检测是否达到时间限制
        gettimeofday(&cur_time, NULL);
        if (cur_time.tv_sec - start_time > TIME_LIMIT)
        {
            flag = 1;
            // 如果当前最优解大于0，说明已经探索了一条路径
            // 将flag设置为2，表示无需进一步探索当前路径
            if (pr->value > 0)
            {
                flag = 2;
            }
            // -----------------------------------
            // 当前一条路径都还没有探索完整
            else
            {
                quit_index = node->level - 1; // 计入weight和value的物品的下标
                quit_weight = node->weight;
                pr->value = node->value;
                // 利用stack和父指针记录最近访问完毕的一条路径
                top = 0;
                while (node && node->level > 0)
                {
                    stack[top++] = node;
                    node = node->parent;
                }
                top--;
                //-----------------------------------
                PrNode *stack_pointer = NULL;
                while (top >= 0)
                {
                    stack_pointer = stack[top--];
                    BNode cur_list_node = list[stack_pointer->level - 1];
                    if (stack_pointer->selected == 1)
                        pr->solution[cur_list_node.index] = 1;
                    else
                        pr->solution[cur_list_node.index] = 0;
                }
            }
            continue;
        }
        // -----------------------------------
        PrNode *left = (PrNode *)malloc(sizeof(PrNode)); // 左子节点（选中当前物品）
        left->level = node->level + 1;                   // 下一个探索的物品的下标
        left->value = node->value + list[node->level].value;
        left->weight = node->weight + list[node->level].weight;
        left->bound = calc_bound(left->level, left->weight, left->value, pq, list); // 计算左子节点的上界
        left->density = left->value / (double)left->weight;
        left->selected = 1;
        left->parent = node;
        // -----------------------------------
        PrNode *right = (PrNode *)malloc(sizeof(PrNode)); // 右子节点（不选当前物品）
        right->level = node->level + 1;                   // 下一个探索的物品的下标
        right->value = node->value;
        right->weight = node->weight;
        right->bound = calc_bound(right->level, right->weight, right->value, pq, list); // 计算右子节点的上界
        right->density = right->value / (double)right->weight;
        right->selected = 0;
        right->parent = node;
        // -----------------------------------
        // 对比左右子节点价值率，价值率较高的节点先入列
        if (left->density > right->density)
        {
            if (left->weight <= pr->C)
                pq_push(&queue, left);
            pq_push(&queue, right);
        }
        else
        {
            pq_push(&queue, right);
            if (left->weight <= pr->C)
                pq_push(&queue, left);
        }
        // -----------------------------------
    }
    // 如果flag是1，则说明超时且没有一条完整的解路径，需要进行贪心法求解
    if (flag == 1)
    {
        // 贪心法求解
        int cur_capacity = pr->C - quit_weight;
        int list_index = quit_index + 1; // 从最大价值率的物品开始
        BNode cur_node;
        while ((list_index < pr->N) && (cur_capacity > 0)) // 当物品未被考察完且背包中仍有空间时
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
            list_index++;
        }
    }
}
double knapsack_branchbound(ptr_q pq, ptr_r pr)
{
    /*
    用分支限界法求解01背包问题
    */
    struct timeval start, end;
    int N = pq->N;
    pr->C = pq->C;
    pr->N = N;
    // -------------------------------------
    // 初始化列表，用于按照价值率倒序排序
    ptr_bn list = (ptr_bn)malloc(sizeof(BNode) * (N + 1));
    for (int i = 0; i < N; i++)
    {
        list[i].index = i;
        list[i].value_per_weight = (double)pq->value[i] / (double)pq->weight[i];
        list[i].value = pq->value[i];
        list[i].weight = pq->weight[i];
    }
    merge_sort_for_B(list, N, 0, N - 1);
    // -------------------------------------
    gettimeofday(&start, NULL);
    branchbound(list, pq, pr, start.tv_sec);
    gettimeofday(&end, NULL);
    double timeuse = (end.tv_sec - start.tv_sec) + (end.tv_usec - start.tv_usec) / 1000000.0;
    return timeuse;
}
