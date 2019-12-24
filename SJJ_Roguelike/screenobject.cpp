#include "ScreenObject.h"

//retrieves ScreenObject's symbol
char ScreenObject::getSymbol()
{
    return symbol;
}

//assigns cSymb as ScreenObject's symbol
void ScreenObject::setSymbol(char cSymb)
{
    symbol = cSymb;
}

//retrieves ScreenObject's current position
CoordinateYX ScreenObject::getPosition()
{
    return position;
}

//assigns cPos as ScreenObject's current position
void ScreenObject::setPosition(CoordinateYX cPos)
{
    position.y = cPos.y;
    position.x = cPos.x;
}

//assigns yPos as ScreenObject's current y position
void ScreenObject::setYPos(int yPos)
{
    position.y = yPos;
}

//assigns xPos as ScreenObject's current x position
void ScreenObject::setXPos(int xPos)
{
    position.x = xPos;
}

//retrieves ScreenObject's current y-coordinate
int ScreenObject::getYPos()
{
    return position.y;
}

//retrieves ScreenObject's current x-coordinate
int ScreenObject::getXPos()
{
    return position.x;
}
