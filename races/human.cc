#include "../entity.h"
#include "human.h"

Human::Human(int r, int c):Player{r, c, 120, 20, 20, Race::Human}{}

int Human::getscore(){
    return getgval() * 1.5;
}
