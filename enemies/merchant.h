#ifndef __merchant_h__
#define __merchant_h__
#include "../enemy.h"
#include "../entity.h"


#include <memory>
class Merchant: public Enemy{
    static bool hostile;
    public:
        Merchant(int r, int c);
        bool isHostile() override;
        int struck(Entity* struckby) override; 
        std::shared_ptr<Entity> die(Entity* killedby) override;
};
#endif
