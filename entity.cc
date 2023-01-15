#include "entity.h"
#include <memory>
#include <cmath>
#include <string>

Entity::Entity(EntityType type, int r, int c,int hp, int atk, int def, int gval, char mapchar): type{type}, r{r}, c{c}, hp{hp}, atk{atk}, def{def}, gval{gval}, mapchar{mapchar}{}
Entity::~Entity(){}

EntityType Entity::getType(){
    return type;
}

int Entity::gethp(){
    return hp;
}

int Entity::getatk(){
    return atk;
}

int Entity::getdef(){
    return def; 
}

int Entity::getgval(){
    return gval;
}

char Entity::getmapchar(){
    return mapchar;
}

std::pair<int, int> Entity::getpos(){
    return {r, c};
}

void Entity::sethp(int nhp){
    hp = nhp;
}

void Entity::setatk(int natk){
    atk = natk; 
}

void Entity::setdef(int ndef){
    def = ndef; 
}

void Entity::setgval(int ngval){
    gval = ngval;
}

void Entity::setpos(int nr, int nc){
    r = nr; c = nc; 
}

bool Entity::isdead(){
    return gethp() <= 0;
}

void Entity::move(std::pair<int, int> dir){
    std::pair<int, int> pos = getpos(); 
    setpos(pos.first + dir.first, pos.second + dir.second); 
}

//return damage dealt
int Entity::strike(Entity* striking){
    return striking->struck(this);
}

//return damage taken
int Entity::struck(Entity* striker){
    int dmg = ceil((100* striker->getatk())/(100.0+getdef()));
    sethp(gethp() - dmg);
    return dmg; 
}

std::shared_ptr<Entity> Entity::die(Entity* killedby){
    killedby->usetreasure(this);
    std::shared_ptr<Entity> corpse{nullptr};
    return corpse;
}

void Entity::sethostile(bool l){}
void Entity::sethoard(Entity*){}
bool Entity::isHostile(){ return false;}
void Entity::setlootable(bool l){}
bool Entity::isarmor(){ return false;}
bool Entity::islootable(){return false;}
std::string Entity::getID(){return "";}
void Entity::setdragon(Entity*){}
bool Entity::alertDragon(bool l){ return false;}
void Entity::usepotion(Entity* potion){}
void Entity::usetreasure(Entity* treasure){}
bool Entity::isStationary(){return false;}
