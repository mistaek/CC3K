#ifndef __player_h__
#define __player_h__
#include <utility>
#include <memory>
#include "entity.h"
#include <string>

class Potion;
class Treasure;
enum class Race {Human, Elf, Dwarf, Orc};

class Player: public Entity{
    Race race;
    bool armor=0;

    int mhp= 0, datk = 0, ddef = 0; //maxhp, default atk, default def
    public:
        Player(int r, int c,int hp, int atk, int def, Race race);
        std::string getrace();
        void setarmor(bool armor);
        void resetstats(); 
        int getmhp(); 
        int getdatk();
        int getddef();
        int struck(Entity* striker) override;
        
        void usepotion(Entity* potion) override;
        void usetreasure(Entity* treasure) override;
        virtual int getscore();
        virtual ~Player() = 0;
};
#endif
