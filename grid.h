#ifndef __grid_h__
#define __grid_h__
#include "tile.h"
#include <memory>
#include <vector>
#include <string>
#include <iostream>
class Entity;
class Player;
class Item;
class Staircase;
class TextDisplay;

class Grid{
    int r= 25, c = 79;
    int floor = -1;
    std::vector<std::vector<std::vector<std::shared_ptr<Tile>>>> grid;
    std::vector<std::vector<std::pair<int, int>>> chambers;
    std::shared_ptr<Player> player;
    std::unique_ptr<TextDisplay> td;
    
    int generatePlayer(); 
    void generateStairs(int pc); 
    std::pair<int, int> selecttile();
    void generateSuit();
    int generateGold();
    std::shared_ptr<Entity> createTreasure(int nr, int nc);
    void generatePotions();
    std::shared_ptr<Entity> createPotion(int nr, int nc);
    void generateEnemies(int d); 
    std::shared_ptr<Entity> createEnemy(int nr, int nc);
    void readMap(std::string filename);
    void scanChambers();
    void readSave(std::string filename);
    void initiateTextDisplay(int i);
    void generate(std::string race); 
    int movePlayer(std::pair<int, int> dir);
    int playerAttack(std::pair<int, int> dir);
    int usePotion(std::pair<int, int> dir);
    void printStatus();
    void actionMove(std::pair<int, int> dir); 
    void actionMoveTreasure(std::pair<int, int> dir, Entity* treasure);
    void actionAttack(Entity* enemy);
    void actionDrink(std::string ID);
    void actionplayerAttacked(int dmg);
    void moveEnemies();
    void resetPlayer();
    void reset();

    public:
        friend std::ostream &operator<<(std::ostream &out, const Grid &g);
        friend class Game;
}; 

#endif
