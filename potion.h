#ifndef __potion_h__
#define __potion_h__
#include "entity.h"
#include <string>
class Potion: public Entity{
    std::string potionID; 
    public:
        Potion(int r, int c, int hp, int atk, int def, std::string potionID); 
        ~Potion() = 0;
        std::string getID() override;
};

#endif
