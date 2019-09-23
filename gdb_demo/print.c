#include<stdio.h>
void print_result(int num1, int num2, int res)
{
    char buf1[] = "sum of";
    char buf2[] = "and";
    char *buf = "is";

    printf("%s %d %s %d %s %d\n",
	buf1, num1, buf2, num2,  buf, res);
}
