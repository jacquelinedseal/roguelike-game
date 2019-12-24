#include <curses.h>

#include "Rogue.h"
#include "CoordinateYX.h"

//Name: print(), overrides pure virtual print() function in Enemy
//Arguments: none
//Processing: prints each Rogue object in green at its current position
//Output: none (void)
void Rogue::print()
{
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    CoordinateYX location = this->getPosition();
    int yPos{location.y}, xPos{location.x};

    mvprintw(yPos, xPos, "%c", this->getSymbol());

    refresh();
    attroff(COLOR_PAIR(1));
}

//constructor
Rogue::Rogue()
{
    this->setSymbol('@');
    this->setHealth(100);
    this->setAttackPow(5);

    //sets the rogue in the center of the screen at the beginning of the program
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);

    this->setYPos(yMax/2);
    this->setXPos(xMax/2 - 1);
}

//Name: printR()
//Arguments: none
//Processing: prints each Rogue object in RED at its current position; used only in specific situation when Rogue is under attack
//Output: none (void)
void Rogue::printR()
{
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    attron(COLOR_PAIR(1));

    CoordinateYX location = this->getPosition();
    int yPos{location.y}, xPos{location.x};

    mvprintw(yPos, xPos, "%c", this->getSymbol());

    refresh();
    attroff(COLOR_PAIR(1));
}
