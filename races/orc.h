#ifndef __orc_h__ 
#define __orc_h__
#include "../player.h"
#include <memory>
class Treasure;
class Orc: public Player{
    public: 
        Orc(int r, int c);
        void usetreasure(Entity* treasure) override;
};
#endif
