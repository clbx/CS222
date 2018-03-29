#include <stdio.h>
#include <stdlib.h>

typedef struct _node{
	int data;
	struct _node* next;
} node;


node* delete(node* head, int value);
node* add(node* head, int value);
void print(node* head);
void empty(node* head);

int main(){

	node* head = (node*)malloc(sizeof(node));
	head->next = NULL;
	int flag = 1;
	int choice = 0;
	while(flag){
		printf("1. Add new element\n2. Delete element\n3. Print list\n4. Exit\n");
		scanf("%d", &choice);
		if(choice == 1){
			int value = 0;
			scanf("%d", &value);
			head = add(head,value);
		}
		else if(choice == 2){
			int value = 0;
			scanf("%d", &value);
			head = delete(head,value);

		}
		else if(choice == 3){
			print(head);
		}
		else if(choice == 4){
			//Free stuff
			flag = 0;
		}
		else{
			printf("Please enter a valid input\n");
		}
	}
}


node* add(node* head, int value){
	node* temp = (node*)malloc(sizeof(node));
	if(head == NULL){
		head = temp;
		temp->data = value;
		temp->next = NULL;
		return temp;
	}
	else{
		temp->next = head;
		temp->data = value;
		return temp;
	}
}

void print(node* head){
	printf("Values:\n");
	while(head->next != NULL){
		printf("%d ", head->data);
		head = head->next;
	}
	printf("\n=====\n");
}

node* delete(node* head, int value){
	node* temp = head;
	if(temp == NULL){
		return NULL;
	}
	else if(head->data == value){
		head = head->next;
		free(temp);
		return head;
	}
	while(temp->next != NULL && temp->next->data != value ){
		temp = temp->next;
	}
	if(temp->next != NULL){
		node* remove = temp->next;
		temp->next = temp->next->next;
		free(remove);
	}
	return head;
}


void empty(node* head){
	while(head->next != NULL){
		node* temp = head;
		head = head->next;
		free(temp);
	}
}