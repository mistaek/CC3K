#ifndef __textdisplay_h__
#define __textdisplay_h__
#include "observer.h"
#include <vector>
#include <iostream>

class TextDisplay: public Observer{
    std::vector<std::vector<char>> display;
    public:
        TextDisplay(int r, int c);
        void notify(Subject &whoFrom) override;
        std::string getcolor(char c) const;
        friend std::ostream &operator<<(std::ostream &out, const TextDisplay &td);
};


#endif
