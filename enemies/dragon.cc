#include "dragon.h"
#include "../entity.h"
#include "../treasure.h"
Dragon::Dragon(int r, int c): Enemy{r, c, 150, 20, 20, 0,'D', EnemyType::Dragon}, hoard{nullptr}{}

void Dragon::sethoard(Entity* hoard){
    this->hoard = hoard;
}

void Dragon::sethostile(bool l){
    hostile = l;
}
bool Dragon::isHostile(){
    return hostile;
}

bool Dragon::isStationary(){
    return true;
}

std::shared_ptr<Entity> Dragon::die(Entity* killedby){
    if(hoard != nullptr){
        hoard->setlootable(true);
        hoard->setdragon(nullptr);
    }
    return nullptr;
}
