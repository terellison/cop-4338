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

char* to_str(node* head){
    //"1 -> 2 -> 3 -> 4"
    char* rv = (char*)malloc(1000);
    if(head == NULL) //empty list
        rv[0] = '\0'; //rv = "";
    else if(head->next == NULL) //second base case
        sprintf(rv, "%d", head->value);
    else //recursive case
        sprintf(rv, "%d -> %s", head->value, to_str(head->next));
    return rv;
}

void remove_odd_indices(node* head)
{
    while(head && head -> next)
    {
        node* temp = head->next;
        head->next = head->next->next;
        head = head->next;
        free(temp);
        temp = 0;
    }
}

int main(void) {
  int vals[] = {1,2,3,4,5,6,7,8,9,10};
  node* list = construct_list(vals, 10);

  //1 -> 2 ->... -> 10
  printf("Original list is %s\n", to_str(list));
  remove_odd_indices(list);

  //1 -> 3 -> 5 -> 7 -> 9
  printf("updated list is %s\n", to_str(list));
  return 0;
}