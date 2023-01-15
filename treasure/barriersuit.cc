#include "barriersuit.h"

BarrierSuit::BarrierSuit(int r, int c): Treasure{r, c, 0, 0, true}, dragon{nullptr}{}

void BarrierSuit::setdragon(Entity* dragon){
    this->dragon = dragon;
}

bool BarrierSuit::alertDragon(bool l){
    if(dragon == nullptr) return false;
    if(dragon->isHostile()){
        dragon->sethostile(l);
        return false;
    }
    dragon->sethostile(l);
    return l;
}
