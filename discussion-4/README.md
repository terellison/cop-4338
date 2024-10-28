The following C program creates an two-dimensional array of integers of size 40 by 50 where each cell at row index i and column index j stores the value of ((i+1)*(j+1)):

```c
#include<stdio.h>

void main(void){

     int array[40][50];

     for(int i = 0; i < 40; i++)

          for(int j = 0; j < 50; j++)

               array[i][j] = (i+1) * (j+1);

     printf("%d", your_function(array));

}
```
1. Write a function that receives the 2D array as its only input parameter, traverses all cells of the array, counts the number of elements in the array that are divisible by 6 but are not divisible by 5 (e.g. 6, 18 are counted, but 30 or 60 are not counted), and finally returns the total count.

2. Can you make the function find the total count in a more efficient way? How?