#include "dwarf.h"
#include "../treasure.h"
#include <memory>
#include <algorithm>

Dwarf::Dwarf(int r, int c): Player{r, c, 100, 20, 30, Race::Dwarf}{}

void Dwarf::usetreasure(Entity* treasure){
    setgval(std::max(getgval() + (2*treasure->getgval()), 0));
    if(treasure->isarmor()) setarmor(true);
}
