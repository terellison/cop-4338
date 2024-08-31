#include <stdio.h>
#include <string.h>
#include "main.h"
#include "helpers.h"

int main(void)
{
    const int LENGTH = 1000;
    char line[LENGTH];

    while(1)
    {
        fgets(line, LENGTH, stdin);
        unsigned int len = strlen(line) - 1;

        if(len <= 0)
            continue;

        singleton(line, len);
        arithmetic(line, len);
        reverse_arithmetic(line, len);
        // tripartite(line, len);
        // bipartite(line, len);
        // palindrome(line, len);

        printf("%c", '\n');
    }

    return 0;
}

void singleton(const char* str, const unsigned int len)
{
    unsigned int isSingleton = 1;
    if(len > 1)
    {
        char c = str[0];

        for(unsigned int i = 0; i < len && isSingleton; ++i)
        {
            isSingleton = c == str[i];
        }
    }

    if(isSingleton)
        printf("%s", "singleton\n");
}

void arithmetic(const char* str, const unsigned int len)
{
    unsigned int isArith = 1;
    if(len > 1)
    {
        char c = str[0];
        
        for(unsigned int i = 1; i < len && isArith; ++i)
        {
            isArith = str[i] == (c + 1);
            c = str[i];
        }
    }

    if(isArith)
        printf("%s", "arithmetic\n");
}

void reverse_arithmetic(const char* str, const unsigned int len)
{
    unsigned int isRevArith = 1;
    if(len > 1)
    {
        char c = str[0];
    
        for(unsigned int i = 1; i < len; ++i)
        {
            isRevArith = str[i] == (c - 1);
            c = str[i];
        }
    }

    if(isRevArith)
        printf("%s","reverse arithmetic\n");
}