#include "RoguelikeFunctions.h"
#include "Obstacle.h"
#include "Rogue.h"
#include "Enemy.h"

#include "Elf.h"
#include "Ogre.h"
#include "Dragon.h"

#include <curses.h>
#include <iostream>
#include <string.h>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <windows.h>
#include <sstream>

//Name: printWelcome
//Arguments: window (WINDOW*)
//Processing: prints a welcome message in the middle of the window
//Output: none (void)
void printWelcome(WINDOW* window)
{
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);

    attron(COLOR_PAIR(1) | A_BOLD);

    int yMax, xMax;
    getmaxyx(window, yMax, xMax);

    mvprintw((yMax/2), (xMax/2) - strlen("WELCOME TO ROGUELIKE!")/2, "%s", "WELCOME TO ROGUELIKE!");

    refresh();
    attroff(COLOR_PAIR(1));
}

//Name: printRules
//Arguments: window (WINDOW*), hero (Rogue object)
//Processing: prints the instructions for the Roguelike game in the middle of the screen
//Output: none (void)
void printRules(WINDOW* window, Rogue hero)
{
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    attron(COLOR_PAIR(1));

    int yMax, xMax;
    getmaxyx(window, yMax, xMax);

    mvprintw((yMax/2) - 3, (xMax/2) - strlen("INSTRUCTIONS:")/2, "%s", "INSTRUCTIONS:");
    mvprintw((yMax/2) - 1, (xMax/2) - strlen("YOU ARE A ROGUE!")/2, "%s", "YOU ARE A ROGUE!");
    mvprintw((yMax/2) + 0, (xMax/2) - strlen("YOU ONLY HAVE ONE LIFE.")/2, "%s", "YOU ONLY HAVE ONE LIFE.");


    std::ostringstream health;
    health << hero.getHealth();
    std::string heroHealth = health.str();

    mvprintw((yMax/2) + 1, (xMax/2) - (strlen("YOU HAVE ") + heroHealth.length() + strlen(" HEALTH."))/2, "%s", "YOU HAVE ");
    mvprintw((yMax/2) + 1, (xMax/2) - (strlen("YOU HAVE ") + heroHealth.length() + strlen(" HEALTH."))/2 + strlen("YOU HAVE "), "%i", hero.getHealth());
    mvprintw((yMax/2) + 1, (xMax/2) - (strlen("YOU HAVE ") + heroHealth.length() + strlen(" HEALTH."))/2 + (strlen("YOU HAVE ") + heroHealth.length()), "%s", " HEALTH."); //MANUALLY ADJUSTED

    mvprintw((yMax/2) + 3, (xMax/2) - strlen("USE THE ARROW KEYS TO MOVE AND ATTACK ENEMIES.")/2, "%s", "USE THE ARROW KEYS TO MOVE AND ATTACK ENEMIES.");

    mvprintw((yMax/2) + 4, (xMax/2) - strlen("BEWARE THE NIMBLE ELF, THE FEROCIOUS OGRE, AND THE MIGHTY DRAGON!")/2, "%s", "BEWARE THE NIMBLE ELF, THE FEROCIOUS OGRE, AND THE MIGHTY DRAGON!");
    mvprintw((yMax/2) + 5, (xMax/2) - strlen("SURVIVE AS LONG AS POSSIBLE.")/2, "%s", "SURVIVE AS LONG AS POSSIBLE.");
    mvprintw((yMax/2) + 7, (xMax/2) - strlen("~~~ Good Luck! ~~~")/2, "%s", "~~~ Good Luck! ~~~");

    refresh();
    attroff(COLOR_PAIR(1));
}

//Name: printEnd
//Arguments: window (WINDOW*), tally of enemies killed overall (enemyKilled), moves made (roundCount), and whether the user won (win)
//Processing: prints the end-of-game stats (moves survived for, enemies killed, win or loss)
//Output: none (void)
void printEnd(WINDOW* window, int enemyKilled, int roundCount, bool win)
{
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    attron(COLOR_PAIR(1));

    int yMax, xMax;
    getmaxyx(window, yMax, xMax);

    if(win == true)
        mvprintw((yMax/2) - 2, (xMax/2) - strlen("YOU WON!")/2, "%s", "YOU WON!");
    else
        mvprintw((yMax/2) - 2, (xMax/2) - strlen("YOU DIED!")/2, "%s", "YOU DIED!");

    std::ostringstream enemyNum;
    enemyNum << enemyKilled;
    std::string enemyKilledStr = enemyNum.str();

    std::ostringstream roundNum;
    roundNum << roundCount;
    std::string roundCountStr = roundNum.str();

    mvprintw((yMax/2), (xMax/2) - (strlen("YOU SURVIVED FOR ") + roundCountStr.length() + strlen(" MOVES!"))/2, "%s", "YOU SURVIVED FOR ");
    mvprintw((yMax/2), (xMax/2) - (strlen("YOU SURVIVED FOR ") + roundCountStr.length() + strlen(" MOVES!"))/2 + strlen("YOU SURVIVED FOR "), "%i", roundCount);
    mvprintw((yMax/2), (xMax/2) - (strlen("YOU SURVIVED FOR ") + roundCountStr.length() + strlen(" MOVES!"))/2 + (strlen("YOU SURVIVED FOR ") + roundCountStr.length()), "%s", " MOVES!");

    mvprintw((yMax/2) + 1, (xMax/2) - (strlen("YOU KILLED ") +  enemyKilledStr.length() + strlen(" ENEMIES!"))/2, "%s", "YOU KILLED ");
    mvprintw((yMax/2) + 1, (xMax/2) - (strlen("YOU KILLED ") +  enemyKilledStr.length() + strlen(" ENEMIES!"))/2 + strlen("YOU KILLED "), "%i", enemyKilled);
    mvprintw((yMax/2) + 1, (xMax/2) - (strlen("YOU KILLED ") +  enemyKilledStr.length() + strlen(" ENEMIES!"))/2 + (strlen("YOU KILLED ") + enemyKilledStr.length()), "%s", " ENEMIES!");


    refresh();
    attroff(COLOR_PAIR(1));
}

//Name: printStats (overloaded)
//Arguments: window (WINDOW*), hero (Rogue object), enemyCount
//Processing: prints start-of-game stats (Rogue health and enemyCount)
//Output: none (void)
void printStats(WINDOW* window, Rogue Hero, int enemyCount)
{
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    attron(COLOR_PAIR(1));

    int yMax, xMax;
    getmaxyx(window, yMax, xMax);

    mvprintw((yMax/2) + 1, (xMax/2) - strlen("HEALTH: ")/2, "%s", "HEALTH: ");
    mvprintw((yMax/2) + 1, (xMax/2) + strlen("HEALTH: ")/2, "%i", Hero.getHealth());
    mvprintw((yMax/2) + 2, (xMax/2) - strlen("ENEMIES:  ")/2, "%s", "ENEMIES: ");
    mvprintw((yMax/2) + 2, (xMax/2) + strlen("ENEMIES:  ")/2, "%i", enemyCount);

    refresh();
    attroff(COLOR_PAIR(1));
}

//Name: printStats (overloaded)
//Arguments: hero (Rogue object), enemyCount
//Processing: prints the stats bar in the top left corner of the screen (during game)
//Output: none (void)
void printStats(Rogue Hero, int enemyCount)
{
    start_color();
    init_pair(1, COLOR_GREEN, COLOR_BLACK);

    attron(COLOR_PAIR(1) | A_BOLD);

    int yMin = 1, xMin = 2;
    int yMax = yMin + 3, xMax = (xMin + strlen("ENEMIES: ") + 2);

    for(int xPos{xMin}; xPos <= xMax; xPos++)
        mvprintw(yMin, xPos, "%c", '-');
    for(int xPos{xMin}; xPos <= xMax; xPos++)
        mvprintw(yMax, xPos, "%c", '-');

    mvprintw((yMin + 1), xMin, "%s", "HEALTH:  ");
    mvprintw((yMin + 1), xMin + strlen("HEALTH: "), "%s", "     ");
    mvprintw((yMin + 1), xMin + strlen("HEALTH:  "), "%i", Hero.getHealth());
    mvprintw((yMin + 2), xMin, "%s", "ENEMIES: ");
    mvprintw((yMin + 2), xMin + strlen("ENEMIES: "), "%s", "  ");
    mvprintw((yMin + 2), xMin + strlen("ENEMIES: "), "%i", enemyCount);

    attroff(COLOR_PAIR(1) | A_BOLD);
    refresh();
}

//Name: printMessage (overloaded)
//Arguments: window (WINDOW*), vector of pointers to Enemies
//Processing: prints message at bottom of screen once an enemy is killed; uses DOWNCASTING to determine enemy type
//Output: none (void)
void printMessage(WINDOW* window, std::vector<Enemy*> enemies)
{
    int xMax, yMax;
    getmaxyx(window, yMax, xMax);

    Elf* elfPtr {nullptr};
    Ogre* ogrePtr {nullptr};
    Dragon* dragonPtr {nullptr};

    for(Enemy* enemy : enemies)
    {
        if(enemy->getHealth() <= 0)
        {
            mvprintw(yMax - 2, (xMax/2) - strlen("                               ")/2, "%s", "                               ");

            elfPtr = dynamic_cast<Elf*>(enemy);
            if(elfPtr != nullptr)
                mvprintw(yMax - 2, (xMax/2) - strlen("YOU KILLED AN ELF!")/2, "%s", "YOU KILLED AN ELF!");
            ogrePtr = dynamic_cast<Ogre*>(enemy);
            if(ogrePtr != nullptr)
                mvprintw(yMax - 2, (xMax/2) - strlen("YOU KILLED AN OGRE!")/2, "%s", "YOU KILLED AN OGRE!");
            dragonPtr = dynamic_cast<Dragon*>(enemy);
            if(dragonPtr != nullptr)
                mvprintw(yMax - 2, (xMax/2) - strlen("YOU KILLED A DRAGON!")/2, "%s", "YOU KILLED A DRAGON!");
        }
    }
}

//Name: printMessage (overloaded)
//Arguments: window (WINDOW*), lostHealth
//Processing: prints message at bottom of screen once the Rogue loses health
//Output: none (void)
void printMessage(WINDOW* window, int lostHealth)
{
    int xMax, yMax;
    getmaxyx(window, yMax, xMax);

    std::ostringstream health;
    health << lostHealth;
    std::string lostHealthStr = health.str();

    mvprintw(yMax - 2, (xMax/2) - (strlen("YOU LOST ") + lostHealthStr.length() + strlen(" HEALTH!"))/2, "%s", "                                                ");
    mvprintw(yMax - 2, (xMax/2) - (strlen("YOU LOST ") + lostHealthStr.length() + strlen(" HEALTH!"))/2, "%s", "YOU LOST ");
    mvprintw(yMax - 2, (xMax/2) - (strlen("YOU LOST ") + lostHealthStr.length() + strlen(" HEALTH!"))/2 + strlen("YOU LOST "), "%i", lostHealth);
    mvprintw(yMax - 2, (xMax/2) - (strlen("YOU LOST ") + lostHealthStr.length() + strlen(" HEALTH!"))/2 + (strlen("YOU LOST ") + lostHealthStr.length()), "%s", " HEALTH!");
}

//Name: printScreen (POLYMORPHISM)
//Arguments: toPrint (a vector of pointers to ScreenObjects)
//Processing: calls the print() functions of ScreenObject pointers using POLYMORPHISM
//Output: none (void)
void printScreen(const std::vector<ScreenObject*>& toPrint)
{
    for(auto elem : toPrint)
        elem->print();

    refresh();
}

//Name: printEnemy (POLYMORPHISM)
//Arguments: toPrint (a vector of pointers to Enemies)
//Processing: calls the print() functions of Enemy pointers using POLYMORPHISM
//Output: none (void)
void printEnemy(const std::vector<Enemy*>& toPrint)
{
    for(auto elem : toPrint)
        elem->print();

    refresh();
}

//Name: enemyMovement (POLYMORPHISM)
//Arguments: toMove (vector of pointers to Enemies), heroPos, wallPos, borderPos, enemyPos
//Processing: calls the attack functions of all enemies using POLYMORPHISM
//Output: none (void)
void enemyMovement(const std::vector<Enemy*>& toMove, CoordinateYX heroPos, const std::vector<CoordinateYX>& wallPos, const std::vector<CoordinateYX>& borderPos, std::vector<CoordinateYX>& enemyPos)
{
    for(size_t i{0}; i < toMove.size(); i++)
    {
        (toMove.at(i))->attack(heroPos, wallPos, borderPos, enemyPos);

        updatePosVec(toMove, enemyPos);
    }
}

//Name: updatePosVec
//Arguments: enemies (vector of pointers to Enemies), enemyPos (coordinates of Enemies)
//Processing: updates enemyPos by clearing 'enemyPos' and loading the positions of each of the enemies in 'enemies' back into vector
//Output: none (void)
void updatePosVec(const std::vector<Enemy*>& enemies, std::vector<CoordinateYX>& enemyPos)
{
    enemyPos.clear();
    for(auto elem : enemies)
        enemyPos.push_back(elem->getPosition());
}

//Name: createElf
//Arguments: enemies (vector of pointers to Enemies), pos (Coordinate at which Elf should be created)
//Processing: adds a 'new' dynamically-allocated Elf to enemies vector at 'pos'
//Output: none (void)
void createElf(std::vector<Enemy*>& enemies, CoordinateYX pos)
{
    enemies.push_back(new Elf(pos.y, pos.x));
}

//Name: createOgre
//Arguments: enemies (vector of pointers to Enemies), pos (Coordinate at which Elf should be created)
//Processing: adds a 'new' dynamically-allocated Ogre to enemies vector at 'pos'
//Output: none (void)
void createOgre(std::vector<Enemy*>& enemies, CoordinateYX pos)
{
    enemies.push_back(new Ogre(pos.y, pos.x));
}

//Name: createDragon
//Arguments: enemies (vector of pointers to Enemies), pos (Coordinate at which Elf should be created)
//Processing: adds a 'new' dynamically-allocated Dragon to enemies vector at 'pos'
//Output: none (void)
void createDragon(std::vector<Enemy*>& enemies, CoordinateYX pos)
{
    enemies.push_back(new Dragon(pos.y, pos.x));
}

//Name: removeEnemy
//Arguments: enemies (vector of pointers to Enemies), enemyPos (vector of Coordinates of enemies), enemyIndex (to be removed)
//Processing: deletes dynamically-allocated enemy at 'enemyIndex', removes this enemy from 'enemies' and 'enemyPos' vectors
//Output: none (void)
void removeEnemy(std::vector<Enemy*>& enemies, std::vector<CoordinateYX>& enemyPos, int enemyIndex)
{
    delete enemies.at(enemyIndex);
    enemies.erase(enemies.begin() + enemyIndex);
    enemyPos.erase(enemyPos.begin() + enemyIndex);
}

//Name: randEnemyType
//Arguments: none
//Processing: generates a number between 1 and 3 to represent type of enemy to be created next (1 = Elf, 2 = Ogre, 3 = Dragon)
//Output: int representing random enemy type
int randEnemyType()
{
    int enemyNum = rand() % 3 + 1;
    return enemyNum;
}

//Name: randWallPos
//Arguments: maxScreen (coordinates of bottom right point on screen, maximum x/y values)
//Processing: generates a random wall position within these bounds (that doesn't collide with Stats bar)
//Output: randPos (random Coordinate of wall to be generated)
CoordinateYX randWallPos(CoordinateYX maxScreen)
{
    CoordinateYX randPos;

    do
    {
        randPos.y = rand() % (int(maxScreen.y) - 2) + 1;
        randPos.x = rand() % (int(maxScreen.x) - 2) + 1;
    }while(collideWithStatBar(randPos) == true);

    return randPos;
}

//Name: randEnemyPos
//Arguments: maxScreen, Hero, wallPos, borderPos, enemyPos
//Processing: generates random STARTING position for enemy (that doesn't overlap walls, border, Hero, or other enemies)
//Output: randPos (random Coordinate of enemy to be generated)
CoordinateYX randEnemyPos(CoordinateYX maxScreen, Rogue Hero, const std::vector<CoordinateYX>& wallPos, const std::vector<CoordinateYX>& borderPos, const std::vector<CoordinateYX>& enemyPos)
{
    CoordinateYX randPos;

    do
    {
        randPos.y = rand() % (int(maxScreen.y - 5) - 2) + 1;
        randPos.x = rand() % (int(maxScreen.x) - 2) + 1;
    }while(collisionCheck(randPos, Hero, wallPos, borderPos, enemyPos) == true);

    return randPos;
}

//Name: generateWalls
//Arguments: window, walls, printFactor
//Processing: generates a certain number of walls to fill inside of arena
//Output: none (updates walls vector)
void generateWalls(WINDOW* window, std::vector<Obstacle>& walls, const double& printFactor)
{
    Obstacle dummy;
    CoordinateYX randPos, maxScreen;
    getmaxyx(window, maxScreen.y, maxScreen.x);
    int areaScreen = (maxScreen.y - 4) * maxScreen.x;

    for(int numWall{0}; numWall < int(printFactor * areaScreen); numWall++)
    {
        randPos = randWallPos(maxScreen);

        dummy.setYPos(randPos.y - 4);
        dummy.setXPos(randPos.x);
        walls.push_back(dummy);
    }
}

//Name: generateBorder
//Arguments: window, border
//Processing: generates a border (1 cell thick) for the game arena
//Output: none (updates border vector)
void generateBorder(WINDOW* window, std::vector<Obstacle>& border)
{
    Obstacle dummy;
    CoordinateYX maxScreen;
    getmaxyx(window, maxScreen.y, maxScreen.x);

    for(int xPos{0}; xPos <= int(maxScreen.x); xPos++)
    {
        dummy.setYPos(0);
        dummy.setXPos(xPos);
        border.push_back(dummy);

        dummy.setYPos(maxScreen.y - 4);
        dummy.setXPos(xPos);
        border.push_back(dummy);
    }

    for(int yPos{0}; yPos <= int(maxScreen.y - 4); yPos++)
    {
        dummy.setYPos(yPos);
        dummy.setXPos(0);
        border.push_back(dummy);

        dummy.setYPos(yPos);
        dummy.setXPos(maxScreen.x - 1);
        border.push_back(dummy);
    }
}

//Name: moveValue
//Arguments: character (pointer to an Enemy), direction, magnitude
//Processing: depending on magnitude of movement, moves the character a certain number of times in the indicated direction
//Output: none (void)
void moveValue(Enemy* character, std::string direction, int magnitude)
{
    if(direction == "UP")
        for(int num {1}; num <= magnitude; num++)
            character->moveUp();
    else if(direction == "DOWN")
        for(int num {1}; num <= magnitude; num++)
            character->moveDown();
    else if(direction == "LEFT")
        for(int num {1}; num <= magnitude; num++)
            character->moveLeft();
    else if(direction == "RIGHT")
        for(int num {1}; num <= magnitude; num++)
            character->moveRight();
    else if(direction == "TOPRIGHT")
        for(int num {1}; num <= magnitude; num++)
            character->moveTopRight();
    else if(direction == "TOPLEFT")
        for(int num {1}; num <= magnitude; num++)
            character->moveTopLeft();
    else if(direction == "BOTTOMRIGHT")
        for(int num {1}; num <= magnitude; num++)
            character->moveBottomRight();
    else if(direction == "BOTTOMLEFT")
        for(int num {1}; num <= magnitude; num++)
            character->moveBottomLeft();
}

//Name: futurePos (overloaded for enemy)
//Arguments: currentPos, move, magnitude
//Processing: calculates potential future position of an enemy based on move type proposed and magnitude of move
//Output: Coordinate representing potential future position
CoordinateYX futurePos(CoordinateYX currentPos, std::string move, int magnitude)
{
    CoordinateYX nextPos = currentPos;

    if(move == "U")
        nextPos.y -= magnitude;
    else if(move == "D")
        nextPos.y += magnitude;
    else if(move == "R")
        nextPos.x += magnitude;
    else if(move == "L")
        nextPos.x -= magnitude;
    else if(move == "DR")
    {
        nextPos.y += magnitude;
        nextPos.x += magnitude;
    }
    else if(move == "DL")
    {
        nextPos.y += magnitude;
        nextPos.x -= magnitude;
    }
    else if(move == "UR")
    {
        nextPos.y -= magnitude;
        nextPos.x += magnitude;
    }
    else if(move == "UL")
    {
        nextPos.y -= magnitude;
        nextPos.x -= magnitude;
    }

    return nextPos;
}

//Name: futurePos (overloaded for Rogue)
//Arguments: currentPos, KEY_SHIFT (representing arrow key pressed)
//Processing: calculates potential future position of an enemy based on arrow key pressed
//Output: Coordinate representing potential future position
CoordinateYX futurePos(CoordinateYX currentPos, int KEY_SHIFT)
{
    CoordinateYX nextPos = currentPos;

    if(KEY_SHIFT == KEY_LEFT)
        nextPos.x -= 1;
    else if(KEY_SHIFT == KEY_RIGHT)
        nextPos.x += 1;
    else if(KEY_SHIFT == KEY_UP)
        nextPos.y -= 1;
    else if(KEY_SHIFT == KEY_DOWN)
        nextPos.y += 1;

    return nextPos;
}

//Name: collideWithStatBar
//Arguments: pos (CoordinateYX)
//Processing: determines whether the given coordinate overlaps with the stats bar in the top left corner
//Output: bool representing whether collision has occurred
bool collideWithStatBar(CoordinateYX pos)
{
    if(pos.y <= 4 && pos.x <= 14)
        return true;
    else
        return false;
}

//NOTE: The following four functions are similar, but have different argument requirements that are useful in different cases.

//Name: collisionCheck (overloaded)
//Arguments: nextPos, wallPos, borderPos
//Processing: checks if nextPos coordinates overlap with wallPos/borderPos coordinates
//Output: bool (representing whether a collision has occurred)
bool collisionCheck(CoordinateYX nextPos, const std::vector<CoordinateYX>& wallPos, const std::vector<CoordinateYX>& borderPos)
{
    bool collision{false};

    int yPos, xPos;
    getmaxyx(stdscr, yPos, xPos);

    for(auto elem : wallPos)
    {
        if(nextPos.x == elem.x && nextPos.y == elem.y)
            collision = true;
    }

    for(auto elem : borderPos)
    {
        if(nextPos.x == elem.x && nextPos.y == elem.y)
            collision = true;
        if(nextPos.y > (yPos - 4) || nextPos.x > xPos )
            collision = true;
    }

    if(collideWithStatBar(nextPos) == true)
        collision = true;

    return collision;
}

//Name: collisionCheck (overloaded)
//Arguments: nextPos, wallPos, borderPos, enemyPos
//Processing: checks if nextPos coordinates overlap with wallPos/borderPos/enemyPos coordinates
//Output: bool (representing whether a collision has occured)
bool collisionCheck(CoordinateYX nextPos, const std::vector<CoordinateYX>& wallPos, const std::vector<CoordinateYX>& borderPos, const std::vector<CoordinateYX>& enemyPos)
{
    bool collision{false};

    int yPos, xPos;
    getmaxyx(stdscr, yPos, xPos);

    for(auto elem : wallPos)
    {
        if(nextPos.x == elem.x && nextPos.y == elem.y)
            collision = true;
    }

    for(auto elem : borderPos)
    {
        if(nextPos.x == elem.x && nextPos.y == elem.y)
            collision = true;
        if(nextPos.y > (yPos - 4) || nextPos.x > xPos )
            collision = true;
    }

    for(auto elem : enemyPos)
    {
        if(nextPos.x == elem.x && nextPos.y == elem.y)
            collision = true;
    }

    if(collideWithStatBar(nextPos) == true)
        collision = true;

    return collision;
}

//Name: collisionCheck (overloaded)
//Arguments: nextPos, wallPos, borderPos, enemyPos, Hero
//Processing: checks if nextPos coordinates overlap with wallPos/borderPos/enemyPos/Hero coordinates
//Output: bool (representing whether a collision has occurred)
bool collisionCheck(CoordinateYX nextPos, Rogue Hero, const std::vector<CoordinateYX>& wallPos, const std::vector<CoordinateYX>& borderPos, const std::vector<CoordinateYX>& enemyPos)
{
    bool collision{false};

    int yPos, xPos;
    getmaxyx(stdscr, yPos, xPos);

    for(auto elem : wallPos)
    {
        if(nextPos.x == elem.x && nextPos.y == elem.y)
            collision = true;
    }

    for(auto elem : borderPos)
    {
        if(nextPos.x == elem.x && nextPos.y == elem.y)
            collision = true;
        if(nextPos.y > (yPos - 4) || nextPos.x > xPos )
            collision = true;
    }

    for(auto elem : enemyPos)
    {
        if(nextPos.x == elem.x && nextPos.y == elem.y)
            collision = true;
    }

    if(collideWithStatBar(nextPos) == true)
        collision = true;

    if(nextPos.x == Hero.getXPos() && nextPos.y == Hero.getYPos())
        collision = true;

    return collision;
}

//Name: enemyCollision
//Arguments: pos, enemyPos, enemyCollideIndex (passed by reference)
//Processing: indicates whether an enemy has been collided with and updates the enemyCollideIndex accordingly
//Output: bool (representing whether a collision has occurred)
bool enemyCollision(CoordinateYX pos, const std::vector<CoordinateYX> enemyPos, int& enemyCollideIndex)
{
    bool collision{false};
    int yPos, xPos;

    for(size_t i{0}; i < enemyPos.size(); i++)
    {
        yPos = enemyPos.at(i).y;
        xPos = enemyPos.at(i).x;

        if(yPos == pos.y && xPos == pos.x)
        {
            collision = true;
            enemyCollideIndex = i;
            break;
        }
    }

    return collision;
}
