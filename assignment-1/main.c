#include <stdio.h>
#include "helpers.h"

int main(void)
{
    const int LENGTH = 1000;
    char line[LENGTH];

    while(1)
    {
        scanf("%s", line);
        char reversed[LENGTH];
        reverse_str(line, LENGTH, reversed);
        printf("%s", reversed);
    }


    return 0;
}