#ifndef ELF_H
#define ELF_H

#include <vector>

#include "Enemy.h"
#include "Rogue.h"

//Elf class derived from Enemy class
class Elf : public Enemy
{
public:
    //prints the Elf to the screen (overrides pure virtual print() function)
    virtual void print() override;

    //moves the Elf to attack the Rogue (by 1 unit at a time)
    virtual void attack(CoordinateYX heroPos, const std::vector<CoordinateYX>& wallPos, const std::vector<CoordinateYX>& borderPos, const std::vector<CoordinateYX>& enemyPos) override;

    //constructors
    Elf();
    Elf(int y, int x);
};

#endif // ELF_H
