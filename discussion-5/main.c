#include<stdio.h>
#include<string.h>
char* names[] = {"kiwi", "berries", "apple", "orange",
"strawberry", "pineapple", "Kiwi", "Berries", "Apple",
"Orange", "Strawberry", "Pineapple"};

int custom_strcmp(const char* first, const char* second);
int custom_strcmp2(const char* first, const char* second);

void swap(void* v[], int i, int j){
    void* temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void generic_qsort(void* v[], int left, int right,
    int (*comp)(void*, void*)){
    int i, last;
    if(left >= right) return;//base case
    swap(v, left, (left + right)/2);//pivot
    last = left;
    for(i = left + 1; i <= right; i++)
        if((*comp)(v[i], v[left]) < 0)
            swap (v, ++last, i);
    swap(v, left, last);
    generic_qsort(v, left, last - 1, comp);
    generic_qsort(v, last + 1, right, comp);
}

int main(void){
    generic_qsort((void**)names, 0, 11,(int(*)(void*, void*))custom_strcmp2);
    for(int i = 0; i < 12; i++)
        printf("%s\n", names[i]);
    return 0;
}

/// @brief Compares first to second
/// @param first 
/// @param second 
/// @return 
int custom_strcmp(const char* first, const char* second)
{
    int i = 0;
    int firstLen = strlen(first), secLen = strlen(second);

    while(i < firstLen && i < secLen)
    {
        if(first[i] > second[i])
        {
            return 1;
        }
        else if(first[i] < second[i])
        {
            return -1;
        }
        
        ++i;
    }

    return 0;
}

/// @brief Compares first to second while ignoring case
/// @param first 
/// @param second 
/// @return 
int custom_strcmp2(const char* first, const char* second)
{
    int i = 0;
    int firstLen = strlen(first), secLen = strlen(second);

    while(i < firstLen && i < secLen)
    {
        char a = first[i], b = second[i];

        if(a >= 'A' && a <= 'Z')
        {
            a = a + ('a' - 'A');
        }

        if(b >= 'A' && b <= 'Z')
        {
            b = b + ('a' - 'A');
        }

        if(a > b)
        {
            return 1;
        }
        else if(a < b)
        {
            return -1;
        }

        ++i;
    }
    return 0;
}