#include "Student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Student* newStudent(char* first, char* last, int points, int year, House house);
Student* insert(Student* root, Student* node);
void print(Student* root);
Student* search(Student* root, char* first, char* last);
Student* removeStudent(Student* root, char* first, char* last);
void printStudent(Student* root);
int nameCmp(char* first1, char* last1, char* first2, char* last2);
Student* findSmallest(Student* root);
House findHouse(char* houseName);
void Load(Student** Houses);
void printAll(Student** Houses);


int main(int argc, char** argv)
{
	Student** Houses = (Student**)malloc(sizeof(Student*)*5);
  Student* Gryf = (Student*)malloc(sizeof(Student));
  Student* Rave = (Student*)malloc(sizeof(Student));
  Student* Huff = (Student*)malloc(sizeof(Student));
  Student* Slyt = (Student*)malloc(sizeof(Student));
	Student* Dead = (Student*)malloc(sizeof(Student));

	Houses[0] = Gryf;
	Houses[1] = Rave;
	Houses[2] = Huff;
	Houses[3] = Slyt;
	Houses[4] = Dead;

  Gryf = NULL;
  Rave = NULL;
  Huff = NULL;
  Slyt = NULL;
	Dead = NULL;

	Load(Houses);
	printAll(Houses);


}

void Load(Student** Houses)
{
	FILE* file = fopen("roster.txt","rb");


	char first[100];
	char last[100];
	char house[100];
	int year=1;
	int points=0;
	House sHouse;
  Student* nStudent;

	//LOOP THROUGH THIS
	int filesRead=5;
  while(filesRead == 5)
	{
		filesRead = fscanf(file, "%s %s %d %d %s",first, last, &points, &year, house);
		sHouse = findHouse(house);
		nStudent = newStudent(first, last, points, year, sHouse);
		if(nStudent->house == GRYFFINDOR)
		{
    	Houses[GRYFFINDOR] = insert(Houses[GRYFFINDOR], nStudent);
    }
		else if(nStudent->house == RAVENCLAW)
    	Houses[RAVENCLAW] = insert(Houses[RAVENCLAW], nStudent);
		else if(nStudent->house == HUFFLEPUFF)
			Houses[HUFFLEPUFF] = insert(Houses[HUFFLEPUFF], nStudent);
		else if(nStudent->house == SLYTHERIN)
			Houses[SLYTHERIN] = insert(Houses[SLYTHERIN], nStudent);
  }
}

void printAll(Student** Houses)
{
	printf("GRYFFINDOR\n");
	print(Houses[GRYFFINDOR]);
	printf("RAVENCLAW\n");
	print(Houses[RAVENCLAW]);
  printf("HUFFLEPUFF\n");
	print(Houses[HUFFLEPUFF]);
	printf("SLYTHERIN\n");
	print(Houses[SLYTHERIN]);
}

House findHouse(char* houseName)
{
	if(strcmp(houseName,"Gryffindor") == 0)
  	return GRYFFINDOR;
  else if(strcmp(houseName,"Hufflepuff") == 0)
    return HUFFLEPUFF;
  else if(strcmp(houseName,"Slytherin") == 0)
    return SLYTHERIN;
  else if(strcmp(houseName,"Ravenclaw") == 0)
    return RAVENCLAW;
}

//Inserts a student into the tree
Student* insert(Student* root, Student* node)
{
  if(root == NULL)
  {
    return node;
  }
	int nameAmt = nameCmp(root->first, root->last, node->first, node->last);
  if(nameAmt > 0)
    root->left = insert(root->left, node);
  else if(nameAmt < 0)
    root->right = insert(root->right, node);
}


//Searches through the tree looking for students
Student* search(Student* root, char* first, char* last)
{
  if(root == NULL)
    return NULL;
	int nameAmt = nameCmp(first, last, root->first, root->last);

	if(nameAmt ==0)
	{
     return root;
	}
  else if(nameAmt < 0)
	{
		return search(root->left, first, last);
	}
	else
	{
		return search(root->right, first, last);
	}
}


//Compares names too see which ones come alphabetically first
int nameCmp(char* first1, char* last1, char* first2, char* last2)
{
  char* name1 = (char*)malloc(sizeof(char));
  name1 = strcat(name1, last1);
  name1 = strcat(name1, first1);
	char* name2 = (char*)malloc(sizeof(char));
	name2 = strcat(name2,last2);
	name2 = strcat(name2,first2);

	int cmpAmt = strcmp(name1, name2);
  return cmpAmt;
}


//Prints out an entire tree of students
void print(Student* root)
{
  if(root != NULL)
  {
    print(root->left);
    printStudent(root);
    print(root->right);
  }
}


//Prints out an individual students information
void printStudent(Student* root)
{
  printf("%s %s (Year: %d) - Points: %d, House %s\n", root->first, root->last, root->year, root->points, HOUSE_NAMES[root->house]);
}


//Creates a new student
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


//Removes a student from the tree
Student* removeStudent(Student* root, char* first, char* last)
{
	if(root == NULL)
    return root;

}

//Finds the smallest node in the tree
Student* findSmallest(Student* root)
{
  Student* current = root;
  while(current->left != NULL)
    current = current -> left;

  return current;
}
