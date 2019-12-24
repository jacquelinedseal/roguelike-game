#ifndef ROGUE_H
#define ROGUE_H

#include "Character.h"

//Rogue class derived from Character class
class Rogue : public Character
{
public:
    //prints the Rogue
    void print() override;

    //constructor
    Rogue();

    //specialized (non-conventional) print function to be used only when Rogue is attacked
    void printR();
};

#endif // ROGUE_H
