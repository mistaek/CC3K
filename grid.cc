#include "grid.h"
#include "tile.h"
#include "entity.h"
#include "player.h"
#include "tiles/verticalwall.h"
#include "tiles/horizontalwall.h"
#include "tiles/passage.h"
#include "tiles/doorway.h"
#include "tiles/staircase.h"
#include "tiles/void.h"
#include "tiles/floortile.h"
#include "races/human.h"
#include "races/elf.h"
#include "races/dwarf.h"
#include "races/orc.h"
#include "enemy.h"
#include "enemies/vampire.h"
#include "enemies/goblin.h"
#include "enemies/werewolf.h"
#include "enemies/troll.h"
#include "enemies/merchant.h"
#include "enemies/dragon.h"
#include "enemies/phoenix.h"
#include "potion.h"
#include "potions/bapotion.h"
#include "potions/bdpotion.h"
#include "potions/phpotion.h"
#include "potions/rhpotion.h"
#include "potions/wapotion.h"
#include "potions/wdpotion.h"
#include "treasure.h"
#include "treasure/biggold.h"
#include "treasure/smallgold.h"
#include "treasure/merchanthoard.h"
#include "treasure/dragonhoard.h"
#include "treasure/barriersuit.h"
#include "textdisplay.h"
#include <fstream>
#include <string>
#include <queue>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <map>
#include <iomanip>


std::string getdir(std::pair<int, int> dir){
    if(dir == std::make_pair(-1,0)) return "northward";
    if(dir == std::make_pair(1, 0)) return "southward"; 
    if(dir == std::make_pair(0, 1)) return "eastward"; 
    if(dir == std::make_pair(0, -1)) return "westward";
    if(dir == std::make_pair(-1, -1)) return "northwestward";
    if(dir == std::make_pair(-1, 1)) return "northeastward";
    if(dir == std::make_pair(1, -1)) return "southwestward"; 
    if(dir == std::make_pair(1, 1)) return "southeastward";
    return "";
}

void Grid::initiateTextDisplay(int i){
    td = std::make_unique<TextDisplay>(r, c);
    
    for(int j = 0; j < r; j++){
        for(int k = 0; k < c; k++){
            grid[i][j][k]->attach(td.get());
            grid[i][j][k]->notifyObservers();
        }
    }
}

void Grid::readMap(std::string filename){
    std::ifstream mapfile(filename); 
    std::string line; 
    for(int k = 0; k < 5; k++){
        std::vector<std::vector<std::shared_ptr<Tile>>> floor;
        for(int i = 0; i < r; i++){
            std::vector<std::shared_ptr<Tile>> row;
            std::getline(mapfile, line);
            for(int j = 0; j < c; j++){
                if(line[j] == '|') row.emplace_back(std::make_shared<VerticalWall>(i,j));
                else if(line[j] == '-') row.emplace_back(std::make_shared<HorizontalWall>(i,j));
                else if(line[j] == ' ') row.emplace_back(std::make_shared<Void>(i,j));
                else if(line[j] == '.') row.emplace_back(std::make_shared<FloorTile>(i,j));
                else if(line[j] == '+') row.emplace_back(std::make_shared<Doorway>(i,j));
                else if(line[j] == '#') row.emplace_back(std::make_shared<Passage>(i,j));
                else row.emplace_back(std::make_shared<Void>(i,j));
            }
            floor.emplace_back(row);
        }
        grid.emplace_back(floor);
    }
    mapfile.close();
}

void Grid::scanChambers(){
    for(int i =0; i < chambers.size(); i++){
        chambers[i].clear();
    }
    chambers.clear();
    bool vis[r][c] = {};
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if(grid[floor][i][j]->getmapchar() == '.' && !vis[i][j]){
                std::vector<std::pair<int, int>> chamber;
                vis[i][j] = 1; 
                std::queue<std::pair<int, int>> bfs;
                bfs.push({i,j});
                int dirx[8]= {-1, -1, 0, 1, 1, 1, 0, -1}, diry[8] = {0, 1, 1, 1, 0, -1, -1, -1};
                while(!bfs.empty()){
                    std::pair<int, int> frnt = bfs.front();
                    chamber.emplace_back(frnt);
                    bfs.pop();
                    for(int k = 0; k < 8; k++){
                        if(grid[floor][frnt.first + dirx[k]][frnt.second + diry[k]]->getmapchar() == '.' && !vis[frnt.first + dirx[k]][frnt.second + diry[k]]){
                            vis[frnt.first + dirx[k]][frnt.second + diry[k]] = 1;
                            bfs.push({frnt.first + dirx[k], frnt.second + diry[k]});
                        }
                    }
                }
                chambers.emplace_back(chamber);
            }
        }
    }
}

void Grid::readSave(std::string filename){
    std::ifstream savefile(filename);
    std::string playerInfo;
    std::getline(savefile, playerInfo);
    std::stringstream sin(playerInfo);
    char race; int hp, atk, def, gval, armor, sfloor;
    sin >> race >> hp >> atk >> def >> gval >> armor >> sfloor; 
    floor = sfloor;
    if(race == 'h') player = std::make_shared<Human>(0, 0);
    else if(race == 'e') player = std::make_shared<Elf>(0, 0);
    else if(race == 'd') player = std::make_shared<Dwarf>(0, 0);
    else if(race == 'o') player = std::make_shared<Orc>(0, 0);
    player->sethp(hp); player->setatk(atk); player->setdef(def); player->setgval(gval); player->setarmor(armor);
    for(int k =0; k < sfloor; k++){
        std::vector<std::vector<std::shared_ptr<Tile>>> layout;
        grid.emplace_back(layout);
    }
    for(int k = sfloor; k < 5; k++){
        std::vector<std::vector<std::shared_ptr<Tile>>> layout;
        for(int i = 0; i < r; i++){
            std::vector<std::shared_ptr<Tile>> row; 
            std::string line; 
            std::getline(savefile,line);
            for(int j = 0; j < c; j++){
                if(line[j] == '|') row.emplace_back(std::make_shared<VerticalWall>(i,j));
                else if(line[j] == '-') row.emplace_back(std::make_shared<HorizontalWall>(i,j));
                else if(line[j] == ' ') row.emplace_back(std::make_shared<Void>(i,j));
                else if(line[j] == '.') row.emplace_back(std::make_shared<FloorTile>(i,j));
                else if(line[j] == '+') row.emplace_back(std::make_shared<Doorway>(i,j));
                else if(line[j] == '#') row.emplace_back(std::make_shared<Passage>(i,j));
                else if(line[j] == '\\') row.emplace_back(std::make_shared<Staircase>(i,j));
                else if(line[j] == '@'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    if(k == sfloor) player->setpos(i,j);
                    tile->setEntity(player);
                    row.emplace_back(tile);
                }
                else if(line[j] == 'V'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<Vampire>(i,j));
                    row.emplace_back(tile);
                }
                else if(line[j] == 'N'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<Goblin>(i,j));
                    row.emplace_back(tile);
                }
                else if(line[j] == 'W'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<Werewolf>(i,j));
                    row.emplace_back(tile);
                }
                else if(line[j] == 'T'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<Troll>(i,j));
                    row.emplace_back(tile);
                }
                else if(line[j] == 'M'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<Merchant>(i, j));
                    row.emplace_back(tile);
                }
                else if(line[j] == 'D'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<Dragon>(i, j));
                    row.emplace_back(tile);
                }
                else if(line[j] == 'X'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<Phoenix>(i,j));
                    row.emplace_back(tile);
                }
                else if(line[j] == '0'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<RHPotion>(i, j));
                    row.emplace_back(tile);
                }
                else if(line[j] == '1'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<BAPotion>(i,j)); 
                    row.emplace_back(tile);
                }
                else if(line[j] == '2'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<BDPotion>(i,j));
                    row.emplace_back(tile);
                }
                else if(line[j] == '3'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<PHPotion>(i,j));
                    row.emplace_back(tile);
                }
                else if(line[j] == '4'){
                    auto tile = std::make_shared<FloorTile>(i,j);
                    tile->setEntity(std::make_shared<WAPotion>(i,j));
                    row.emplace_back(tile);
                }
                else if(line[j] == '5'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<WDPotion>(i,j));
                    row.emplace_back(tile);
                }
                else if(line[j] == '6'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<SmallGold>(i,j));
                    row.emplace_back(tile);
                }
                else if(line[j] == '7'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<BigGold>(i,j));
                    row.emplace_back(tile);
                }
                else if(line[j] == '8'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<MerchantHoard>(i,j)); 
                    row.emplace_back(tile);
                }
                else if(line[j] == '9'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<DragonHoard>(i,j));
                    row.emplace_back(tile);
                }
                else if(line[j] == 'B'){
                    auto tile = std::make_shared<FloorTile>(i, j);
                    tile->setEntity(std::make_shared<BarrierSuit>(i,j));
                    row.emplace_back(tile);
                }
                else row.emplace_back(std::make_shared<Void>(i,j));         
            }
            layout.emplace_back(row);
        }
        grid.emplace_back(layout);
    }
    for(int k = sfloor; k < 5; k++){
        for(int i = 0; i < r; i++){
            for(int j = 0; j < c; j++){
                Entity* entity = grid[k][i][j]->getEntity();
                if(entity != nullptr && entity->getType() == EntityType::Treasure && (entity->getgval() == 6 || entity->isarmor() == true)){
                    int dirx[8]= {-1, -1, 0, 1, 1, 1, 0, -1}, diry[8] = {0, 1, 1, 1, 0, -1, -1, -1};
                    for(int looper = 0; looper < 8; looper++){
                        Entity* maybedragon = grid[k][i+dirx[looper]][j + diry[looper]]->getEntity();
                        if(maybedragon != nullptr && maybedragon->getType() == EntityType::Enemy && maybedragon->isStationary() == true){
                            entity->setdragon(maybedragon);
                            maybedragon->sethoard(entity);
                        }
                    }
                }
            }
        }
    }
    savefile.close();
    initiateTextDisplay(sfloor);
    printStatus();
    std::cout << "Action: Loaded save\n";
}

void Grid::generateSuit(){
    std::pair<int, int> tile = selecttile();
    auto gold = std::make_shared<BarrierSuit>(tile.first, tile.second);
    grid[floor][tile.first][tile.second]->setEntity(gold);
    int dirx[8]= {-1, -1, 0, 1, 1, 1, 0, -1}, diry[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    for(int looper = 0; looper < 8; looper++){
        Entity* entity = grid[floor][tile.first+dirx[looper]][tile.second + diry[looper]]->getEntity();
        if(entity == nullptr && grid[floor][tile.first+dirx[looper]][tile.second + diry[looper]]->getPassable()){
            std::shared_ptr<Entity> dragon = std::make_shared<Dragon>(tile.first + dirx[looper], tile.second+ diry[looper]);
            grid[floor][tile.first+dirx[looper]][tile.second + diry[looper]]->setEntity(dragon);
            gold->setdragon(dragon.get());
            dragon->sethoard(gold.get());
            break;
        }
    }
}

void Grid::generate(std::string race){
    if(race == "h") player = std::make_shared<Human>(0, 0);
    if(race == "e") player = std::make_shared<Elf>(0, 0);
    if(race == "d") player = std::make_shared<Dwarf>(0,0); 
    if(race == "o") player = std::make_shared<Orc>(0, 0);
    int sfloor = rand() % 5;
    for(floor = 0; floor < 5; floor++){
        scanChambers();
        generateStairs(generatePlayer());
        generatePotions();
        if(floor == sfloor) generateSuit();
        generateEnemies(generateGold());
    }
    floor = -1;
}

int Grid::generatePlayer() {
    int chamberchoice = rand() % chambers.size();
    int tilechoice = rand() %chambers[chamberchoice].size();
    grid[floor][chambers[chamberchoice][tilechoice].first][chambers[chamberchoice][tilechoice].second]->setEntity(player);
    if(floor == 0) player->setpos(chambers[chamberchoice][tilechoice].first, chambers[chamberchoice][tilechoice].second);
    return chamberchoice;
}

void Grid::generateStairs(int pc) {
    int chamberchoice = rand() % chambers.size(); 
    while(chamberchoice == pc){
        chamberchoice = rand() % chambers.size(); 
    }
    int tilechoice = rand() %chambers[chamberchoice].size();
    grid[floor][chambers[chamberchoice][tilechoice].first][chambers[chamberchoice][tilechoice].second] = std::make_shared<Staircase>(chambers[chamberchoice][tilechoice].first, chambers[chamberchoice][tilechoice].second);
}

std::pair<int, int> Grid::selecttile(){
    int chamberchoice = rand() % chambers.size();
    int tilechoice = rand() %chambers[chamberchoice].size();
    if(!grid[floor][chambers[chamberchoice][tilechoice].first][chambers[chamberchoice][tilechoice].second]->getPassable() || grid[floor][chambers[chamberchoice][tilechoice].first][chambers[chamberchoice][tilechoice].second]->getEntity() != nullptr) return selecttile();
    return chambers[chamberchoice][tilechoice];
}
void Grid::generatePotions() {
    int pots = 10;
    while(pots > 0){
        std::pair<int, int> tile = selecttile();
        std::shared_ptr<Entity> potion = createPotion(tile.first, tile.second);
        grid[floor][tile.first][tile.second]->setEntity(potion);
        pots--;
    }
}

std::shared_ptr<Entity> Grid::createPotion(int nr, int nc){
    int potiontype = rand() % 6;
    if(potiontype == 0) return std::make_shared<BAPotion>(nr, nc); 
    if(potiontype == 1) return std::make_shared<BDPotion>(nr, nc);
    if(potiontype == 2) return std::make_shared<RHPotion>(nr, nc);
    if(potiontype == 3) return std::make_shared<PHPotion>(nr, nc);
    if(potiontype == 4) return std::make_shared<WAPotion>(nr, nc);
    if(potiontype == 5) return std::make_shared<WDPotion>(nr, nc);
    return nullptr;
}

int Grid::generateGold() {
    int ngold = 10, dragons = 0;
    while(ngold > 0){
        std::pair<int, int> tile = selecttile();
        std::shared_ptr<Entity> gold = createTreasure(tile.first, tile.second);
        grid[floor][tile.first][tile.second]->setEntity(gold);
        if(gold->getgval() == 6 || gold->isarmor()){
            int dirx[8]= {-1, -1, 0, 1, 1, 1, 0, -1}, diry[8] = {0, 1, 1, 1, 0, -1, -1, -1};
            for(int looper = 0; looper < 8; looper++){
                Entity* entity = grid[floor][tile.first+dirx[looper]][tile.second + diry[looper]]->getEntity();
                if(entity == nullptr && grid[floor][tile.first+dirx[looper]][tile.second + diry[looper]]->getPassable()){
                    std::shared_ptr<Entity> dragon = std::make_shared<Dragon>(tile.first + dirx[looper], tile.second+ diry[looper]);
                    grid[floor][tile.first+dirx[looper]][tile.second + diry[looper]]->setEntity(dragon);
                    gold->setdragon(dragon.get());
                    dragon->sethoard(gold.get());
                    break;
                }
            }
        }
        ngold--;
    }
    return dragons;
}

std::shared_ptr<Entity> Grid::createTreasure(int nr, int nc){
    int ttype = rand() % 8;
    if(ttype < 5) return std::make_shared<SmallGold>(nr, nc);
    else if (ttype < 7) return std::make_shared<BigGold>(nr, nc);
    else if(ttype == 7) return std::make_shared<DragonHoard>(nr, nc);
    return nullptr;
}
void Grid::generateEnemies(int d) {
    int enemies = 20-d;
    while(enemies > 0){
        std::pair<int, int> tile = selecttile();
        std::shared_ptr<Entity> enemy = createEnemy(tile.first, tile.second);
        grid[floor][tile.first][tile.second]->setEntity(enemy);
        enemies--;
    }
}

std::shared_ptr<Entity> Grid::createEnemy(int nr, int nc){
    int etype = rand() % 18;
    if(etype < 4) return std::make_shared<Werewolf>(nr, nc);
    else if(etype < 7) return std::make_shared<Vampire>(nr, nc);
    else if(etype < 12) return std::make_shared<Goblin>(nr, nc);
    else if(etype < 14) return std::make_shared<Troll>(nr, nc);
    else if(etype <16) return std::make_shared<Phoenix>(nr, nc); 
    else if(etype < 18) return std::make_shared<Merchant>(nr, nc);
    return nullptr; 
}
int Grid::movePlayer(std::pair<int, int> dir){
    if((dir.first == 0 && dir.second == 0) || player == nullptr || floor < 0 || floor >= 5){ std::cout << "Can't move in that direction!\n"; return 1;}
    std::pair<int, int> ppos = player->getpos();
    if(grid[floor][ppos.first + dir.first][ppos.second + dir.second]->isStaircase()){
        return 2;
    }
    if(grid[floor][ppos.first + dir.first][ppos.second + dir.second]->getPassable()){
        Entity* entity = grid[floor][ppos.first + dir.first][ppos.second + dir.second]->getEntity(); 
        if(entity == nullptr){
            grid[floor][ppos.first + dir.first][ppos.second + dir.second]->setEntity(player);
            grid[floor][ppos.first][ppos.second]->setEntity(nullptr);
            player->move(dir);
            printStatus(); 
            actionMove(dir);
            return 0;
        }
        else if(entity->getType() == EntityType::Treasure){
            if(entity->islootable()){
                player->usetreasure(entity);
                player->move(dir);
                grid[floor][ppos.first + dir.first][ppos.second + dir.second]->setEntity(player);
                grid[floor][ppos.first][ppos.second]->setEntity(nullptr);
                printStatus();
                actionMoveTreasure(dir, entity);
                return 0;
            }
            else {
                 std::cout << "You can't pick up that treasure!\n"; return 1;
            }
        }
        else{
             std::cout << "Can't move in that direction!\n"; return 1;
        }
    }
    else{
        std::cout << "Can't move in that direction!\n"; return 1;
    }
    return 1;
}

int Grid::playerAttack(std::pair<int, int> dir){
    std::pair<int, int> ppos = player->getpos();
    Entity* entity = grid[floor][ppos.first + dir.first][ppos.second + dir.second]->getEntity();
    if(entity != nullptr && entity->getType() == EntityType::Enemy){
        player->strike(entity);
        if(entity->isdead()) grid[floor][ppos.first + dir.first][ppos.second+dir.second]->setEntity(entity->die(player.get()));
        printStatus(); 
        actionAttack(entity);
        return 0;
    } 
    else{
        std::cout <<"You can't attack that!\n"; return 1;
    }

    return 1;
}
int Grid::usePotion(std::pair<int, int> dir){
    std::pair<int, int> ppos = player->getpos();
    Entity* entity = grid[floor][ppos.first + dir.first][ppos.second+dir.second]->getEntity();
    if(entity!= nullptr && entity->getType() == EntityType::Potion){
        std::string ID = entity->getID();
        player->usepotion(entity);
        grid[floor][ppos.first + dir.first][ppos.second+dir.second]->setEntity(entity->die(player.get()));
        printStatus(); 
        actionDrink(ID);
        return 0;
    }
    else{
        std::cout << "You can't drink that!\n";
        return 1;
    }
    return 1;
}

void Grid::actionMove(std::pair<int, int> dir){
    std::pair<int, int> ppos = player->getpos();
    std::cout << "Action: Player moved " << getdir(dir); 
    int dirx[8]= {-1, -1, 0, 1, 1, 1, 0, -1}, diry[8] = {0, 1, 1, 1, 0, -1, -1, -1};
    for(int i = 0; i < 8; i++){
        Entity* entity = grid[floor][ppos.first + dirx[i]][ppos.second + diry[i]]->getEntity();
        if(entity != nullptr && entity->getType() == EntityType::Potion){
            std::cout << " and saw a " << entity->getID();
        }
    }
    std::cout << std::endl;
}

void Grid::actionMoveTreasure(std::pair<int, int> dir, Entity* treasure){
    std::string bounty; 
    if(treasure->getgval() == 1) bounty = "small pile of treasure";
    if(treasure->getgval() == 2) bounty = "big pile of treasure"; 
    if(treasure->getgval() == 4) bounty = "merchant's treasure hoard";
    if(treasure->getgval() == 6) bounty = "dragon's treasure hoard";
    if(treasure->getgval() == 0){ bounty = "barrier suit!!";}
    std::cout <<"Action: Player moved " << getdir(dir) << " and claimed a " << bounty << "!" << std::endl;
}

void Grid::actionAttack(Entity* enemy){
    std::cout <<"Action: Player attacked "<< enemy->getmapchar() << " (" << std::max(0, enemy->gethp()) << " HP)"<< std::endl; 
}

void Grid::actionDrink(std::string ID){
    std::cout << "Action: Player drank " << ID << std::endl;
}

void Grid::moveEnemies(){
    std::pair<int, int> ppos = player->getpos();
    int dmg = 0, alert = 0;
    std::map<std::pair<int, int>, bool> moved;
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if(moved.count({i,j}) == 0) moved[{i, j}] = 0;
            if(moved[{i, j}] == true) continue;
            auto eptr = grid[floor][i][j]->getEntityptr();
            Entity* entity =grid[floor][i][j]->getEntity();
            if(entity == nullptr) continue;
            std::pair<int, int> epos = entity->getpos();
            if(entity->getType() == EntityType::Enemy){
                if(entity->isHostile() && std::abs(ppos.first - epos.first) <= 1 && std::abs(ppos.second - epos.second) <= 1){
                    int tryhit = rand()%2; 
                    if(tryhit) dmg += entity->strike(player.get());
                }
                else{
                    if(entity->isStationary()){
                        continue; 
                    }
                    else{
                        int dirx[8] = {-1, -1, 0, 1, 1, 1, 0, -1}, diry[8] = {0, 1, 1, 1, 0, -1, -1, -1};
                        std::vector<std::pair<int, int>> movable;
                        for(int k = 0; k < 8; k++){
                            if(grid[floor][i + dirx[k]][j + diry[k]]->getPassable() && grid[floor][i + dirx[k]][j + diry[k]]->getEntity() == nullptr){
                                movable.emplace_back(std::make_pair(dirx[k], diry[k]));
                            }
                        }
                        int choice = rand() % movable.size();
                        std::pair<int, int> dir = movable[choice];
                        entity->move(dir);
                        grid[floor][i+dir.first][j + dir.second]->setEntity(eptr);
                        grid[floor][i][j]->setEntity(nullptr);
                        moved[{i + dir.first, j + dir.second}] = 1;
                    }
                }
            }
            if(entity->getType() == EntityType::Treasure){
                if(std::abs(ppos.first - epos.first) <= 1 && std::abs(ppos.second - epos.second) <= 1){
                    if(entity->alertDragon(true)){
                        alert = 1;
                    }
                }
                else entity->alertDragon(false);
            }
            moved[{i, j}] = 1;
        }
    }
    printStatus();
    std::cout << "Action: ";
    if(dmg) actionplayerAttacked(dmg);
    if(alert) std::cout << (dmg ? " " : "") <<  "A dragon has noticed your presence...";
    if(!(dmg || alert)) std::cout <<"Enemies have moved.";
    std::cout << std::endl;
}

void Grid::actionplayerAttacked(int dmg){
    std::cout << "Player was attacked for " << dmg << " damage.";
}

void Grid::resetPlayer(){
    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            Entity* entity = grid[floor][i][j]->getEntity();
            if(entity!= nullptr && entity->getType() == EntityType::Player){
                player->setpos(i, j);
                break;
            }
        }
    }
    player->resetstats();
    initiateTextDisplay(floor);
    printStatus();
    std::cout << "Action: Welcome to floor " << floor + 1 << std::endl;
}


void Grid::printStatus(){
    std::cout << *(td);
    std::cout<< "Race: " << player->getrace() << " Gold: " << player->getgval() << std::setw(55) << "Floor " << floor+1 << "\n";
    std::cout << "HP: " << std::max(player->gethp(), 0) << "\n";
    std::cout << "Atk: " << player->getatk() << "\n";
    std::cout << "Def: " << player->getdef() << std::endl;
}


void Grid::reset(){
    floor = -1;
    for(int i = 0; i < grid.size(); i++){
        for(int j = 0; j < grid[i].size(); j++){
            grid[i][j].clear();
        }
        grid[i].clear();
    }
    for(int i = 0; i < chambers.size(); i++){
        chambers[i].clear(); 
    }
    chambers.clear();
    grid.clear();
    
}

std::ostream &operator<<(std::ostream &out, const Grid &g){
    out << *(g.td);
    return out; 
}
