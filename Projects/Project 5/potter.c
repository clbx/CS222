#include "Student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct node
{
  struct node* left;
  struct node* right;
  int data;
} node;


node* newNode(int data);
node* insert(node* branch, int data);
void print(node* branch);
node* search(node* branch, int data);
node* remove(node* branch, int data);

int main(int argc, char** argv)
{
  node* root = (node*)malloc(sizeof(node));
  root->left = NULL;
  root->right = NULL;
  root->data = 25;



  insert(root, 10);
  insert(root, 20);
  insert(root, 60);
  insert(root, 12);
  insert(root, 50);
  insert(root, 5);

  print(root);

  int lookFor = 1243;

  if(search(root, lookFor) != NULL)
    printf("%d", search(root, lookFor)->data);
  else
    printf("%d", 0);

  printf("\n");
}

void print(node* branch)
{
  if(branch != NULL)
  {
    print(branch->left);
    printf("%d ", branch->data);
    print(branch->right);
  }

}

node* insert(node* branch,int data)
{
  if(branch == NULL)
    return newNode(data);
  if(data < branch->data)
    branch->left = insert(branch->left, data);
  else if(data > branch->data)
    branch->right = insert(branch->right, data);
}

node* search(node* branch, int data)
{
  if(branch == NULL)
  {
    return NULL;
  }
  else if(branch->data == data)
    return branch;
  else if(data<branch->data)
    return search(branch->left, data);
  else
    return search(branch->right, data);
}

node* remove(node* branch, int data)
{
  
}

node* newNode(int data)
{
  node* branch = (node*)malloc(sizeof(node));
  branch->data = data;
  branch->left = NULL;
  branch->right = NULL;
  return branch;
}
