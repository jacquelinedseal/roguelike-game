// CLARIFICATIONS REGARDING PROJECT INTERPRETATION (FOR THE USER):
   //The window is not re-scalable. Changing window size mid-program will cause the objects on screen to disappear.
   //Elves are blue ampersands (&). Ogres are purple percent signs (%). Dragons are yellow dollar signs ($).
   //Elves will move by 1 unit for each move the Rogue makes. Ogres will move by 2. Dragons will move by 3. This means that Ogres and Dragons CAN jump over walls (but not border walls).
   //If the enemy's calculated next position overlaps with an obstacle/another enemy, it will not move. The enemy will remain static until the Rogue moves within range.
   //The enemy count displayed in the stats bar IS accurate. In some cases, it will seem that the count is one more than the number of enemies on screen. This only occurs when the Rogue is attacking (and thus covering) the missing enemy.
   //Elves will die after being attacked once. Ogres will die after being attacked twice. Dragons will die after being attacked three times.
   //Inheritance is used as shown in UML diagram planning. Polymorphism used for printEnemy(), printScreen(), and enemyMovement() functions.
   //We did NOT use polymorphism to print the enemies AND the rogue TOGETHER in one function. Given the order of events in main.cpp, the Hero and the enemies must be printed at different times (and thus an all-encompassing print function would be unreasonable). We did - however - used polymorphism for printing our three types of enemies.
   //Once the enemies attack the Rogue, they jump back to their previous positions to allow the rogue to escape. If the previous position is occupied, the enemy in occupying the position will be expelled to a random location on screen.
   //When the enemies attack the Rogue, the Rogue loses health. When the Rogue attacks the enemies, the enemies lose health and then the enemies fight back, causing the Rogue to lose health.
   //In-game messages are only printed when an enemy dies or the Rogue loses health.

#include <iostream>
#include <vector>
#include <curses.h>
#include <cstdlib>
#include <ctime>
#include <windows.h>

#include "Rogue.h"
#include "Enemy.h"
#include "Elf.h"
#include "Ogre.h"
#include "Dragon.h"
#include "Obstacle.h"
#include "CoordinateYX.h"
#include "RoguelikeFunctions.h"

using namespace std;

int main()
{
//                       ~~~{ NCURSES MODE INITIALIZATIONS }~~~

    initscr();                  //----> initializes stdscr and the curses mode
    raw();                      //----> ensures raw input to output - no buffer
    noecho();                   //----> does not allow character typed to instantly appear
    srand(time(NULL));          //----> initializes random assignment process
    keypad(stdscr, TRUE);       //----> for key input
    curs_set(0);                //----> makes cursor invisible

//                 ~~~{ VARIABLE DECLARATION AND INITIALIZATIONS }~~~
    CoordinateYX maxScreen;
    int key, numMoves{0}, spawnFrequency{10}, enemyToAdd{1}, enemyType;
    double delayTime{4000}, printFactor{0.03};
    string buffer = "                                                ";

    Rogue Hero;
    int prevHealth, lostHealth;
    bool heroAlive{true};
    CoordinateYX nextRoguePos, nextEnemyPos;

    Enemy* currentEnemy{nullptr};
    int enemyIndex{0}, enemyKilled {0};

    std::vector<Enemy*> enemies;//to be used with polymorphism

    //As the enemy Coordinates are used frequently, they have a seperate position vector to be passed to functions (instead of entire objects). This will limit memory use.
    std::vector<CoordinateYX> enemyPos;

    std::vector<Obstacle> border;
    std::vector<Obstacle> walls;

    //As the border/wall Coordinates are used frequently, they have a seperate position vector to be passed to functions (instead of entire objects). This will limit memory use.
    std::vector<CoordinateYX> borderPos;
    std::vector<CoordinateYX> wallPos;

    std::vector<ScreenObject*> toPrint; //to be used with polymorphism

//                          ~~~~~~{ INTRODUCTION }~~~~~~

    getmaxyx(stdscr, maxScreen.y, maxScreen.x);

    printWelcome(stdscr);
    delay_output(delayTime);
    clear();

    printRules(stdscr, Hero);
    delay_output(delayTime);
    clear();

    printStats(stdscr, Hero, enemies.size());
    delay_output(delayTime);
    clear();

//         ~~~~~~{ INITIAL OBSTACLE GENERATION AND SCREEN FORMATING }~~~~~~

    generateBorder(stdscr, border);

    //loads border Obstacles into toPrint for polymorphism printing and into borderPos for future reference
    for(auto& elem : border)
    {
        toPrint.push_back(&elem);
        borderPos.push_back(elem.getPosition());
    }

    generateWalls(stdscr, walls, printFactor);

    //loads wall Obstacles into toPrint for polymorphism printing and into wallPos for future reference
    for(auto& elem : walls)
    {
        toPrint.push_back(&elem);
        wallPos.push_back(elem.getPosition());
    }

    toPrint.push_back(&Hero);

    printScreen(toPrint);
    printStats(Hero, enemies.size());


//                          ~~~~~~{ GAME LOGIC }~~~~~~
    do
    {
        if((numMoves >= spawnFrequency) && (numMoves % spawnFrequency == 0)) //generates new enemy every "spawnFrequency" moves
        {
            for(int numEnemy{0}; numEnemy < enemyToAdd; numEnemy++)
            {
                nextEnemyPos = randEnemyPos(maxScreen, Hero, wallPos, borderPos, enemyPos); //generates random position (within bounds, not on walls)
                enemyType = randEnemyType(); //generates random enemy type (Elf, Ogre, Dragon)

                if(enemyType == 1)
                    createElf(enemies, nextEnemyPos); //adds new Elf to enemies vector at 'nextEnemyPos'
                else if(enemyType == 2)
                    createOgre(enemies, nextEnemyPos); //adds new Ogre to enemies vector at 'nextEnemyPos'
                else if(enemyType == 3)
                    createDragon(enemies, nextEnemyPos); //adds new Dragon to enemies vector at 'nextEnemyPos'

                currentEnemy = enemies.at(enemies.size() - 1);
                enemyPos.push_back(currentEnemy->getPosition()); //adds new enemy's position to enemyPos vector
            }
        }

        do
        {
            key = getch(); //user presses arrow key to move
        }while(key != KEY_UP && key != KEY_DOWN && key != KEY_LEFT && key != KEY_RIGHT); //data sanitation

       Hero.setPrevPosition(Hero.getPosition());
       nextRoguePos = futurePos(Hero.getPrevPosition(), key); //based on user's key, calculates next potential location

       mvprintw(maxScreen.y - 2, (maxScreen.x/2) - buffer.length()/ 2, "%s", "                                                "); //refreshes message bar

       if(collisionCheck(nextRoguePos, wallPos, borderPos) == false) //if the rogue's future position doesn't collide with a wall/border...
       {
           //Rogue movement
           if(key == KEY_LEFT)
               Hero.moveLeft();
           else if(key == KEY_RIGHT)
               Hero.moveRight();
           else if(key == KEY_UP)
               Hero.moveUp();
           else if(key == KEY_DOWN)
               Hero.moveDown();

           if(enemyCollision(Hero.getPosition(), enemyPos, enemyIndex) == true) //if the Rogue's new position results in collision with enemy...
           {
                enemies.at(enemyIndex)->loseHealth(Hero.getAttackPow()); //reduces health of enemy (Rogue attacks)

                if(enemies.at(enemyIndex)->getHealth() <= 0) //if the enemy's health is less than / equal to 0, it dies...
                {
                    printMessage(stdscr, enemies); //prints message regarding enemy death (using downcasting)
                    removeEnemy(enemies, enemyPos, enemyIndex); //deletes enemy from vector etc.
                    enemyKilled++;
                }
           }

           Hero.resetPrev(); //overwrites Rogue's previously printed character
       }

       Hero.print();
       numMoves++;

       enemyMovement(enemies, Hero.getPosition(), wallPos, borderPos, enemyPos); //use of polymorphism
       printEnemy(enemies);

       prevHealth = Hero.getHealth();

       for(auto& elem : enemies)
       {
           if(elem->getXPos() == Hero.getXPos() && elem->getYPos() == Hero.getYPos()) //if the enemies attack the rogue...
           {
               Hero.loseHealth(elem->getAttackPow()); //the rogue loses health...

               if(Hero.getHealth() <= 0) //if the rogue loses all of its health, it dies
                   heroAlive = false;

               //The enemy now needs to jump back from Rogue (after attack)...
               if(enemyCollision(elem->getPrevPosition(), enemyPos, enemyIndex) == true) //If the position the enemy will jump back to is occupied, send the enemy occupying the space to a random position and sends the current enemy to its previous position.
               {
                   nextEnemyPos = randEnemyPos(maxScreen, Hero, wallPos, borderPos, enemyPos);
                   enemies.at(enemyIndex)->setPosition(nextEnemyPos);
                   elem->stepBack();
               }
               else //If the position the enemy will jump back to is not occupied, sends the enemy to its previous position.
                   elem->stepBack();

               updatePosVec(enemies, enemyPos); //updates enemyPos

               printEnemy(enemies);
               Hero.printR(); //prints the Hero in red (after attacked)
           }

           lostHealth = prevHealth - Hero.getHealth(); //calculates amount of health lost
           if(lostHealth != 0)
               printMessage(stdscr, lostHealth); //prints message regarding health loss
       }

       printStats(Hero, enemies.size()); //updates stats bar
       updatePosVec(enemies, enemyPos);
    }while(heroAlive == true && (enemies.size() > 0 || numMoves <= spawnFrequency)); //continue if the rogue is alive AND there are still enemies left

//                          ~~~~~~{ END MESSAGES AND DESTRUCTION OF DYNAMICALLY-ALLOCATED ENEMIES }~~~~~~
    clear();

    //prints end-of-game stats
    if(heroAlive == false)
        printEnd(stdscr, enemyKilled, numMoves, false);
    else if(enemies.size() == 0)
        printEnd(stdscr, enemyKilled, numMoves, true);

    delay_output(delayTime);

    for(auto& elem : enemies)
        delete elem;

    return 0;
}
