#include "Student.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Student* newStudent(char* first, char* last, int points, int year, House house);
Student* insert(Student* root, Student* node);
Student* search(Student* root, char* first, char* last);
Student* removeStudent(Student* root, char* first, char* last);
void printStudent(Student* root);
int nameCmp(char* first1, char* last1, char* first2, char* last2);
Student* findSmallest(Student* root, Student* parent);
House findHouse(char* houseName);
void load(Student** Houses, char* filename);
void printAll(Student** Houses,int order);
void printhelp();
void inOrder(Student* root);
void preOrder(Student* root);
void postOrder(Student* root);
int printScores(Student* root);
void saveHouse(FILE* file, Student* root);
void clearRoster(Student* root);

int main(int argc, char** argv)
{
	Student* Houses[5];

	Houses[GRYFFINDOR] = NULL;
	Houses[RAVENCLAW] = NULL;
	Houses[HUFFLEPUFF] = NULL;
	Houses[SLYTHERIN] = NULL;
	Houses[4] = NULL;    //Dead;

	/*COMMAND STRUCTURE*/
	int quit = 1;

	char cmdString[50];


	while(quit){

		int validFlag = 1;

		printf("Enter your command: ");
		scanf("%s", cmdString);

		//HELP
		if(strcmp(cmdString, "help") == 0)
		{
			printhelp();
		}
		//LOAD
		else if(strcmp(cmdString, "load") == 0)
		{
			char filename[50];
			scanf("%s", filename);
			load(Houses, filename);
		}
		//SAVE
		else if(strcmp(cmdString, "save") == 0)
		{
			char filename[50];
			scanf("%s", filename);
			int i;
			FILE* file = fopen(filename,"r+");
			if(file == NULL){
				printf("Save Failed. Invalid File <%s>\n", filename);
			}
			else
			{
				for(i = GRYFFINDOR; i <= DEAD; i++)
					saveHouse(file, Houses[i]);
				printf("Successfully saved data to the file %s\n", filename);
			}
			fclose(file);

		}
		//CLEAR
		else if(strcmp(cmdString, "clear") == 0)
		{
			int i;
			for(i = GRYFFINDOR; i <=DEAD; i++){
				clearRoster(Houses[i]);
				Houses[i] = NULL;
			}

		}
		//INORDER
		else if(strcmp(cmdString, "inorder") == 0)
		{
			printAll(Houses, 1);
			printf("\n\n\n");
		}
		//PREORDER
		else if(strcmp(cmdString, "preorder") == 0)
		{
			printAll(Houses, 2);
			printf("\n\n\n");
		}
		//POSTORDER
		else if(strcmp(cmdString, "postorder") == 0)
		{
			printAll(Houses, 3);
			printf("\n\n\n");
		}
		//ADD
		else if(strcmp(cmdString, "add") == 0)
		{
			char first[50];
			char last[50];
			char house[50];
			int points;
			int year;
			House sHouse;
			validFlag = 1;

			scanf("%s%s%d%d%s",first, last, &points, &year, house);
			sHouse = findHouse(house);
			if(sHouse == -1)
			{
				printf("Add failed. Invalid house: %s\n", house);
				validFlag = 0;
			}
			else if(year < 1 || year > 6){
				printf("Add failed. Invalid year %d\n", year);
				validFlag = 0;
			}
			else if(validFlag)
			{
				Student* nStudent = newStudent(first, last, points, year, sHouse);
				Student* temp = search(Houses[sHouse], first, last);
				if(temp == NULL)
				{
					Houses[sHouse]  = insert(Houses[sHouse], nStudent);
					printf("Added %s %s to roster\n", first, last);
				}
				else{
					printf("Add failed. Student named %s %s already present in roster.\n", first, last);
				}
			}

		}
		//KILL
		else if(strcmp(cmdString, "kill") == 0)
		{
			char first[50];
			char last[50];
			char house[50];
			validFlag = 1;
			House sHouse;

			scanf("%s%s%s", first, last, house);
			sHouse = findHouse(house);
			if(sHouse == -1)
			{
				printf("Kill failed. Invalid house %s\n", house);
				validFlag = 0;
			}
			if(validFlag)
			{
				Student* temp = search(Houses[sHouse], first, last);
				if(temp != NULL)
				{
					Houses[sHouse] = removeStudent(Houses[sHouse], first, last);
					Houses[DEAD] = insert(Houses[DEAD], temp);
					printf("Moved %s %s to the list of deceased students.\n", first, last);
				}
				else{
					printf("Kill failed: %s %s was not found in %s house\n", first, last, house);
				}
			}


		}
		//FIND
		else if(strcmp(cmdString, "find") == 0)
		{
			char first[50];
			char last[50];
			char house[50];
			House sHouse;
			int validFlag = 1;
			scanf("%s%s%s", first, last, house);
			sHouse = findHouse(house);
			if(sHouse == -1){
				printf("Find failed. Invalid house: %s\n", house);
				validFlag = 0;
			}
			if(validFlag)
			{
				Student* temp = search(Houses[sHouse],first, last);
				if(temp != NULL){
					printStudent(temp);
				}
				else
					printf("Find failed. %s %s was not found in %s\n", first, last, house);
			}
		}
		//POINTS
		else if(strcmp(cmdString, "points") == 0)
		{
			char first[50];
			char last[50];
			char house[50];
			House sHouse;
			int points;
			int validFlag = 1;

			scanf("%s%s%s%d", first, last, house, &points);
			sHouse = findHouse(house);
			if(sHouse == -1){
				printf("Point change failed. Invalid house: %s\n", house);
				validFlag = 0;
			}
			if(validFlag){
				Student* temp = search(Houses[sHouse], first, last);
				if(temp != NULL)
				{
					temp->points = points;
					printf("Points for %s %s changed to %d\n", first, last, points);
				}
				else{
					printf("Point change failed. %s %s was not found in %s\n", first, last, house);
				}
			}


		}
		//SCORE
		else if(strcmp(cmdString, "score") == 0)
		{
			int scores[4];
			int i;
			for(i = GRYFFINDOR; i <= SLYTHERIN; i++)
			{
				scores[i]= printScores(Houses[i]);
				printf("%-10s House:\t %d\n", HOUSE_NAMES[i], scores[i]);
			}

		}
		//QUIT
		else if(strcmp(cmdString, "quit") == 0)
		{
			int i;
			for(i = GRYFFINDOR; i <=DEAD; i++){
				clearRoster(Houses[i]);
				Houses[i] = NULL;
			}
			printf("All data cleared.\n");
			quit = 0;

		}
		else
		{
			printf("Unknown Command %s\n", cmdString);
		}
	}


}

void load(Student** Houses, char* filename)
{
	FILE* file = fopen(filename,"r+");
	if(file == NULL){
		printf("Load Failed. Invalid File <%s>\n", filename);
		return;
	}

	char first[100];
	char last[100];
	char house[100];
	int year=1;
	int points=0;
	House sHouse;
	Student* nStudent;

	//LOOP THROUGH THIS
	int filesRead=5;
	int validAdd = 1;
	while(filesRead == 5)
	{
		validAdd = 1;
		filesRead = fscanf(file, "%s %s %d %d %s",first, last, &points, &year, house);
		if(filesRead == 5)
		{

			sHouse = findHouse(house);

			if(year < 1 || year > 6)
			{
				printf("Add Failed: Invalid Year %d\n", year);
				validAdd = 0;
			}
			//Check to see if it's a legal house.
			else if(sHouse == -1){
				printf("Add Failed: Invalid House: %s\n", house);
				validAdd = 0;
			}
			//Check to see if student is already in the tree.
			else if(sHouse != -1){
				Student* temp = search(Houses[sHouse], first, last);
				if(temp != NULL)
				{
					printf("Add failed: Student named %s %s already present in roster\n", first, last);
					validAdd = 0;
				}
			}

			if(validAdd)
			{
				nStudent = newStudent(first, last, points, year, sHouse);
				Houses[sHouse] = insert(Houses[sHouse], nStudent);
			}
		}
	}
	printf("Successfully loaded data from file %s\n", filename);
	fclose(file);
}

void saveHouse(FILE* file, Student* root){
	if(root != NULL)
	{
		saveHouse(file, root->right);
		fprintf(file, "%s %s %d %d %s\n",root->first, root->last, root->points, root->year, HOUSE_NAMES[root->house]);
		saveHouse(file, root->left);
	}
}


void printAll(Student** Houses, int order)
{
	int i;
	for(i = GRYFFINDOR; i <= SLYTHERIN+1; i++){
		printf("\n%s\n", HOUSE_NAMES[i]);
		printf("\n");
		if(order == 1)
			inOrder(Houses[i]);
		else if(order == 2)
			preOrder(Houses[i]);
		else
			postOrder(Houses[i]);
	}
}



int printScores(Student* root){
	int sum = 0;
	if(root != NULL)
	{
		sum += printScores(root->left);
		sum += root->points;
		sum += printScores(root->right);
	}
	return sum;
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



void inOrder(Student* root){
	if(root != NULL)
	{
		inOrder(root->left);
		printStudent(root);
		inOrder(root->right);
	}
}

void preOrder(Student* root){
	if(root != NULL){
		printStudent(root);
		preOrder(root->left);
		preOrder(root->right);
	}
}

void postOrder(Student* root){
	if(root != NULL)
	{
		preOrder(root->left);
		preOrder(root->right);
		printStudent(root);
	}
}

void clearRoster(Student* root){
	if(root != NULL)
	{
		clearRoster(root->left);
		clearRoster(root->right);
		free(root);
	}
}


//Prints out an individual students information
void printStudent(Student* root)
{
  printf("%-10s %-15s \tPoints: %-5d  Year: %d House: %s\n", root->first, root->last, root->points, root->year, HOUSE_NAMES[root->house]);
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
		{
			root->right = NULL;
			return root->right;
		}
		else if(root->right == NULL)
		{
			root->left = NULL;
			return root->left;
		}
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

void printhelp(){
	printf("help\nPrints this display\n\n");
	printf("load <filename>\nAdds the contents of a file to the current roster\n\n");
	printf("save <filename>\nSaves the current roster to a file\n\n");
	printf("clear\nCleat the corrent roster\n\n");
	printf("inorder\nPrint out an inorder traversal of the roster for each house\n\n");
	printf("preorder\nPrint out a preorder traversal of the roster for each house\n\n");
	printf("postorder\nPrint out a postorder traversal of the roster for each house\n\n");
	printf("add <firstname> <lastname> <points> <year> <house>\nAdds a student to the roster\n\n");
	printf("kill <firstname> <lastname> <house>\nMoves a student to the deceased list\n\n");
	printf("find <firstname> <lastname> <house>\nSearches for a student in a house\n\n");
	printf("points <firstname> <lastname> <house>\nChanges the points a student has earned by the specified amount\n\n");
	printf("score\nLists the point totals for all four houses\n\n");
	printf("quit\nQuits the program\n\n");
	return;
}
