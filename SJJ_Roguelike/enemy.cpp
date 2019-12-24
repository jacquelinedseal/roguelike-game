#include <curses.h>

#include "Enemy.h"
#include "coordinateYX.h"

void Enemy::print()
{
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    CoordinateYX location = this->getPosition();
    double yPos{location.y}, xPos{location.x};

    mvprintw((yPos), (xPos) - 0.5, "%c", this->getSymbol());

    refresh();
    attroff(COLOR_PAIR(1));
}
//RANDOM POSITIONS? NEED POS ARGUMENTS...?
Enemy::Enemy(int userH, char eSym, int yPos, int xPos)
{
    this->setSymbol(eSym);
    this->setHealth(userH);
    this->setAttackPow(5);
}
Enemy::Enemy(int userH, char eSym)
{
    this->setSymbol(eSym);
    this->setHealth(userH);
    this->setAttackPow(5);
}
Enemy::Enemy()
{
    this->setSymbol('&');
    this->setHealth(10);
    this->setAttackPow(5);
}
//ENEMY MOVEMENT - JANE
