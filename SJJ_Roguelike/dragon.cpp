#include <curses.h>

#include "Dragon.h"
#include "CoordinateYX.h"
#include "RoguelikeFunctions.h"

//Name: print(), overrides pure virtual print() function in Enemy
//Arguments: none
//Processing: prints each Dragon object in yellow at its current position
//Output: none (void)
void Dragon::print()
{
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    CoordinateYX location = this->getPosition();
    int yPos{location.y}, xPos{location.x};

    mvprintw(yPos, xPos, "%c", this->getSymbol());

    refresh();
    attroff(COLOR_PAIR(1));
}

//Name: attack()
//Arguments: heroPos (Rogue's position), wallPos (the Coordinates of the walls), borderPos (the Coordinates of the borders), and enemyPos (the Coordinates of the enemies)
//Processing: moves the Dragon (by 3 units) towards the Rogue in order to attack; PLEASE NOTE: if the calculated nextPos overlaps with an obstacle or another enemy, the enemy will NOT move
//Output: none (void)
void Dragon::attack(CoordinateYX heroPos, const std::vector<CoordinateYX>& wallPos, const std::vector<CoordinateYX>& borderPos, const std::vector<CoordinateYX> &enemyPos)
{
    CoordinateYX currentPos{this->getPosition()}, nextPos;

    setPrevPosition(this->getPosition()); //how to deal with converging enemies

    if((heroPos.y != currentPos.y) || (heroPos.x != currentPos.x))
    {
        if(heroPos.y > currentPos.y && heroPos.x == currentPos.x)
        {
            nextPos = futurePos(currentPos, "D", 3);
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "DOWN", 3);
        }
        else if(heroPos.y < currentPos.y && heroPos.x == currentPos.x)
        {
            nextPos = futurePos(currentPos, "U", 3); //fix, make more intuitive
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "UP", 3);
        }
        else if(heroPos.y == currentPos.y && heroPos.x > currentPos.x)
        {
            nextPos = futurePos(currentPos, "R", 3); //fix, make more intuitive
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "RIGHT", 3);
        }
        else if(heroPos.y == currentPos.y && heroPos.x < currentPos.x)
        {
            nextPos = futurePos(currentPos, "L", 3); //fix, make more intuitive
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "LEFT", 3);
        }
        else if(heroPos.y > currentPos.y && heroPos.x > currentPos.x)
        {
            nextPos = futurePos(currentPos, "DR", 3); //fix, make more intuitive
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "BOTTOMRIGHT", 3);
        }
        else if(heroPos.y > currentPos.y && heroPos.x < currentPos.x)
        {
            nextPos = futurePos(currentPos, "DL", 3); //fix, make more intuitive
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "BOTTOMLEFT", 3);
        }
        else if(heroPos.y < currentPos.y && heroPos.x > currentPos.x)
        {
            nextPos = futurePos(currentPos, "UR", 3); //fix, make more intuitive
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "TOPRIGHT", 3);
        }
        else if(heroPos.y < currentPos.y && heroPos.x < currentPos.x)
        {
            nextPos = futurePos(currentPos, "UL", 3); //fix, make more intuitive
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "TOPLEFT", 3);
        }
    }

    this->resetPrev();
}

//Constructor (no position)
Dragon::Dragon()
{
    this->setSymbol('$');
    this->setHealth(20);
    this->setAttackPow(6);
}

//Constructor (with position)
Dragon::Dragon(int y, int x)
{
    this->setSymbol('$');
    this->setHealth(20);
    this->setAttackPow(6);

    this->setYPos(y);
    this->setXPos(x);
}
