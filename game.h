#ifndef __game_h__
#define __game_h__
#include "grid.h"
#include <utility>
#include <string>
#include <memory>

class Entity;
class Player; 
class Staircase;

class Game{
    Grid g; 
    std::pair<int, int> getdir(std::string dir);

    public:
        void readMap(std::string filename); 
        void readSave(std::string filename);
        int command(std::string cmd);
        void takeTurn();
        void floorcomplete();
        bool gg();
};

#endif
