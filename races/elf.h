#ifndef __elf_h__
#define __elf_h__
#include "../player.h"
#include <memory>

class Elf: public Player{
    public:
        Elf(int r, int c);
        void usepotion(Entity* potion) override;
};

#endif 
