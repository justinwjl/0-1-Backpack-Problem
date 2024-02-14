
#include "basic_function.h"
ElemType max(ElemType a, ElemType b)
{
    return (a > b) ? a : b;
}
void my_strcpy(char *des, char *src, long int len)
{
    for (long int i = 0; i < len; i++)
        des[i] = src[i];
}
