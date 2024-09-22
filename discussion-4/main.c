#include<stdio.h>

int count(int arr[40][50]);

int main(void){

    int array[40][50];

    for(int i = 0; i < 40; i++)

        for(int j = 0; j < 50; j++)

            array[i][j] = (i+1) * (j+1);

    printf("%d", count(array));
    return 0;
}

int count(int arr[40][50])
{
    int count = 0;
    for(int i = 1; i < 40; ++i)
    {
        for(int j = 1; j < 50; ++j)
        {
            int num = i * j;

            if(num % 5 != 0 && num % 6 == 0)
            {
                count++;
            }
        }
    }

    return count;
}