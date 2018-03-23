#include <stdio.h>
#include <stdlib.h>


typedef struct _node{
	int data;
	struct _node* next;
}node;

void addNode(node** headPointer, int value){
	node* head = (node*)malloc(sizeof(node));
	head->data = value;
	head->next = *headPointer;
	*headPointer = head;
}

node* find(node* head, int value){
	while(head != NULL){
		if(head->data == value){
			return head;
		}
		head = head->next;
	}
	return NULL;
}

int main(){

	return 0;
}

