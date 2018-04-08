#include "Student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Student* newStudent(char* first, char* last, int points, int year, House house);
Student* insert(Student* root, Student* node);
void print(Student* root);
Student* search(Student* root, char* first, char* last);
Student* removeStudent(Student* root, char* first, char* last);
void printstudent(Student* root);
char* addNames(char* first, char* last);
Student* findSmallest(Student* root);

int main(int argc, char** argv)
{
  //CREATE HOUSES
  Student** GryfPoint;
  Student** RavePoint;
  Student** HuffPoint;
  Student** SlytPoint;

  Student* Gryf = (Student*)malloc(sizeof(Student));
  Student* Rave = (Student*)malloc(sizeof(Student));
  Student* Huff = (Student*)malloc(sizeof(Student));
  Student* Slyt = (Student*)malloc(sizeof(Student));

  Gryf = NULL;
  Rave = NULL;
  Huff = NULL;
  Slyt = NULL;

  GryfPoint = &Gryf;
  RavePoint = &Rave;
  HuffPoint = &Huff;
  SlytPoint = &Slyt;

  Student* Harry = newStudent("Harry", "Potter", 50, 3, GRYFFINDOR);
  *GryfPoint = insert(*GryfPoint, Harry);
  Student* Ron = newStudent("Ron", "Weasley", 150, 3, GRYFFINDOR);
  *GryfPoint = insert(*GryfPoint, Ron);
  Student* Hermione = newStudent("Hermione", "Granger", 500, 3, GRYFFINDOR);
  *GryfPoint = insert(*GryfPoint, Hermione);
  printf("=============\n");
  print(*GryfPoint);
  printf("=============\n");
  printstudent(search(*GryfPoint, "Ron", "Weasley"));
  *GryfPoint = removeStudent(*GryfPoint, "Harry", "Potter");
  printf("=============\n");
  print(*GryfPoint);


}

Student* insert(Student* root, Student* node)
{
  fprintf(stderr, "Gets inside\n");
  if(root == NULL)
  {
    return node;
  }

  if(strcmp(root->last, node->last) > 0)
    root->left = insert(root->left, node);
  else if(strcmp(root->last, node->last) < 0)
    root->right = insert(root->right, node);
}

Student* search(Student* root, char* first, char* last)
{
  char* name = addNames(first, last);
  char* rootName = addNames(root->first, root->last);
  if(root == NULL)
    return NULL;
  else if(strcmp(name, rootName)==0)
	{
     return root;
	}
  else if(strcmp(name, rootName)<0)
	{
		return search(root->left, first, last);
	}
	else
	{
		return search(root->right, first, last);
	}

}

char* addNames(char* first, char* last)
{
  char* name = (char*)malloc(sizeof(char));
  name = strcat(name, last);
  name = strcat(name, first);
  return name;
}

void print(Student* root)
{
  if(root != NULL)
  {
    print(root->left);
    printstudent(root);
    print(root->right);
  }
}

void printstudent(Student* root)
{
  printf("%s %s (Year: %d) - Points: %d, House %s\n", root->first, root->last, root->year, root->points, HOUSE_NAMES[root->house]);
}

Student* newStudent(char* first, char* last, int points, int year, House house)
{
  Student* student = (Student*)malloc(sizeof(Student));
  student->first = strdup(first);
  student->last = strdup(last);
  student->points = points;
  student->year = year;
  student->house = house;
  student->left = NULL;
  student->right = NULL;
  return student;
}

Student* removeStudent(Student* root, char* first, char* last)
{
  char* name = addNames(first, last);
  char* rootName = addNames(root->first, root->last);
  if(root == NULL)
    return root;
  if(strcmp(name, rootName) < 0)
    root->left = removeStudent(root->left, first, last);
  else if(strcmp(name, rootName) > 0)
    root->right = removeStudent(root->right, first, last);
  else
  {
    if(root->left == NULL)
    {
      Student* temp = root->right;
      free(root);
      return temp;
    }
    else if(root->right == NULL)
    {
      Student* temp = root->left;
      free(root);
      return temp;
    }
    Student* temp = findSmallest(root->right);
    root->first = temp->first;
    root->last = temp->last;
    root->right = removeStudent(root->right, first, last);
  }
  return root;

}

Student* findSmallest(Student* root)
{
  Student* current = root;
  while(current->left != NULL)
    current = current -> left;

  return current;
}

//hello
