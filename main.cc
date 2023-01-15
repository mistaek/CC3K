#include "player.h"
#include "races/human.h" 
#include "enemies/goblin.h"
#include "entity.h"
#include "grid.h"
#include "game.h"
#include "textdisplay.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
#include <string>

int main(int argc, char *argv[]){
    Game g; 
    std::srand(std::time(nullptr));
    bool start = 0;
    while(true){
        if(!start){
            if(argc == 1) g.readMap("maps/cc3kfloorblank.txt"); //default map
            else if(argc == 2){
                std::string savefile = argv[1];
                g.readSave(savefile);
                start = 1;
                continue;
            }
            else if(argc == 3){
                std::string t = argv[1]; 
                std::string m = argv[2];
            if(t == "m") g.readMap(m); 
            else if(t == "s") g.readSave(m);
            }
            else{
                std::cout << "Usage: ./cc3k [ms] filename" << std::endl;
                return 0;
            }

            std::cout << "Welcome to CC3K! Start the game by picking a race: \n";
            std::cout << "Human: 140 HP, 20 ATK, 20 DEF. Score is multiplied by 1.5.\n";
            std::cout << "Elf : 140 HP, 30 ATK, 10 DEF. Negative potions have positive effect.\n";
            std::cout << "Dwarf: 100 HP, 20 ATK, 30 DEF. Gold is doubled in value. \n";
            std::cout << "Orc: 180 HP, 30 ATK, 25 DEF. Gold is halved in value.\n";
            std::cout << "Pick a race by entering h, e, d, or o, respectively." << std::endl;
        }
        
        
        std::string cmd; 
        std::getline(std::cin, cmd);
        if(std::cin.eof()) break;
        int status = g.command(cmd); 
        if(!start){
            std::cout << "Enter a direction to move: no so ea we ne nw se sw\n";
            std::cout << "Enter \"a <direction>\" to attack an enemy. Ex: a no\n";
            std::cout << "Enter \"u <direction>\" to use a potion. Ex: u no\n";
            std::cout << "Reach the staircases denoted \\ and climb the chamber to win!\n";
            std::cout << "To quit or restart, enter the commands q and r respectively.\n";
        }
        if(status == 0) g.takeTurn();
        //g.print();
        if(cmd == "q" || g.gg()) break;
        start = 1;
        if(cmd == "r") start = 0;
    }
    return 0;
}
