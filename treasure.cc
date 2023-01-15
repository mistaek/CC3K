#include "treasure.h"
#include <iostream>
Treasure::Treasure(int r, int c, int n,bool lootable, bool armor): Entity{EntityType::Treasure, r, c, 0, 0, 0, n, (armor ? 'B' : 'G')}, lootable{lootable}, armor{armor}{}
Treasure::~Treasure(){}

void Treasure::setlootable(bool l){
    lootable = l;
}

bool Treasure::islootable(){
    return lootable;
}

bool Treasure::isarmor(){
    return armor;
}
