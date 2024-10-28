Consider the following program that sorts and prints out a given list of fruit names:

```c

#include<stdio.h>
#include<string.h>
char* names[] = {"kiwi", "berries", "apple", "orange",
"strawberry", "pineapple", "Kiwi", "Berries", "Apple",
"Orange", "Strawberry", "Pineapple"};
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

void main(void){
    generic_qsort((void**)names, 0, 11,(int(*)(void*, void*))strcmp);
    for(int i = 0; i < 12; i++)
        printf("%s\n", names[i]);
}
```
This program passes function pointer "strcmp" to the generic_qsort function to compare two fruit names in the quick sort and do the sorting operation.

1. Change the program that sorts the names decreasingly. To do so, define a function and replace "strcmp" with a pointer to your function.

2. Change the program that sorts the names after ignoring their case. To do so, define a function and replace "strcmp" with a pointer to your function.

3. Share your defined functions in steps 1 and 2 with your classmates.