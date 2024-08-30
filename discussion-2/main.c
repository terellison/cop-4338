#include<stdio.h>

int main()
{
    char str[15] = "hello world!";

    char* p = &str[4];

    printf("%d %d %c %c %c", p - str, p[-2] - 'a', p[3] - 4, *(p--), *(++p));
}