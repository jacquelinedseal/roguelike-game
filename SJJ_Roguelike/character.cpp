#include <curses.h>
#include "Character.h"

//retrieves Character's current health
int Character::getHealth()
{
    return health;
}

//assigns cHealth as Character's health
void Character::setHealth(int cHealth)
{
    health = cHealth;
}

//retrieves Character's attack power
int Character::getAttackPow()
{
    return attackPow;
}

//assigns cAttackPow as Character's attack power
void Character::setAttackPow(int cAttackPow)
{
    attackPow = cAttackPow;
}

//retrieves Character's current position
CoordinateYX Character::getPrevPosition()
{
    return prevPosition;
}

//assigns prevPos as Character's previous position
void Character::setPrevPosition(CoordinateYX prevPos)
{
    prevPosition = prevPos;
}

//Name: resetPrev
//Arguments: none
//Processing: prints a blank character to overwrite Character's previous position on screen (prevent "trailing characters" effect)
//Output: none(void)
void Character::resetPrev()
{
    start_color();
    init_pair(1, COLOR_BLACK, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    mvprintw(prevPosition.y, prevPosition.x, "%c", ' ');

    attroff(COLOR_PAIR(1));
    refresh();
}

//Name: lostHealth
//Arguments: cHealth (int)
//Processing: reduces Character's current health by cHealth (to represent attack)
//Output: none
void Character::loseHealth(int cHealth)
{
    health -= cHealth;
}

//moves the Character's position 1 unit right
void Character::moveRight()
{
    this->setXPos(this->getXPos() + 1);
}

//moves the Character's position 1 unit left
void Character::moveLeft()
{
    this->setXPos(this->getXPos() - 1);
}

//moves the Character's position 1 unit up
void Character::moveUp()
{
    this->setYPos(this->getYPos() - 1);
}

//moves the Character's position 1 unit down
void Character::moveDown()
{
    this->setYPos(this->getYPos() + 1);
}

//moves the Character's position diagonally 1 unit up and 1 unit right
void Character::moveTopRight()
{
    this->moveRight();
    this->moveUp();
}

//moves the Character's position diagonally 1 unit up and 1 unit left
void Character::moveTopLeft()
{
    this->moveLeft();
    this->moveUp();
}

//moves the Character's position diagonally 1 unit down and 1 unit right
void Character::moveBottomRight()
{
    this->moveDown();
    this->moveRight();
}

//moves the Character's position diagonally 1 unit down and 1 unit left
void Character::moveBottomLeft()
{
    this->moveDown();
    this->moveLeft();
}

//moves the Character back to its previous position (after attacking)
void Character::stepBack()
{
    this->setPosition(prevPosition);
}
