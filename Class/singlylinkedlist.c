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

void remove(node** headPointer, int value){
	node* head = *headPointer;
	if(head == NULL){
		return;
	}
	else if(head->data == value){
		*headPointer = head->next;
		free(head);
	}
	while(head->next != NULL){
		if(head->next->data == value){
			head->next = head->next->next;
		}
		head = head->next;
	}
}

void insert(node** headPointer, int value){
	node* head = *headPointer;
	if(head == NULL || value< head-> data){
		node* box = (node*)malloc(sizeof(node));
		box->data = value;
		box->next = head;
		*headPointer = box;
		return;
	}
	while(head->next != NULL && head->next->data < value)
	 	head = head->next;
	node* box = (node*)malloc(sizeof(node));
	box->data = value;
	box->next = head->next;
	head->next = box;
	return;
}
void empty(node* head){
	while(head != NULL){
		node* box;
		box = head;
		head = head->next;
		free(box);
	}
}


int main(){

	return 0;
}

