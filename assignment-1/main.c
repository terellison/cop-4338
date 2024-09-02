#include <stdio.h>
#include <string.h>
#include "main.h"

int main(void)
{
    const int LENGTH = 1000;
    char line[LENGTH];

    while(1)
    {
        fgets(line, LENGTH, stdin);
        int len = strlen(line) - 1;

        if(len <= 0)
            break;

        singleton(line, len);
        arithmetic(line, len);
        reverse_arithmetic(line, len);
        tripartite(line, len);
        bipartite(line, len);
        palindrome(line, len);

        printf("%c", '\n');
    }

    return 0;
}

void singleton(const char* str, const UINT len)
{
    UINT isSingleton = 1;
    if(len > 1)
    {
        char c = str[0];

        for(UINT i = 1; i < len && isSingleton; ++i)
        {
            isSingleton = c == str[i];
        }
    }

    if(isSingleton)
        printf("%s", "singleton\n");
}

void arithmetic(const char* str, const UINT len)
{
    UINT isArith = 1;
    if(len > 1)
    {
        char c = str[0];
        
        for(UINT i = 1; i < len && isArith; ++i)
        {
            isArith = str[i] == (c + 1);
            c = str[i];
        }
    }

    if(isArith)
        printf("%s", "arithmetic\n");
}

void reverse_arithmetic(const char* str, const UINT len)
{
    UINT isRevArith = 1;
    if(len > 1)
    {
        char c = str[0];
    
        for(UINT i = 1; i < len; ++i)
        {
            isRevArith = str[i] == (c - 1);
            c = str[i];
        }
    }

    if(isRevArith)
        printf("%s","reverse arithmetic\n");
}

void tripartite(const char* str, const UINT len)
{
    if(len < 3)
        return;
    
    char c = str[0];
    char part[len];
    part[0] = c;
    UINT p = 1;

    for(UINT i = 1; i < len; ++i)
    {
        if(str[i] != c)
        {
            part[p] = str[i];
            ++p;
        }
        else
            break;
    }

    UINT partLen = p;

    UINT partCount = 1;
    UINT i = p;

    while(i < len && partCount < 3)
    {
        UINT foundPart = 1;
        for(UINT j = 0; j < partLen - 1; ++j)
        {
            if(str[i] != part[j])
            {
                foundPart = 0;
                break;
            }
            ++i;
        }

        if(!foundPart)
            break;
        
        ++partCount;
        ++i;
    }

    if(partCount == 3)
        printf("balanced tripartite\n");
}

void bipartite(const char* str, const UINT len)
{
    if(len < 2)
        return;
    
    UINT j = len / 2;
    UINT isBipartite = 1;
    for(UINT i = 0; i < (len / 2); ++i, ++j)
    {
        if(str[i] != str[j])
        {
            isBipartite = !isBipartite;
            break;
        }
    }

    if(isBipartite)
        printf("%s", "balanced bipartite\n");
}

void palindrome(const char* str, const UINT len)
{
    UINT isPalindrome = 1;
    if(len > 1)
    {
        char reverse[len];
        
        reverse_str(str, len, reverse);
        
        for(UINT i = 0; i < len; ++i)
        {
            if(str[i] != reverse[i])
            {
                isPalindrome = !isPalindrome;
                break;
            }
        }
    }

    if(isPalindrome)
        printf("%s", "palindrome\n");
}