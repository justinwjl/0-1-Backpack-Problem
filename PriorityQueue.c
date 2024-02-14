#include "PriorityQueue.h"

// 按照价值率进行排序
short cmp_by_density(const void *a, const void *b)
{
    PrNode *na = (PrNode *)a;
    PrNode *nb = (PrNode *)b;
    if (na->density > nb->density)
    {
        return 1;
    }
    if (na->density < nb->density)
    {
        return -1;
    }
    return 0;
}

// 计算当前以节点为根的子树的价值上界
double calc_bound(int level, int weight, int value, ptr_q pq, ptr_bn list)
{
    double bound = value; // 初始化上界为当前价值，不包含当前节点
    int i;
    for (i = level; i < pq->N && weight + list[i].weight <= pq->C; ++i)
    { // 尽可能装满背包
        weight += list[i].weight;
        bound += list[i].value;
    }
    if (i < pq->N)
    { // 装填剩余容量
        bound += (pq->C - weight) * list[i].value_per_weight;
    }
    return bound;
}

// 初始化优先队列
void pq_init(PrQ *pri_que)
{
    pri_que->size = 0;
    memset(pri_que->data, 0, sizeof(pri_que->data));
}

// 插入node节点到优先队列pq中，保证队首节点为价值率最高的节点
void pq_push(PrQ *pri_que, PrNode *node)
{
    // 计算当前节点的价值密度
    node->density = (double)node->value / node->weight;
    // -----------------------------------
    // 将当前节点放在数组末尾，相当于放在大根堆的叶子节点处
    pri_que->data[pri_que->size++] = node;
    int i = pri_que->size - 1;
    // -----------------------------------
    // 从底向上调整节点以维持大根堆的性质
    while (i > 0 && cmp_by_density(pri_que->data[(i - 1) / 2], pri_que->data[i]) < 0)
    {
        // 父节点更小则交换父子节点
        PrNode *tmp = pri_que->data[(i - 1) / 2];
        pri_que->data[(i - 1) / 2] = pri_que->data[i];
        pri_que->data[i] = tmp;
        i = (i - 1) / 2;
    }
}

// 取出队首节点，并调整以维持大根堆（优先队列）的性质
PrNode *pq_pop(PrQ *pri_que)
{
    // 取出队首节点，原先队首节点位置的节点用叶子节点代替
    PrNode *ret = pri_que->data[0];
    pri_que->data[0] = pri_que->data[--pri_que->size];
    // -----------------------------------
    // 从上往下调整
    int i = 0;
    while (i * 2 + 1 < pri_que->size)
    {
        int left = i * 2 + 1, right = i * 2 + 2;
        int largest = left;
        // -----------------------------------
        // 右孩子大于左孩子节点
        if (right < pri_que->size && cmp_by_density(pri_que->data[left], pri_que->data[right]) < 0)
        {
            largest = right;
        }
        // -----------------------------------
        // 当前节点大于左右孩子节点，则表明调整完毕
        if (cmp_by_density(pri_que->data[i], pri_que->data[largest]) >= 0)
        {
            break;
        }
        // -----------------------------------
        // 交换当前节点与左右孩子节点中较大的那个
        PrNode *tmp = pri_que->data[i];
        pri_que->data[i] = pri_que->data[largest];
        pri_que->data[largest] = tmp;
        i = largest;
    }
    return ret;
}
