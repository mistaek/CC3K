#include "tile.h"
#include <utility>
#include <memory>
#include "entity.h"



Tile::Tile(int r, int c, int passable, char mapchar): r{r}, c{c}, passable{passable}, mapchar{mapchar}{} 
Tile::~Tile(){}

bool Tile::getPassable(){
    return passable;
}

void Tile::setEntity(std::shared_ptr<Entity> entity){
    this->entity = entity;
    notifyObservers();
}

void Tile::setVisible(bool l){}

bool Tile::isStaircase(){return false;}

Entity* Tile::getEntity(){
    return entity.get();
}

std::shared_ptr<Entity> Tile::getEntityptr(){
    return this->entity;
}

char Tile::getmapchar(){
    return (entity == nullptr) ? mapchar : entity->getmapchar();
}

std::pair<std::pair<int, int>, char> Tile::getInfo(){
    if(entity != nullptr){
        return {{r, c}, entity->getmapchar()}; 
    }
    return {{r, c}, mapchar};
}

