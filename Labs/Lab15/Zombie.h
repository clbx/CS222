#ifndef ZOMBIE_H
#define ZOMBIE_H

#include <string>

using namespace std;

#define ZOMBIE_DEFAULT_STRENGTH 75

class Zombie
{
public:
	/* Constructors */
	Zombie(void);
	Zombie(const string &name, int strength);

	/* Destructor */
	virtual ~Zombie(void);

	string getName();
	int getStrength();

	int hurt(int damage);
	int makeAttack();

private:
	int strength;
	string name;
};

#endif
