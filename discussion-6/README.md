Consider the following implementation of singly linked list in C programming language. Rewrite the function "remove_odd_indices" so that it uses iteration (while or for loops) instead of recursion to remove every other element of a given linked list:

```c
#include <stdio.h>
#include <stdlib.h>
//Singly Linked List is an implementation of List ADT
struct node{
    int value;
    struct node* next;
};
typedef struct node node;
node* construct_list(int arr[], int len) {
  if(len == 0)
    return NULL;
  node* head = (node*)malloc(sizeof(node));
  head->value = arr[0];
  node* temp = head;
  for(int i = 1; i < len; i++){
    temp -> next = (node*)malloc(sizeof(node));
    temp -> next -> value = arr[i];
    temp = temp->next;
  }
  temp -> next = NULL;
  return head;
}
char* to_str(node* head){//"1 -> 2 -> 3 -> 4"
  char* rv = (char*)malloc(1000);
  if(head == NULL)//empty list
    rv[0] = '\0';//rv = "";
  else if(head->next == NULL)//second base case
    sprintf(rv, "%d", head->value);
  else//recursive case
    sprintf(rv, "%d -> %s", head->value, to_str(head->next));
  return rv;
}
void remove_odd_indices(node* head){
    if(head == NULL || head -> next == NULL)
        return;
    head->next = head->next->next;
    remove_odd_indices(head->next);
}
int main(void) {
  int vals[] = {1,2,3,4,5,6,7,8,9,10};
  node* list = construct_list(vals, 10);
  printf("Original list is %s\n", to_str(list));//1 -> 2 ->... -> 10
  remove_odd_indices(list);
  printf("updated list is %s\n", to_str(list));//1 -> 3 -> 5 -> 7 -> 9
  return 0;
}
```

Hint: watch the following video explaining how to implement singly linked lists in C:

[![](https://img.youtube.com/vi/aoj_d8Q0VEQ/0.jpg)](https://www.youtube.com/watch?v=aoj_d8Q0VEQ)