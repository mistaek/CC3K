#ifndef __tile_h__
#define __tile_h__
#include "subject.h"
#include <utility>
#include <memory>

class Entity;

class Tile: public Subject{
    protected:
        int r = 0, c = 0; 
        bool passable = 0;
        char mapchar;
        std::shared_ptr<Entity> entity;
    public:
        Tile(int r, int c, int passable, char mapchar);
        virtual ~Tile() = 0;
        
        bool getPassable();
        void setEntity(std::shared_ptr<Entity> entity);
        virtual void setVisible(bool l);
        virtual bool isStaircase();

        Entity* getEntity();
        std::shared_ptr<Entity> getEntityptr();
        char getmapchar(); 
        std::pair<std::pair<int, int>, char> getInfo() override; 
};
#endif
