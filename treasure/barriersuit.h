#ifndef __barrier_suit_h__
#define __barrier_suit_h__
#include "../treasure.h"

class BarrierSuit: public Treasure{
    Entity* dragon = nullptr;
    public:
        BarrierSuit(int r, int c);
        void setdragon(Entity* dragon) override;
        bool alertDragon(bool l) override;
};
#endif

