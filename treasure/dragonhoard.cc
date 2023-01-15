#include "dragonhoard.h"

DragonHoard::DragonHoard(int r, int c): Treasure{r, c, 6, 0, 0}, dragon{nullptr}{}

void DragonHoard::setdragon(Entity* dragon){
    this->dragon = dragon;
}

bool DragonHoard::alertDragon(bool l){
    if(dragon == nullptr) return false;
    if(dragon->isHostile()){
        dragon->sethostile(l);
        return false;
    }
    dragon->sethostile(l);
    return l;
}
