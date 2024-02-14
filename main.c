#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "MyHeader.h"
int main(void)
{
    // 初始化问题参数
    Question question;
    printf("请输入物体个数N\n");
    long int N = input_long();
    question.N = (int)N;
    printf("物体个数N为%d\n", question.N);
    printf("请输入背包最大容量C\n");
    long int C = input_long();
    question.C = (int)C;
    printf("背包最大容量C为%d\n", question.C);
    char alg_name[6][20];
    strcpy(alg_name[0], "分治法");
    strcpy(alg_name[1], "动态规划算法");
    strcpy(alg_name[2], "贪心算法");
    strcpy(alg_name[3], "回溯法");
    strcpy(alg_name[4], "分支限界法");
    strcpy(alg_name[5], "蒙特卡洛算法");
    question.value = (ElemType *)malloc(sizeof(ElemType) * N);
    question.weight = (ElemType *)malloc(sizeof(ElemType) * N);
    question.upper_bound = (ElemType *)malloc(sizeof(ElemType) * (N + 1));
    for (int i = 0; i <= N - 1; i++)
    {
        question.value[i] = myrand(1, 100);
        question.weight[i] = myrand(1, 100);
    }
    question.upper_bound[N] = 0;
    for (long int i = N - 1; i >= 0; i--)
    {
        question.upper_bound[i] = question.upper_bound[i + 1] + question.value[i];
    }
    // -----------------------------------------
    // 初始化结果参数
    Result results[6];
    for (short i = 0; i < 6; i++)
    {
        results[i].solution = (char *)malloc(sizeof(char) * N);
        results[i].value = 0;
        results[i].N = (int)N;
        results[i].weight = 0;
        results[i].C = (int)C;
    }
    double time_spent[6] = {0};
    // -----------------------------------------
    // 运行算法
    short index = 0;
    time_spent[index] = knapsack_divide(&question, &(results[index]));
    index++;
    time_spent[index] = knapsack_dp(&question, &results[index]);
    index++;
    time_spent[index] = knapsack_greedy(&question, &results[index]);
    index++;
    time_spent[index] = knapsack_backtrack(&question, &results[index]);
    index++;
    time_spent[index] = knapsack_branchbound(&question, &results[index]);
    index++;
    time_spent[index] = knapsack_montecarlo(&question, &results[index]);

    // -----------------------------------------
    // 输出结果
    for (short i = 0; i < 6; i++)
    {
        printf("%s的输出如下:\n", alg_name[i]);
        printf("merge value:%-12d time:%-15lf solution:", results[i].value, time_spent[i]);
        for (int j = 0; j < N; j++)
            printf("%c", (results[i].solution)[j] + '0');
        printf("\n");
    }
    // -----------------------------------------
    return 0;
}
