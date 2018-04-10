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
Student* findSmallest(Student* root, Student* parent);
House findHouse(char* houseName);
void Load(Student** Houses);
void printAll(Student** Houses);
Student* kill(char* first, char* last, Student* root);


int main(int argc, char** argv)
{
	Student* Houses[5];

	Houses[GRYFFINDOR] = NULL;
	Houses[RAVENCLAW] = NULL;
	Houses[HUFFLEPUFF] = NULL;
	Houses[SLYTHERIN] = NULL;
	Houses[4] = NULL;    //Dead;



	Load(Houses);
	printAll(Houses);

	printf("==================\n");
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
		if(filesRead == 5)
		{
			sHouse = findHouse(house);
			nStudent = newStudent(first, last, points, year, sHouse);
			Houses[sHouse] = insert(Houses[sHouse], nStudent);
		}
	}
}

void printAll(Student** Houses)
{
	int i;
	for(i = GRYFFINDOR; i <= SLYTHERIN+1; i++){
		print(Houses[i]);
	}
}

House findHouse(char* houseName)
{

	int i = 0;
	for(i = GRYFFINDOR; i <= SLYTHERIN; i++){
		if(strcmp(houseName,HOUSE_NAMES[i]) == 0)
	  	return (House)i;
	}
	return (House)-1;
}

//Inserts a student into the tree
Student* insert(Student* root, Student* node)
{
  if(root == NULL)
  {
    return node;
  }
	int nameAmt = nameCmp(node->first, node->last, root->first, root->last);
  if(nameAmt < 0)
    root->left = insert(root->left, node);
  else if(nameAmt > 0)
    root->right = insert(root->right, node);

	return root;
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
	int lastCmp = strcmp(last1, last2);
	if(lastCmp == 0){
		return strcmp(first1, first2);
	}
	return lastCmp;
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
    return NULL;

	int nameAmt = nameCmp(first, last, root->first, root->last);

	if(nameAmt ==0)
	{
		if(root->left == NULL)
			return root->right;
		else if(root->right == NULL)
			return root->left;
		else
		{
			Student* temp = findSmallest(root->right, root);
			temp->left = root->left;
			temp->right = root->right;
			root->left = NULL;
			root->right = NULL;
			return temp;
		}
	}

	else if(nameAmt < 0)
		root->left = removeStudent(root->left, first, last);
	else
		root->right = removeStudent(root->right, first, last);

	return root;
}

//Finds the smallest node in the tree
Student* findSmallest(Student* root, Student* parent)
{
  while(root->left != NULL)
	{
		parent = root;
    root = root -> left;
	}

	if(parent->right == root)
	{
		parent->right = root->right;
	}
	else
	{
		parent->left = root->right;
	}

	return root;
}

Student* kill(Student** Houses, char* first, char* last, char* sHouse){
	House house = findHouse(sHouse);
	Student* temp = search(Houses[house], first, last);
	Houses[GRYFFINDOR] = removeStudent(Houses[GRYFFINDOR], "Harry", "Potter");
	Houses[4] = insert(Houses[4], temp);
}
