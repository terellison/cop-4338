#include "main.h"

void reverse_str(const char* str, const UINT len, char* result)
{
    UINT j = 0;
    for(int i = len - 1; i >= 0; i--, ++j)
    {
        result[j] = *(str + i);
    }
}