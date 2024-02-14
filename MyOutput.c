#include "MyOutput.h"

void output_array(double *array, long int len)
{

    // printf("\n");
    int line_count = 0;
    for (long int i = 0; i < len; i++)
    {
        printf("%-15lf ", array[i]); // 输出生成的随机数组
        line_count++;
        if (line_count == 5)
        {
            printf("\n");
            line_count = 0;
        }
    }
    printf("\n");
}
