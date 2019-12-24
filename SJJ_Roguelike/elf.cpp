#include <curses.h>
#include <vector>
#include <iostream>

#include "Elf.h"
#include "Rogue.h"
#include "CoordinateYX.h"
#include "RoguelikeFunctions.h"

//Name: print(), overrides pure virtual print() function in Enemy
//Arguments: none
//Processing: prints each Elf object in cyan at its current position
//Output: none (void)
void Elf::print()
{
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    CoordinateYX location = this->getPosition();
    int yPos{location.y}, xPos{location.x};

    mvprintw(yPos, xPos, "%c", this->getSymbol());

    refresh();
    attroff(COLOR_PAIR(1));
}

//Name: attack()
//Arguments: heroPos (Rogue's position), wallPos (the Coordinates of the walls), borderPos (the Coordinates of the borders), and enemyPos (the Coordinates of the enemies)
//Processing: moves the Elf (by 1 unit) towards the Rogue in order to attack; PLEASE NOTE: if the calculated nextPos overlaps with an obstacle or another enemy, the enemy will NOT move
//Output: none (void)
void Elf::attack(CoordinateYX heroPos, const std::vector<CoordinateYX>& wallPos, const std::vector<CoordinateYX>& borderPos, const std::vector<CoordinateYX>& enemyPos)
{
    CoordinateYX currentPos{this->getPosition()}, nextPos;

    setPrevPosition(this->getPosition());

    if((heroPos.y != currentPos.y) || (heroPos.x != currentPos.x))
    {
        if(heroPos.y > currentPos.y && heroPos.x == currentPos.x)
        {
            nextPos = futurePos(currentPos, "D", 1);
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "DOWN", 1);
        }
        else if(heroPos.y < currentPos.y && heroPos.x == currentPos.x)
        {
            nextPos = futurePos(currentPos, "U", 1); //fix, make more intuitive
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "UP", 1);
        }
        else if(heroPos.y == currentPos.y && heroPos.x > currentPos.x)
        {
            nextPos = futurePos(currentPos, "R", 1); //fix, make more intuitive
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "RIGHT", 1);
        }
        else if(heroPos.y == currentPos.y && heroPos.x < currentPos.x)
        {
            nextPos = futurePos(currentPos, "L", 1); //fix, make more intuitive
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "LEFT", 1);
        }
        else if(heroPos.y > currentPos.y && heroPos.x > currentPos.x)
        {
            nextPos = futurePos(currentPos, "DR", 1); //fix, make more intuitive
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "BOTTOMRIGHT", 1);
        }
        else if(heroPos.y > currentPos.y && heroPos.x < currentPos.x)
        {
            nextPos = futurePos(currentPos, "DL", 1); //fix, make more intuitive
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "BOTTOMLEFT", 1);
        }
        else if(heroPos.y < currentPos.y && heroPos.x > currentPos.x)
        {
            nextPos = futurePos(currentPos, "UR", 1); //fix, make more intuitive
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "TOPRIGHT", 1);
        }
        else if(heroPos.y < currentPos.y && heroPos.x < currentPos.x)
        {
            nextPos = futurePos(currentPos, "UL", 1); //fix, make more intuitive
            if(collisionCheck(nextPos, wallPos, borderPos, enemyPos) == false)
                moveValue(this, "TOPLEFT", 1);
        }
    }

    this->resetPrev();
}

//constructor (no position)
Elf::Elf()
{
    this->setSymbol('&');
    this->setHealth(5);
    this->setAttackPow(2);
}

//constructor (with position)
Elf::Elf(int y, int x)
{
    this->setSymbol('&');
    this->setHealth(5);
    this->setAttackPow(2);

    this->setYPos(y);
    this->setXPos(x);
}

