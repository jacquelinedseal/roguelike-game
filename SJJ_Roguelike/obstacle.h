#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "ScreenObject.h"

//Obstacle class derived from ScreenObject class
class Obstacle : public ScreenObject
{
public:
    //prints the obstacles
    virtual void print() override;

    //constructors
    Obstacle();
    Obstacle(int y, int x);
};

#endif // OBSTACLE_H
