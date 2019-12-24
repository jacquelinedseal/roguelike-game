#ifndef ENEMY_H
#define ENEMY_H

#include <vector>

#include "Character.h"
#include "Rogue.h"

//Enemy class inherits from Character
class Enemy : public Character
{
public:
    //pure virtual function for drawing Enemies
    virtual void print() = 0;

    //pure virtual function for Enemy attack pattern
    virtual void attack(CoordinateYX heroPos, const std::vector<CoordinateYX>& wallPos, const std::vector<CoordinateYX>& borderPos, const std::vector<CoordinateYX>& enemyPos) = 0;
};

#endif // ENEMY_H
