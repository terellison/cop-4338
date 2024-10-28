First try to predict the outcome of the following C program. Then, run it to find out whether your prediction was correct or not. Try to justify your observation using the concept of pointers in C.

Hint: Please note that:

- p is a pointer initialized to letter 'o' in the string "hello world!"
- str which is the name of char array containing the "hello world!" string is considered to be the pointer to the first letter 'h'
- expression (p - str) subtracts a pointer from the other resulting in an integer counting how many characters can be fit between these two pointers.
- p[-2] is a character stored two letters before the current position that pointer p refers to
- p-- moves the pointer p backward in the string "hello world!"
- ++p moves the pointer p forward in the string "hello world!

```c
#include <stdio.h>

int main(){

    char str[15] = "hello world!";

    char* p = &str[4];

    printf("%d %d %c %c %c", p - str, p[-2] - 'a', p[3] - 4, *(p--), *(++p));

}
```