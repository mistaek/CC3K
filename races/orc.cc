#include "orc.h"
#include "../treasure.h"
#include <memory>
#include <algorithm>

Orc::Orc(int r, int c): Player{r, c, 180, 30, 25, Race::Orc}{}
void Orc::usetreasure(Entity* treasure){
    setgval(std::max(getgval() + (0.5 *treasure->getgval()), 0.0));
    if(treasure->isarmor()) setarmor(true);
}
