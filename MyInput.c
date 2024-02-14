#include "MyInput.h"
long int input_long(void)
{
    char input[8] = "";
    short flag = 0;
    while (flag == 0)
    {
        fgets(input, 8, stdin);
        flag = 1;
        int i = 0;
        char cur = input[i];
        while (cur != 0 && cur != '\n')
        {
            if (!(cur >= '0' && cur <= '9'))
            {
                flag = 0;
                printf("检测到数字之外的字符，请重新输入：\n");
                memset(input, 0, 8);
                break;
            }
            i++;
            cur = input[i];
        }
    }
    char *endptr;
    long int n = strtol(input, &endptr, 10);
    return n;
}
