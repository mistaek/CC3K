#include "elf.h"
#include "../potion.h"
#include <memory>
#include <cmath>
#include <algorithm>

Elf::Elf(int r, int c): Player{r, c, 140, 30, 10, Race::Elf}{}

void Elf::usepotion(Entity* potion){
    sethp(std::min(std::max(gethp() + abs(potion->gethp()), 1), getmhp())); //can't die from potion, can't go above mhp
    setatk(std::max(getatk() + abs(potion->getatk()), 0));
    setdef(std::max(getdef() + abs(potion->getdef()), 0));
}
