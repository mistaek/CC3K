#ifndef __entity_h__
#define __entity_h__
#include <utility>
#include <memory>

enum class EntityType{Player, Enemy, Potion, Treasure};

class Entity{
    EntityType type;
    int r, c;
    int hp = 0, atk = 0, def = 0, gval = 0;
    char mapchar;

    public:
        Entity(EntityType type, int r, int c,int hp, int atk, int def, int gval, char mapchar);
        EntityType getType(); 
        int gethp(); 
        int getatk(); 
        int getdef(); 
        int getgval();
        char getmapchar(); 
        std::pair<int, int> getpos();

        void sethp(int nhp); 
        void setatk(int natk); 
        void setdef(int ndef); 
        void setgval(int ngval);
        void setpos(int nr, int nc);


        bool isdead();
        virtual void move(std::pair<int, int> dir);
        virtual int strike(Entity* striking); 
        virtual int struck(Entity* struckby);
        
        virtual std::shared_ptr<Entity> die(Entity* killedby);

        virtual void sethostile(bool l);
        virtual void sethoard(Entity* hoard);
        virtual bool isHostile();
        virtual void setlootable(bool l);
        virtual bool islootable();
        virtual bool isarmor();
        virtual std::string getID();
        virtual void setdragon(Entity*); 
        virtual bool alertDragon(bool l);
        virtual void usepotion(Entity* potion); 
        virtual void usetreasure(Entity* treasure);
        virtual bool isStationary();
        virtual ~Entity() = 0;
};

#endif
