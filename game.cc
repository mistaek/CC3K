#include "game.h"
#include "player.h"
#include "entity.h"
#include "grid.h"
#include <string>
#include <sstream>
#include <iostream>

std::pair<int, int> Game::getdir(std::string dir){
    if(dir == "no") return {-1, 0};
    if(dir == "so") return {1, 0}; 
    if(dir == "ea") return {0, 1}; 
    if(dir == "we") return {0, -1};
    if(dir == "ne") return {-1, 1}; 
    if(dir == "nw") return {-1, -1}; 
    if(dir == "se") return {1, 1}; 
    if(dir == "sw") return {1, -1};
    return {0, 0};
}

int Game::command(std::string cmd){
    std::stringstream sin(cmd);
    std::string cmd1;
    if(g.floor == -1){
        sin >> cmd1; 
        if(cmd1 == "h" || cmd1 == "e" || cmd1 =="d" || cmd1 == "o"){
            g.generate(cmd1);
            floorcomplete();
        }
        else{
            std::cout<<"That's not a race!" << std::endl;
        }
    }
    else{
        sin >> cmd1; 
        if(cmd1 == "u"){
            sin >> cmd1; 
            std::pair<int, int> dir = getdir(cmd1);
            return g.usePotion(dir);
        }
        else if(cmd1 == "a"){
            sin >> cmd1; 
            std::pair<int, int> dir = getdir(cmd1);
            return g.playerAttack(dir);
        }
        else if(cmd1 == "q"){
            return -1;
        }
        else if(cmd1 == "r"){
            g.reset();
            return 1;
        }
        else{
            sin >> cmd1; 
            std::pair<int, int> dir = getdir(cmd1); 
            int cmdstatus = g.movePlayer(dir);
            if(cmdstatus == 2){
                floorcomplete(); 
            }
            return cmdstatus;
        }
    }
    return 1;
}

void Game::readMap(std::string filename){
    g.readMap(filename);
}

void Game::readSave(std::string filename){
    g.readSave(filename);
}


void Game::takeTurn(){
    g.moveEnemies();
}

void Game::floorcomplete(){
    g.floor++;
    if(g.floor >= 5) return;
    g.resetPlayer();
}

bool Game::gg(){
    if(g.player->isdead()){
        std::cout << "You died! Score: " << g.player->getscore() << std::endl;
        return true;
    }
    if(g.floor == 5){
        std::cout << "You escaped the chamber! Score: " << g.player->getscore() << std::endl;
        return true;
    }
    return false;
}
