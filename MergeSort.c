#include "MergeSort.h"

void merge_for_greedy(GreedyNode *array, long int l, long int m, long int r)
{
    // l：左半部分数组的起始下标
    // m：左半部分数组的结束下标
    // r：右半部分数组的结束下标
    long int len1 = m - l + 1; // 左半子数组长度
    long int len2 = r - m;     // 右半子数组长度
    GreedyNode L[len1];
    GreedyNode R[len2];
    for (int i = 0; i < len1; i++)
        L[i] = array[l + i];
    for (int j = 0; j < len2; j++)
        R[j] = array[m + 1 + j];
    long int i = 0;
    long int j = 0;
    long int k = l;                        // 辅助下标,注意初始取值
    while (i <= len1 - 1 && j <= len2 - 1) // 排序并合并到原数组中
    {
        if (L[i].value_per_weight <= R[j].value_per_weight)
        {
            array[k++] = L[i++];
        }
        else
        {
            array[k++] = R[j++];
        }
    }
    while (i <= len1 - 1)
    {
        array[k++] = L[i++];
    }
    while (j <= len2 - 1)
    {
        array[k++] = R[j++];
    }
}

void merge_sort_for_greedy(GreedyNode *array, long int len, long int l, long int r)
{
    if (l < r)
    {
        long int m = l + (r - l) / 2;
        merge_sort_for_greedy(array, len, l, m);
        merge_sort_for_greedy(array, len, m + 1, r);
        merge_for_greedy(array, l, m, r);
    }
}
void merge_for_B(BNode *array, long int l, long int m, long int r)
{
    // l：左半部分数组的起始下标
    // m：左半部分数组的结束下标
    // r：右半部分数组的结束下标
    long int len1 = m - l + 1; // 左半子数组长度
    long int len2 = r - m;     // 右半子数组长度
    BNode L[len1];
    BNode R[len2];
    for (int i = 0; i < len1; i++)
        L[i] = array[l + i];
    for (int j = 0; j < len2; j++)
        R[j] = array[m + 1 + j];
    long int i = 0;
    long int j = 0;
    long int k = l;                        // 辅助下标,注意初始取值
    while (i <= len1 - 1 && j <= len2 - 1) // 排序并合并到原数组中
    {
        if (L[i].value_per_weight >= R[j].value_per_weight)
        {
            array[k++] = L[i++];
        }
        else
        {
            array[k++] = R[j++];
        }
    }
    while (i <= len1 - 1)
    {
        array[k++] = L[i++];
    }
    while (j <= len2 - 1)
    {
        array[k++] = R[j++];
    }
}

void merge_sort_for_B(BNode *array, long int len, long int l, long int r)
{
    if (l < r)
    {
        long int m = l + (r - l) / 2;
        merge_sort_for_B(array, len, l, m);
        merge_sort_for_B(array, len, m + 1, r);
        merge_for_B(array, l, m, r);
    }
}