#include "merchant.h"
#include "../entity.h"
#include "../treasure.h"
#include "../treasure/merchanthoard.h"
#include <cmath>

Merchant::Merchant(int r, int c): Enemy{r, c, 30, 75, 5, 0, 'M',EnemyType::Merchant}{}

bool Merchant::hostile = false;
bool Merchant::isHostile(){
    return hostile;
}

int Merchant::struck(Entity* struckby){
    hostile = true;
    int dmg = ceil((100* struckby->getatk())/(100.0+getdef())) ;

    sethp(gethp() - dmg);
    return dmg; 
}

std::shared_ptr<Entity> Merchant::die(Entity* killedby){
    std::shared_ptr<MerchantHoard> hoard = std::make_shared<MerchantHoard>(getpos().first, getpos().second);
    return hoard;
}
