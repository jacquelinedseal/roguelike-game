#ifndef CHARACTER_H
#define CHARACTER_H

#include "ScreenObject.h"

//Character inherits from ScreenObject
class Character : public ScreenObject
{
private:
    int health;
    int attackPow;

    //prevPosition is not needed in ScreenObject (only Characters can move / have a previous position)
    CoordinateYX prevPosition;
public:
    //get and set functions
    int getHealth();
    void setHealth(int cHealth);
    int getAttackPow();
    void setAttackPow(int cAttackPow);
    CoordinateYX getPrevPosition();
    void setPrevPosition(CoordinateYX prevPos);

    //erases character in previous position (after character moves)
    void resetPrev();

    //changes health when character attacked
    void loseHealth(int cHealth);

    //for character movement
    void moveRight();
    void moveLeft();
    void moveUp();
    void moveDown();
    void moveTopRight();
    void moveTopLeft();
    void moveBottomRight();
    void moveBottomLeft();

    void stepBack();

    //for drawing the character to screen
    virtual void print() = 0;
};

#endif // CHARACTER_H
