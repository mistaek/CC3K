#include "staircase.h"
#include "../tile.h"
#include <utility>

Staircase::Staircase(int r, int c):Tile{r, c, 0, '\\'}, visible{1}{} 

void Staircase::setVisible(bool visible){
    this->visible = visible;
}

std::pair<std::pair<int, int>, char> Staircase::getInfo(){
    if(visible) return {{r, c}, mapchar}; 
    else return {{r, c}, '.'};
}

bool Staircase::isStaircase(){return true;}
