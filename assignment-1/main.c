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
        // arithmetic(line, len);
        // tripartite(line, len);
        // bipartite(line, len);
        // palindrome(line, len);

        printf("%c", '\n');
    }

    return 0;
}

void singleton(const char* str, const unsigned int len)
{
    int isSingleton = 1;
    if(len > 1)
    {
        char c = str[0];

        for(unsigned int i = 0; i < len && isSingleton == 1; ++i)
        {
            isSingleton = c == str[i];
        }
    }

    if(isSingleton)
        printf("%s", "singleton\n");
}