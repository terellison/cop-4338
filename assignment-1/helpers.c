#include "helpers.h"

void reverse_str(char* str, unsigned int len, char* reversed)
{
    // Find the actual end of the string
    unsigned int actualEnd = 0;
    char toTest = ' ';

    while(toTest != '\0')
    {
        toTest = str[actualEnd];
        ++actualEnd;
    }

    int j = 0;

    for(int i = actualEnd - 1; i >= 0; --i)
    {
        reversed[j] = str[i];
        ++j;
    }
    
}