#include <iostream>
#include <ctime>
#include <cstdlib>
#include "Zombie.h"
#include "Human.h"

using namespace std;

int battle(Human*, Zombie*);

int main()
{
	srand((unsigned long)time(NULL));

   /**
	* TODO: Declare a string and an int value.
	* 		Prompt the user to enter a zombie name and a zombie strength.
	*		Read these values into the variables you have declared.
	*		Dynamically allocate a new Zombie, passing it the name and the strength value.
	*		Store a pointer to this new Zombie in a Zombie* called zombie.
	* NOTE: You are not allowed to use malloc().
	*		Use cin and cout for input and output.
	*		getline() can get a line of data, allowing for names with spaces in them.
	*		Normally, you wouldn't need to dynamically allocate the zombie.
	*		I'm forcing you to do so for practice with new.
	**/
	int zStrength;
	string zName;
	cout << "Please enter the zombie strength ";
	cin >> zStrength;
	cin.ignore();
	cout << "Please enter a zombie name ";
	getline(cin, zName);
	Zombie* zombie = new Zombie(zName, zStrength);
   /**
	* TODO: Declare a string and an int value.
	* 		Prompt the user to enter a human name and a human strength.
	*		Read these values into the variables you have declared.
	*		Dynamically allocate a new Human, passing it the name and the strength value.
	*		Store a pointer to this new Human in a Human* called human.
	* NOTE: You are not allowed to use malloc().
	*		Use cin and cout for input and output.
	*		getline() can get a line of data, allowing for names with spaces in them.
	*		Normally, you wouldn't need to dynamically allocate the human.
	*		I'm forcing you to do so for practice with new.
	**/
	int hStrengh;
	string hName;
	cout << "Please enter the human strength ";
	cin >> hStrengh;
	cin.ignore();
	cout << "Please enter a human name ";
	getline(cin, hName);
	Human* human = new Human(hName,hStrengh);


   //Simulates battle between the human and the zombie
	battle(human, zombie);

	delete zombie;
	delete human;

	return 0;
}



/**
 * The battle method takes in a Zombie pointer and a Human pointer.
 * They will take turns fighting until one of them is dead.
 * The human goes first.
 **/

int battle(Human* human, Zombie * zombie)
{
	int zombieStrength = zombie->getStrength(); // zombie's strength
	int humanStrength = human->getStrength(); //  human's strength
	int turn = 0;  // whose turn is it
	int damage;

	while( zombieStrength > 0 && humanStrength > 0 )
	{
		cout << "Turn " << (turn + 1) << ": ";

		if( turn % 2 == 0 )
		{
			damage = human->makeAttack();
			zombieStrength = zombie->hurt(damage);
			cout << human->getName();
			cout << " hit " <<
			zombie->getName();
		}
		else
		{
			damage = zombie->makeAttack();
			humanStrength = human->hurt(damage);
			cout << zombie->getName();
			cout << " hit " <<
			human->getName();
		}

		cout << " for " << damage << " points of damage." << endl;
		turn++;
	}

	cout << endl;

	if(zombieStrength < 0 )
	{
		cout << "The zombie " << zombie->getName();
		cout << " was defeated by the human " << human->getName();
		cout << "!"<<endl;
		return 1;
	}
	else
	{
		cout << "The human " << human->getName();
		cout << " was defeated by the zombie " << zombie->getName();
		cout << "!" << endl;
		return 0;
	}
}
