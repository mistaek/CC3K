#include "enemy.h"
#include "entity.h"

Enemy::Enemy(int r, int c, int hp, int atk, int def, int gval, char mapchar, EnemyType species): Entity{EntityType::Enemy, r, c, hp, atk, def, gval,mapchar}, species{species}{}
Enemy::~Enemy(){}

bool Enemy::isHostile(){
    return true;
}
