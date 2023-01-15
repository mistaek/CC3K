#ifndef __dragon_hoard_h__
#define __dragon_hoard_h__
#include "../treasure.h"

class DragonHoard: public Treasure{
    Entity* dragon = nullptr;
    public:
        DragonHoard(int r, int c);
        void setdragon(Entity* dragon) override;
        bool alertDragon(bool l) override;
};

#endif
