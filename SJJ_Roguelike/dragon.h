#ifndef DRAGON_H
#define DRAGON_H

#include <vector>

#include "Enemy.h"

//Dragon class derived from Enemy class
class Dragon : public Enemy
{
public:
    //prints the dragon to the screen (overrides pure virtual print() function)
    virtual void print() override;

    //moves the Dragon to attack the Rogue (by 3 units at a time)
    virtual void attack(CoordinateYX heroPos, const std::vector<CoordinateYX> &wallPos, const std::vector<CoordinateYX> &borderPos, const std::vector<CoordinateYX> &enemyPos) override;

    //constructors
    Dragon();
    Dragon(int y, int x);
};

#endif // DRAGON_H
