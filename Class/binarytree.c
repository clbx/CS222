#include <stdio.h>
#include <stdlib.h>

typedef struct _Tree{
	int data;
	struct _Tree* left;
	struct _Tree* right;
} Tree;

int main(){

}

Tree* find(Tree* root, int value){
	if(root==NULL){
		return NULL;
	}
	else if(root->data == value){
		return root;
	}
	else if(root->data < value){
		return find(root->left, value);
	}
	else{
		return find(root->right, value);
	}

}

Tree* add(Tree* root, int value){
	if(root == NULL){
		Tree* temp = (Tree)malloc(sizeof(Tree));
		temp->left = NULL;
		temp->right = NULL;
		temp->data = value;
	}
	else if(value< root->data){
		root->left = add(root->left, value);
	}
	else if(value > root->data){
		root->left = add(root->right, value);
	}

	return root;
}