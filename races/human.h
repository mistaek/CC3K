#ifndef __human_h__ 
#define __human_h__
#include "../player.h"

class Human: public Player{
    public:
        Human(int r, int c);
        int getscore() override; 

};

#endif