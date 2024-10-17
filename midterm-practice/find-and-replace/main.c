#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* findAndReplace(const char* str, const char* pattern, const char* altPattern);

int main(void)
{
    char* str = "I really like fried chicken";
    char* pattern = "chicken";
    char* replacement = "watermelon";

    printf("Replacing \'%s\' in \"%s\" with \'%s\'...\n", pattern, str, replacement);

    char* result = findAndReplace(str, pattern, replacement);

    printf("New string after replacement: %s", result);

    return 0;
}

char* findAndReplace(const char* str, const char* pattern, const char* altPattern)
{
    size_t strLen = strlen(str);
    size_t patternLen = strlen(pattern);
    size_t altPatternLen = strlen(altPattern);

    // First, calculate the length of the resulting string.
    size_t count = 0;
    const char* tmp = str;
    while ((tmp = strstr(tmp, pattern)) != NULL) {
        count++;
        tmp += patternLen;
    }

    // Allocate memory for the resulting string.
    size_t newLen = strLen + count * (altPatternLen - patternLen);
    char* result = (char*)malloc(newLen + 1);

    // Replace occurrences of pattern with altPattern.
    const char* src = str;
    char* dest = result;
    while (*src) {
        if (strstr(src, pattern) == src) {
            strcpy(dest, altPattern);
            dest += altPatternLen;
            src += patternLen;
        } else {
            *dest++ = *src++;
        }
    }

    *dest = '\0';
    return result;
}
