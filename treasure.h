#ifndef __gold_h__
#define __gold_h__
#include "entity.h"
class Treasure : public Entity{
    bool lootable=1;
    bool armor=0;
    public:
        Treasure(int r, int c, int n, bool lootable, bool armor); 
        ~Treasure() = 0;
        void setlootable(bool l) override;
        bool islootable() override;
        bool isarmor() override;
        
};

#endif
