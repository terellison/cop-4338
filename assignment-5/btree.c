#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "solver.h"


bstNode* talloc(){
	return (bstNode*) malloc(sizeof(bstNode));
}

void inorder_print(bstNode* root){
	if(root == NULL) return;
	bstData* data = root->data;
	inorder_print(root->left);//visiting the left substree
	printf("%s\t%d\t%d:%d\t%d:%d\n", data->value, data->threadIndex,
					data->startRow, data->endRow, data->startCol, data->endCol);;//visitig the root
	inorder_print(root->right);//visiting the left substree	
}
int bst_insert(bstNode** root_p, bstData* data){
	if((*root_p) == NULL){//tree is empty
		*root_p = talloc();
		(*root_p)->data = data;
		(*root_p)->left = (*root_p)->right = NULL;
		return 1;//successful insert
	}
	if(!strcmp((*root_p)->data->value, data->value))//duplicate!
		return 0;//unsuccessful
	if(strcmp((*root_p)->data->value, data->value) > 0)
		return bst_insert(&(*root_p)->left, data);
	return bst_insert(&(*root_p)->right, data);
}

