#ifndef HUMAN_H
#define HUMAN_H

#include <string>

using namespace std;

#define HUMAN_DEFAULT_STRENGTH 50

class Human
{
public:
	/* Constructors */
	Human(void);
	Human(const string &name, int strength);

	/* Destructor */
	virtual ~Human(void);

	string getName();
	int getStrength();

	int hurt(int damage);
	int makeAttack();

private:
	int strength;
	string name;
};

#endif
