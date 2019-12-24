#include <curses.h>

#include "Obstacle.h"

//Name: print(), overrides pure virtual print() function in ScreenObject
//Arguments: none
//Processing: prints each Obstacle object as a blank white box at its current position
//Output: none (void)
void Obstacle::print()
{
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_WHITE);
    attron(COLOR_PAIR(1));

    CoordinateYX location = this->getPosition();
    int yPos{location.y}, xPos{location.x};

    mvprintw(yPos, xPos, "%c", this->getSymbol());

    refresh();
    attroff(COLOR_PAIR(1));
}

//constructor (no position)
Obstacle::Obstacle()
{
    this->setSymbol(' ');
}

//constructor (with position)
Obstacle::Obstacle(int y, int x)
{
    this->setSymbol(' ');
    this->setYPos(y);
    this->setXPos(x);
}
