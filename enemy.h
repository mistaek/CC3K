#ifndef __enemy_h__
#define __enemy_h__
#include "entity.h"

enum class EnemyType{Vampire, Werewolf, Troll, Goblin, Merchant, Dragon, Phoenix};
class Enemy : public Entity{
    EnemyType species;
    bool compass = 0;
    public:
        Enemy(int r, int c, int hp, int atk, int def, int gval, char mapchar, EnemyType species);
        bool isHostile() override;
        virtual ~Enemy() = 0;
};
#endif
