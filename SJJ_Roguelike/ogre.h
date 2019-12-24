#ifndef OGRE_H
#define OGRE_H

#include <vector>

#include "Enemy.h"

//Ogre class derived from Enemy class
class Ogre : public Enemy
{
public:
    //prints the Ogre to the screen (overrides pure virtual print() function)
    virtual void print() override;

    //moves the Ogre to attack the Rogue (by 2 units at a time)
    virtual void attack(CoordinateYX heroPos, const std::vector<CoordinateYX> &wallPos, const std::vector<CoordinateYX> &borderPos, const std::vector<CoordinateYX> &enemyPos) override;

    //constructors
    Ogre();
    Ogre(int y, int x);
};

#endif // OGRE_H
