#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <fcntl.h>
#include <pthread.h>
#include <unistd.h>

#define MEM_LIMIT 64000000
#define error(m, c) do{fprintf(stderr, "%s\n", m);exit(c);}while(0)
#define BINS 101

void print_buffer(char** sub_puzzle, int subpuzzle_rows, int subpuzzle_cols);
void* solve(void* arg);

struct node {
  struct node *next;
  char *value;
};
typedef struct node node;
typedef struct {
  node **table;
  int size;
  int bins;
} hashset;
struct tnode{
	char* value;
	struct tnode* left;
	struct tnode* right;
};
typedef struct tnode tnode;//tnode is my binary tree node typedef

typedef struct threadData 
{
    char **sub_puzzle;
    int subpuzzle_rows;
    int subpuzzle_cols;
    int start_row;
    int start_col;
    int min_len;
    int max_len;
    int sorted;
    int threadIndex;
} threadData;
typedef struct bstData
{
	char* value;
	int startRow;
	int startCol;
	int endRow;
	int endCol;
	int threadIndex;
} bstData;

struct bstNode{
	bstData* data;
	struct bstNode* left;
	struct bstNode* right;
};
typedef struct bstNode bstNode;//bstNode is my binary tree node typedef

//hash set functions
int search(hashset h, char *val);
int insert(hashset *h, char *val);
hashset set_init();
int delete_value(hashset *h, char *value);
//bst functions
bstNode* talloc();
void inorder_print(bstNode* root);
int bst_insert(bstNode** root_p, bstData* data);
void* solve(void* args);
void searchInDirection(threadData* data, int startRow, int startCol, int rowStep, int colStep);
int checkForDuplicate(hashset h, char* word);

