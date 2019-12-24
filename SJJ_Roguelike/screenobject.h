#ifndef SCREENOBJECT_H
#define SCREENOBJECT_H

#include "CoordinateYX.h"

//ScreenObject is the base class from which other classes inherit
class ScreenObject
{
private:
    char symbol;
    CoordinateYX position;
public:
    //pure virtual function to draw objects to screen
    virtual void print() = 0;

    //get and set functions
    CoordinateYX getPosition();
    void setPosition(CoordinateYX cPos);
    char getSymbol();
    void setSymbol(char cSymb);

    int getYPos();
    int getXPos();
    void setYPos(int yPos);
    void setXPos(int xPos);
};

#endif // SCREENOBJECT_H
