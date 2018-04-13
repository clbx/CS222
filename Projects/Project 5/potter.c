/*******************************
*
*  Project Name: Project 5: Trees Worse than Whomping Willows
*  Description: A student record program for Hogwarts School of Witchcraft and Wizardry
*  File names: potter.c Student.h <roster>
*  Date: 04/12/18
*  Authors: Clay Buxton and Lindsey Fasolo
*
*******************************/

/*
TODO: Ask about max cmdString length
TODO: Ask if dead should be printed out
*/


#include "Student.h"																														//Include our stuff
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Student* newStudent(char* first, char* last, int points, int year, House house);
Student* insert(Student* root, Student* node);
Student* search(Student* root, char* first, char* last);
Student* removeStudent(Student* root, char* first, char* last);
void printStudent(Student* root);
int nameCmp(char* first1, char* last1, char* first2, char* last2);
Student* findReplacement(Student* root, Student* parent);
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
	//Array that holds the pointers for all the houses
	Student* Houses[5];
	//Gotta null it all out
	Houses[GRYFFINDOR] = NULL;
	Houses[RAVENCLAW] = NULL;
	Houses[HUFFLEPUFF] = NULL;
	Houses[SLYTHERIN] = NULL;
	Houses[DEAD] = NULL;

	/*COMMAND STRUCTURE*/
	int quit = 1;							//The quit flag, keeps going until this is set to 0
	char cmdString[50];				//The char* that holds the command


	while(quit)
	{

		int validFlag = 1;
		printf("Enter your command: ");
		scanf("%s", cmdString);

		//HELP
		if(strcmp(cmdString, "help") == 0)//
		{
			printhelp();
		}
		//LOAD
		else if(strcmp(cmdString, "load") == 0)
		{
			char filename[50];						//Get the filename character array
			scanf("%s", filename);				//Get in the filename from the user
			load(Houses, filename);				//Load into houses from filename
		}
		//SAVE
		else if(strcmp(cmdString, "save") == 0)
		{
			char filename[50];											//Get the filename character array
			scanf("%s", filename);									//Get filename from the user
			int i;
			FILE* file = fopen(filename,"r+");			//Create the file object
			if(file == NULL)												//If the file doesnt exist, throw an error
			{
				printf("Save Failed. Invalid File <%s>\n", filename);
			}
			else
			{
				for(i = GRYFFINDOR; i <= SLYTHERIN; i++)//But if it's not, then go through all the houses, print to the file
					saveHouse(file, Houses[i]);
				printf("Successfully saved data to the file %s\n", filename);
			}
			fclose(file);

		}
		//CLEAR
		else if(strcmp(cmdString, "clear") == 0)
		{
			int i;
			for(i = GRYFFINDOR; i <=DEAD; i++)			//Run clear on every house
			{
				clearRoster(Houses[i]);
				Houses[i] = NULL;											//Then NULL them out
			}

		}
		//INORDER
		else if(strcmp(cmdString, "inorder") == 0)
		{
			printAll(Houses, 1);				//Calls printAll with the inorder function
			printf("\n\n\n");
		}
		//PREORDER
		else if(strcmp(cmdString, "preorder") == 0)
		{
			printAll(Houses, 2);				//Call printAll with the preorder function
			printf("\n\n\n");
		}
		//POSTORDER
		else if(strcmp(cmdString, "postorder") == 0)
		{
			printAll(Houses, 3);				//Call printAll with the postorder function
			printf("\n\n\n");
		}
		//ADD
		else if(strcmp(cmdString, "add") == 0)
		{
			char first[50];							//Get an array for the first name
			char last[50];							//Get an array for the last name
			char house[50];							//Get an array for the house name
			int points;									//Points
			int year;										//Year
			House sHouse;								//A place for the sHouse
			validFlag = 1;							//The valid flag

			scanf("%s%s%d%d%s",first, last, &points, &year, house);
			sHouse = findHouse(house);														//Get the house type
			if(sHouse == -1)																			//If the house type doesnt exist
			{
				printf("Add failed. Invalid house: %s\n", house);
				validFlag = 0;																			//Set the validFlag to 0 so that the add doesnt happen
			}
			else if(year < 1 || year > 6){												//If the year is invalid
				printf("Add failed. Invalid year %d\n", year);
				validFlag = 0;																			//Set the validFlag to 0
			}
			else if(validFlag)																		//Now make sure that the valid flag is on
			{
				Student* nStudent = newStudent(first, last, points, year, sHouse);			//Call the newStudent function
				Student* temp = search(Houses[sHouse], first, last);										//Search for the Student in the rosters
				if(temp == NULL)																												//If its not in the house then add it
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
			char first[50];								//Array for first name
			char last[50];								//Array for last name
			char house[50];								//Array for house name
			validFlag = 1;
			House sHouse;									//House

			scanf("%s%s%s", first, last, house);
			sHouse = findHouse(house);
			if(sHouse == -1)																									//If sHouse is -1 then the house doesnt exist
			{
				printf("Kill failed. Invalid house %s\n", house);
				validFlag = 0;
			}
			if(validFlag)																											//If valid flag is true then actually go through the kill
			{
				Student* temp = search(Houses[sHouse], first, last);						//Get search for the student
				if(temp != NULL)																								//If it's not in there
				{
					Houses[sHouse] = removeStudent(Houses[sHouse], first, last);	//Remove the student from the house
					temp->right = NULL;																						//Sever the legs of the student going into the dead
					temp->left = NULL;
					Houses[DEAD] = insert(Houses[DEAD], temp);										//Put them in the dead
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
			char first[50];														//Create our Arrays
			char last[50];
			char house[50];
			House sHouse;
			int validFlag = 1;
			scanf("%s%s%s", first, last, house);
			sHouse = findHouse(house);
			if(sHouse == -1){													//Check to see if the house exists
				printf("Find failed. Invalid house: %s\n", house);
				validFlag = 0;
			}
			if(validFlag)															//Make sure there were no errors
			{
				Student* temp = search(Houses[sHouse],first, last);		//Search for the house
				if(temp != NULL){																			//If it was there print it out
					printStudent(temp);
				}
				else
					printf("Find failed. %s %s was not found in %s\n", first, last, house);
			}
		}
		//POINTS
		else if(strcmp(cmdString, "points") == 0)
		{
			char first[50];													//Create our varaibles
			char last[50];
			char house[50];
			House sHouse;
			int points;
			int validFlag = 1;

			scanf("%s%s%s%d", first, last, house, &points);
			sHouse = findHouse(house);
			if(sHouse == -1)												//Make sure the house exists
			{
				printf("Point change failed. Invalid house: %s\n", house);
				validFlag = 0;
			}
			if(validFlag){													//Check if there were errors
				Student* temp = search(Houses[sHouse], first, last);
				if(temp != NULL)											//if not
				{
					temp->points = points;							//change the points
					printf("Points for %s %s changed to %d\n", first, last, points);
				}
				else
					printf("Point change failed. %s %s was not found in %s\n", first, last, house);
			}


		}
		//SCORE
		else if(strcmp(cmdString, "score") == 0)
		{
			int scores[4];														//create an array that will hold the point values
			int i;
			for(i = GRYFFINDOR; i <= SLYTHERIN; i++)			//Since the house names are just integers, we can use them as such and index through the array
			{
				scores[i]= printScores(Houses[i]);          //Get the scores and then put it in the array
				printf("%-10s House:\t %d\n", HOUSE_NAMES[i], scores[i]);	//And print
			}

		}
		//QUIT
		else if(strcmp(cmdString, "quit") == 0)
		{
			int i;
			for(i = GRYFFINDOR; i <=DEAD; i++)	//Clear all of the houses
			{
				clearRoster(Houses[i]);
				Houses[i] = NULL;
			}
			printf("All data cleared.\n");
			quit = 0;														//Reset the quit flag to it exits

		}
		else
		{
			printf("Unknown Command %s\n", cmdString);
		}
	}


}


/* LOAD
   Description: Loads a file into the houses
   Parameters: Student** Houses, the array that contains the houses. char* filename, the file to get them from
   Returns: Nothing
*/
void load(Student** Houses, char* filename)
{
	FILE* file = fopen(filename,"r+");													//Open the file
	if(file == NULL)																						//If file is null then the file didnt exist
	{
		printf("Load Failed. Invalid File <%s>\n", filename);
		return;
	}

	char first[50];																							//Create our variables
	char last[50];
	char house[50];
	int year=1;
	int points=0;
	House sHouse;
	Student* nStudent;

	//LOOP THROUGH THIS
	int filesRead=5;																						//filesRead is how many things is read from the file
	int validAdd = 1;																						//validAdd flag
	while(filesRead == 5)
	{
		validAdd = 1;
		filesRead = fscanf(file, "%s %s %d %d %s",first, last, &points, &year, house);   //Scans first name, last name, points, year, and house
		if(filesRead == 5)
		{

			sHouse = findHouse(house);																								//Get the house

			if(year < 1 || year > 6)																									//Make sure the year is valid
			{
				printf("Add Failed: Invalid Year %d\n", year);
				validAdd = 0;
			}
			//Check to see if it's a legal house.
			else if(sHouse == -1)																											//Make sure the house was valid
			{
				printf("Add Failed: Invalid House: %s\n", house);
				validAdd = 0;
			}
			//Check to see if student is already in the tree.
			else if(sHouse != -1)																											//If everything else checks out
			{
				Student* temp = search(Houses[sHouse], first, last);										//Search for the student
				if(temp != NULL)																												//If it exists then turn off the validAdd
				{
					printf("Add failed: Student named %s %s already present in roster\n", first, last);
					validAdd = 0;
				}
			}

			if(validAdd)																															//If everything checks out
			{
				nStudent = newStudent(first, last, points, year, sHouse);								//Create a new student
				Houses[sHouse] = insert(Houses[sHouse], nStudent);											//And add it to the appropriate house
			}
		}
	}
	printf("Successfully loaded data from file %s\n", filename);
	fclose(file);																																	//Dont forget to close the file
}


/*SAVE HOUSE
   Description: Saves a house to the file
   Parameters: FILE* file, the file which is being written to. Student* root, the tree being read from
   Returns: Nothing
*/
void saveHouse(FILE* file, Student* root){
	if(root != NULL)														//As long as the root exists
	{
		fprintf(file, "%s %s %d %d %s\n",root->first, root->last, root->points, root->year, HOUSE_NAMES[root->house]);		//Write to the file
		saveHouse(file, root->left);							//Recursivly do this to all of the nodes in the tree
		saveHouse(file, root->right);
	}
}

/* PRINT ALL
   Description: Prints all of the students in a specified order
   Parameters:	Student** Houses, the array in which all of the houses are helf. int order, a specifiers for how the students are printed
   Returns:	Nothing
*/
void printAll(Student** Houses, int order)
{
	int i;
	for(i = GRYFFINDOR; i <= SLYTHERIN+1; i++)			//Index through the houses
	{
		printf("\n%s\n", HOUSE_NAMES[i]);
		printf("\n");
		if(order == 1)
			inOrder(Houses[i]);					//if the order is 1, print out in order
		else if(order == 2)
			preOrder(Houses[i]);				//if the order is 2, print out in pre-Order
		else
			postOrder(Houses[i]);				//if the order is 3, print out the post-Order
	}
}


/* PRINT SCORES
   Description: Prints out the scores of a specified house
   Parameters: Student* house, the houses scores to get
   Returns:	int, the total amount of the points from that house
*/
int printScores(Student* root){
	int sum = 0;									//The total amount of points
	if(root != NULL)
	{
		sum += printScores(root->left);			//Recursivly get the total amount of points
		sum += root->points;
		sum += printScores(root->right);
	}
	return sum;
}

/* FIND HOUSE
   Description: Returns a House type house based on the given string
   Parameters: char* houseName, the house being looked for
   Returns: House, the house being looked for
*/
House findHouse(char* houseName)
{

	int i = 0;
	for(i = GRYFFINDOR; i <= SLYTHERIN; i++)				//We can index through the houses
	{
		if(strcmp(houseName,HOUSE_NAMES[i]) == 0)			//And if the house entered is from the HOUSE_NAMES String, it is the house
	  	return (House)i;														//So return that house
	}
	return (House)-1;																//But if it doesnt exist, we return -1
}


/* INSERT
   Description: Inserts a student into the tree
   Parameters: Student* root, the tree that student is being inserted, Student* node, the student being inserted
   Returns:	Student*, the root after the insert
*/
Student* insert(Student* root, Student* node)
{
  if(root == NULL)			//If root is empty or once we get to an empty part of the tree, return node.
  {
    return node;
  }
	int nameAmt = nameCmp(node->first, node->last, root->first, root->last);			//Get the difference between the name of the current node, and the name of the new student
  if(nameAmt < 0)
    root->left = insert(root->left, node);																			//If its less Recursivly call this function until we reach an empty location going left
  else if(nameAmt > 0)
    root->right = insert(root->right, node);																		//If its more Recursivly call this function until we reach an empty location going right

	return root;
}

/* SEARCH
   Description: Searches through a house to find a student
   Parameters: Student* root, the house being looked through, char* first, char* last, the first and last
	 						 name of the student being searched for
   Returns:	Student*, the student being searched for
*/
//Searches through the tree looking for students
Student* search(Student* root, char* first, char* last)
{
  if(root == NULL)
    return NULL;																									 //If the house is empty, or the student eventually could not be found return NULL
	int nameAmt = nameCmp(first, last, root->first, root->last);     //Compare the names of the current node, and the student being searched for

	if(nameAmt ==0)																										//If nameAmt is 0, we found the student and return them
     return root;
  else if(nameAmt < 0)
		return search(root->left, first, last);													//If the compared amount was less than zero we go left
	else
		return search(root->right, first, last);												//If it was more than 0 we go right.
}


/* SEARCH
   Description: Compares 2 names to find out which comes first alphabetically
   Parameters: char* first1, char* last1, the name of the first student, char* first2, char* last2, the name of the second student
   Returns:	int, the comapare value
*/
int nameCmp(char* first1, char* last1, char* first2, char* last2)
{
	int lastCmp = strcmp(last1, last2);				//Compare the last names
	if(lastCmp == 0)													//if they are the same, compare the first names, and return the compare on that
		return strcmp(first1, first2);
	return lastCmp;														//otherwise, just return the compare on the last names
}



/* INORDER
   Description: Prints out the house inorder
   Parameters: Student* root, the House to be printed
   Returns:	Nothing
*/
void inOrder(Student* root){
	if(root != NULL)				//if the current root has students in it
	{
		inOrder(root->left);  //Call itself on the left
		printStudent(root);		//Print the student
		inOrder(root->right);	//Call itself on the right
	}
}

/* PREORDER
   Description: Prints out the house in preorder
   Parameters: Student* root, the House to be printed
   Returns:	Nothing
*/
void preOrder(Student* root){
	if(root != NULL)					//If the current root has students in it
	{
		printStudent(root);			//Print the student
		preOrder(root->left);		//Call itself on the left
		preOrder(root->right);	//Call itself on the right
	}
}

/* POSTORDER
   Description: Prints out the house in postOrder
   Parameters: Student* root, the House to be printed
   Returns:	Nothing
*/
void postOrder(Student* root){
	if(root != NULL)						//If the current root has students in it
	{
		preOrder(root->left);			//Call itself on the left
		preOrder(root->right);		//Call itself on the right
		printStudent(root);				//Print the student
	}
}


/* CLEAR
   Description: Clears the roster
   Parameters: Student* root, the House to be cleared
   Returns:	Nothing
*/
void clearRoster(Student* root){
	if(root != NULL)							//If it's not already empty
	{
		clearRoster(root->left);		//Call itself Recursivly so it clears the whole tree
		clearRoster(root->right);
		free(root->first);					//Free the allocated names
		free(root->last);
		free(root);									//Free itself
	}
}


/* PRINT STUDENT
   Description: Prints the information on an individual student
   Parameters: Student* root, the student to be printed
   Returns:	Nothing
*/
void printStudent(Student* root)
{
  printf("%-10s %-15s \tPoints: %-5d  Year: %d House: %s\n", root->first, root->last, root->points, root->year, HOUSE_NAMES[root->house]);
}


/* NEW STUDENT
   Description: Clears the roster
   Parameters: char* first, char* last, the name of the student, int points, the amount of points the student has
	 						 int year, the year the student is in, House house, the house the student it in.
   Returns:	Nothing
*/
Student* newStudent(char* first, char* last, int points, int year, House house)
{
  Student* student = (Student*)malloc(sizeof(Student));		//Create the student
  student->first = strdup(first);													//Assign all information
  student->last = strdup(last);
  student->points = points;
  student->year = year;
  student->house = house;
  student->left = NULL;
  student->right = NULL;
  return student;
}


/* REMOVE STUDENT
   Description: Removes a student from the roster
   Parameters: Student* root, the roster in which the student will be removed, char* first, char* last, the student to be removed
   Returns:	Student* The adjusted house
*/
Student* removeStudent(Student* root, char* first, char* last)
{
	if(root == NULL)																								//If the roster is empty, or we couldnt find the student, return NULL
    return NULL;

	int nameAmt = nameCmp(first, last, root->first, root->last);		//Get the comparison between the name were looking for and the students name

	if(nameAmt ==0)																									//if it's 0, we found him/her
	{
		if(root->left == NULL)																				//For cases if it's only a parent to one child
		{
			return root->right;
		}
		else if(root->right == NULL)
		{
			return root->left;
		}
		else																													//Otherwise more work needs to be done
		{
			Student* temp = findReplacement(root->right, root);						//Get to the spot we want to get to replace this node
			temp->left = root->left;																		//Replace the node
			temp->right = root->right;
			root->left = NULL;
			root->right = NULL;
			return temp;
		}
	}

	else if(nameAmt < 0)																						//If it doesnt equal the student were looking for, keep looking
		root->left = removeStudent(root->left, first, last);
	else
		root->right = removeStudent(root->right, first, last);

	return root;
}



Student* findReplacement(Student* root, Student* parent)
{
  while(root->left != NULL)														//We need to keep track of the parent to properly replace the node
	{
		parent = root;																		//Navigate to the correct node, to replace the removed node.
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
