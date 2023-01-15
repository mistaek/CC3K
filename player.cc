#include <utility>
#include "player.h"
#include "potion.h"
#include "treasure.h"
#include <cmath>
#include <algorithm>
#include <string>

Player::Player(int r, int c,int hp, int atk, int def, Race race): Entity{EntityType::Player, r, c, hp, atk, def, 0, '@'}, race{race}, armor{0}, mhp{hp}, datk{atk}, ddef{def}{}
Player::~Player(){}

void Player::setarmor(bool armor){
    this->armor = armor;
}

void Player::resetstats(){
    setatk(datk);
    setdef(ddef);
}
std::string Player::getrace(){
    if(race == Race::Human) return "Human"; 
    if(race == Race::Elf) return "Elf";
    if(race == Race::Dwarf) return "Dwarf";
    if(race == Race::Orc) return "Orc";
    return "Player";
}
int Player::getmhp(){ return mhp;}

int Player::getdatk(){return datk;}

int Player::getddef(){return ddef;}

int Player::struck(Entity* striker){
    int dmg = ceil((100* striker->getatk())/(100.0+getdef())) ;
    if(armor) dmg = std::ceil(dmg/2.0); 
    sethp(gethp() - dmg);
    return dmg;
}

void Player::usepotion(Entity* potion){
    sethp(std::min(std::max(gethp() + potion->gethp(), 1), mhp)); //can't die from potion, can't go above mhp
    setatk(std::max(getatk() + potion->getatk(), 0));
    setdef(std::max(getdef() + potion->getdef(), 0));
}

void Player::usetreasure(Entity* treasure){
    setgval(std::max(getgval() + treasure->getgval(), 0));
    if(treasure->isarmor()) setarmor(true);
}

int Player::getscore(){
    return getgval();
}
