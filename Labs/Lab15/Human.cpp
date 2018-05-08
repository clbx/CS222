#include <cstdlib>
#include <cstring>
#include <iostream>
#include "Human.h"

using namespace std;


/* Default Constructor */
Human::Human(void)
{
  name = "Bruce Campbell";
  strength = HUMAN_DEFAULT_STRENGTH;
}


/**
 * TODO:	Store the input name into the  member variable name, and do
 *      	the same with strength.
 * Hint:	Don't forget the this keyword.
 **/
Human::Human(const string &name, int strength)
{
	this->name = name;
	this->strength = strength;
}

/**
 * TODO:	Nothing really needs to be done here.
 *
 **/
Human::~Human(void)
{
}

/**
 * TODO:	Return the human's name.
 **/
string Human::getName()
{
	return name;
}

/**
 * TODO:	Return the strength variable.
 **/
int Human::getStrength()
{
	return strength;
}

/**
 * TODO: 	Because the human is alive, he or she is healing.
 * 			If the human's strength is less than HUMAN_DEFAULT_STRENGTH, increase their strength by 1.
 * 			Then reduce the human's strength by the damage parameter.
 * 			Return the new strength.
 **/
int Human::hurt(int damage)
{
	if(strength < HUMAN_DEFAULT_STRENGTH)
		strength++;
	strength = strength - damage;
	return strength;
}


/**
 * TODO:	Generate a random number between 1 and 10.
 * 			If the number is between 2 and 9, inclusive, return the value.
 * 			If the number is 1, it's a critical miss.  Print "*Critical miss!* " and return 0.
 * 			If the number is 10, it's a critical hit.  Print "*Critical hit!* " and return 20.
 **/

int Human::makeAttack()
{
	int num = rand()%10+1;
	if(num == 1){
		cout << "*Critical miss!* ";
		return 0;
	}
	else if(num == 10){
		cout << "*Critical hit!* ";
		return 20;
	}
	else
		return num;
}
