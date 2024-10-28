In one of the video lectures of module 4, I talked about a recursive function in C for implementing the quick sort algorithm.

Below, you can find another example of recursive functions in C.

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char *helper(char *str, int left, int right) {
  int len = right - left + 1;
  if (len == 0) // base case #1
    return "";
  if (len == 1) { // base case #2
    char *rv = (char *)malloc(2);
    strncpy(rv, str + left, 1);
    return rv;
  }
  // recurisve step!
  char *first = helper(str, left, left + len / 2 - 1);
  char *second = helper(str, left + len / 2, right);
  char *rv = (char *)malloc(len+1);
  strcpy(rv, second);
  strcat(rv, first);
  return rv;
}
char *unknown_operation(char *str) {
  int len = strlen(str);
  return helper(str, 0, len - 1);
}
int main(void) {
  char *out = unknown_operation("what does this function do?!!");
  printf("%s\n", out);
  return 0;
}
```

1. Try to guess the output of this program first.

2. Then, run it on ocelot and find out the real output.

3. Finally, justify your observation by explaining the way the recursive step and base cases of the recursive function "helper" works.