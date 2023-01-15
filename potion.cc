#include "potion.h"
#include <string>
Potion::Potion(int r, int c, int hp, int atk, int def, std::string potionID): Entity{EntityType::Potion,r, c, hp, atk, def, 0, 'P'}, potionID{potionID} {}
Potion::~Potion(){}

std::string Potion::getID(){
    return potionID;
}
