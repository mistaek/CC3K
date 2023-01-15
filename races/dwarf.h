#ifndef __dwarf_h__
#define __dwarf_h__
#include "../player.h"
#include <memory>
class Treasure;

class Dwarf: public Player{
    public: 
        Dwarf(int r, int c);
        void usetreasure(Entity* treasure) override;
        
        
};

#endif
