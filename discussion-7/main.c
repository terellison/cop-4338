#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"

int main(void) 
{
    const size_t size = 100;
    char buffer[size];
    fgets(buffer, size, stdin);

    t_node* root = make_bst(buffer, strlen(buffer) - 1);
    in_order_print(root);
    clear(root);
    return 0;
}

t_node* insert(t_node* root_p, char value) {  
  if(root_p != NULL)
  {
    if(root_p->value > value)
    {
      root_p->left = insert(root_p->left, value);
    }
    else if(root_p->value < value)
    {
      root_p->right = insert(root_p->right, value);
    }

    // do nothing if the value already exists
  }
  else
  {
    root_p = (t_node*)malloc(sizeof(t_node));
    if(!root_p)
      exit(1); // no memory
    root_p->value = value;
  }
  return root_p;
}

int search(t_node* root, char value) {
  if (!root) {
    return 0;
  }

  if (value == root->value) {
    return 1;
  }

  if (value > root->value) {
    return search(root->right, value);
  }

  return search(root->left, value);
}

t_node* make_bst(char arr[], int size) {
  t_node* head = (t_node*)malloc(sizeof(t_node));
  head->value = arr[0];

  for (int i = 1; i < size; i++) {
    head = insert(head, arr[i]);
  }

  return head;
}

void post_order_print(t_node* root) {
  if (root) {
    post_order_print(root->left);
    post_order_print(root->right);
    printf("%c ", root->value);
  }
}

void pre_order_print(t_node* root) {
  if (root) {
    printf("%c ", root->value);
    pre_order_print(root->left);
    pre_order_print(root->right);
  }
}

int height(t_node* root) {
  if (!root) {
    return -1;
  }

  return 1 + max(height(root->left), height(root->right));
}

int count(t_node* root) {
  if (!root) {
    return 0;
  }

  return 1 + count(root->left) + count(root->right);
}

int min_value(t_node* root) {
  if (!root) {
    return (1 << 31);
  }

  if (!root->left) {
    return root->value;
  }

  return min_value(root->left);
}

int max_value(t_node* root) {
  if (!root) {
    return (1 << (31 - 1));
  }

  if (!root->right) {
    return root->value;
  }

  if (!root->right) {
    return root->value;
  }

  return max_value(root->right);
}

void in_order_print(t_node* root)
{
    if(root)
    {
      char c = root->value;
      in_order_print(root->left);
      printf("%c", c);
      in_order_print(root->right);
    }
}

void clear(t_node* root)
{
  if(root)
  {
    clear(root->left);
    clear(root->right);
    free(root);
  }
}