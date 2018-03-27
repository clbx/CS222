#ifndef STUDENT_H
#define STUDENT_H

#define HOUSES 4

typedef enum { GRYFFINDOR, RAVENCLAW, HUFFLEPUFF, SLYTHERIN } House;
char* HOUSE_NAMES[HOUSES] = {"Gryffindor", "Ravenclaw", "Hufflepuff", "Slytherin"};


typedef struct _Student
{
	char* first;
	char* last;
	int points;
	int year;
	House house;	
	
	struct _Student* left;
	struct _Student* right;

} Student;

#endif