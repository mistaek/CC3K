#ifndef __dragon_h__
#define __dragon_h__
#include "../enemy.h"
#include <memory>

class Treasure;
class Dragon: public Enemy{
    bool hostile;
    Entity* hoard;
    public:
        Dragon(int r, int c);
        void sethoard(Entity* hoard) override;
        bool isHostile() override;
        bool isStationary() override;
        std::shared_ptr<Entity> die(Entity* killedby) override;
        void sethostile(bool h) override;
};
#endif
