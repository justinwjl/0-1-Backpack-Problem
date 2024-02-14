#include "MyRand.h"

// 生成从a到b的随机整数
ElemType myrand(ElemType a, ElemType b)
{
    srand48(1);
    ElemType result = a + (1.0 * rand()) / RAND_MAX * (b - a);
    return result;
}

ElemType myrand_for_windows(ElemType a, ElemType b)
{
    int num = 0;
    int max = 0;
    srand(1);
    for (int j = 0; j < 10; j++)
    {
        int temp = rand() % 10;
        num += temp * pow(10, j);
        max += 9 * pow(10, j);
    }
    ElemType result = a + (1.0 * num) / max * (b - a);
    return result;
}
