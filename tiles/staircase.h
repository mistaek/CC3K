#ifndef __staircase_h__
#define __staircase_h__
#include "../tile.h"
#include <utility>

class Staircase:public Tile{
    bool visible=0;
    public:
        Staircase(int r, int c);
        void setVisible(bool visible) override;
        bool isStaircase() override;
        std::pair<std::pair<int, int>, char> getInfo() override;
};

#endif
