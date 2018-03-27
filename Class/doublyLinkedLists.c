#include <stdio.h>
#include <stdlib.h>


typedef struct _node{
	int data;
	struct _node* prev;
	struct _node* next;
}node;

addToFront(node** headPointer, node** tailPointer, int value){
	node* box = (node)malloc(sizeof(node));
	box->data = value;
	
}