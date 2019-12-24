#ifndef ROGUELIKEFUNCTIONS_H
#define ROGUELIKEFUNCTIONS_H

#include <curses.h>
#include <vector>
#include <string>
#include "Rogue.h"
#include "Enemy.h"
#include "Obstacle.h"
#include "CoordinateYX.h"

void printWelcome(WINDOW* window);
void printRules(WINDOW* window, Rogue hero);
void printEnd(WINDOW* window, int enemyKilled, int roundCount, bool win);

void printStats(WINDOW* window, Rogue Hero, int enemyCount);
void printStats(Rogue Hero, int enemyCount);
void printMessage(WINDOW* window, std::vector<Enemy*> enemies);
void printMessage(WINDOW* window, int lostHealth);

void printScreen(const std::vector<ScreenObject*>& toPrint);
void printEnemy(const std::vector<Enemy*>& toPrint);
void printChar(const std::vector<Character*>& toPrint);

void enemyMovement(const std::vector<Enemy*>& toMove, CoordinateYX heroPos, const std::vector<CoordinateYX>& wallPos, const std::vector<CoordinateYX>& borderPos, std::vector<CoordinateYX>& enemyPos);
void updatePosVec(const std::vector<Enemy*>& enemies, std::vector<CoordinateYX>& enemyPos);

void createElf(std::vector<Enemy*>& enemies, CoordinateYX pos);
void createOgre(std::vector<Enemy*>& enemies, CoordinateYX pos);
void createDragon(std::vector<Enemy*>& enemies, CoordinateYX pos);
void removeEnemy(std::vector<Enemy*>& enemies, std::vector<CoordinateYX> &enemyPos, int enemyIndex);

void generateWalls(WINDOW* window, std::vector<Obstacle>& walls, const double& printFactor);
void generateBorder(WINDOW* window, std::vector<Obstacle>& border);

int randEnemyType();
CoordinateYX randWallPos(CoordinateYX maxScreen);
CoordinateYX randEnemyPos(CoordinateYX maxScreen, Rogue Hero, const std::vector<CoordinateYX>& wallPos, const std::vector<CoordinateYX>& borderPos, const std::vector<CoordinateYX>& enemyPos);

void moveValue(Enemy* character, std::string direction, int magnitude);
CoordinateYX futurePos(CoordinateYX currentPos, std::string move, int magnitude);
CoordinateYX futurePos(CoordinateYX currentPos, int KEY_SHIFT);

bool collideWithStatBar(CoordinateYX pos);
bool enemyCollision(CoordinateYX pos, const std::vector<CoordinateYX> enemyPos, int &enemyCollideIndex);
bool collisionCheck(CoordinateYX nextPos, const std::vector<CoordinateYX>& wallPos, const std::vector<CoordinateYX>& borderPos);
bool collisionCheck(CoordinateYX nextPos, const std::vector<CoordinateYX>& wallPos, const std::vector<CoordinateYX>& borderPos, const std::vector<CoordinateYX>& enemyPos);
bool collisionCheck(CoordinateYX nextPos, Rogue Hero, const std::vector<CoordinateYX>& wallPos, const std::vector<CoordinateYX>& borderPos, const std::vector<CoordinateYX>& enemyPos);

#endif // ROGUELIKEFUNCTIONS_H
