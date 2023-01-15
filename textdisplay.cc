#include "textdisplay.h"
#include "subject.h"
#include <string>

const std::string RED = "\033[31m";
const std::string YELLOW =  "\033[33m";
const std::string GREEN = "\033[32m";
const std::string CYAN = "\033[36m";
const std::string RESET =  "\033[0m";
const std::string REVERSE = "\033[7m";


TextDisplay::TextDisplay(int r, int c){
    for(int i = 0; i < r; i++){
        std::vector<char> v; 
        for(int j = 0; j < c; j++){
            v.emplace_back('-'); 
        }
        display.emplace_back(v);
    }
}

std::string TextDisplay::getcolor(char c) const{
    if(c == '@') return REVERSE;
    if(c == '\\') return REVERSE;
    if(c == 'W' || c == 'M' || c == 'T' || c == 'D' || c == 'X' || c == 'V' || c == 'N') return RED;
    if(c == 'P') return CYAN;
    if(c == 'G' || c == 'B') return YELLOW;
    return "";
}
void TextDisplay::notify(Subject &whoFrom){
    std::pair<std::pair<int, int>, char> info = whoFrom.getInfo();
    display[info.first.first][info.first.second] = info.second;
}

std::ostream &operator<<(std::ostream&out, const TextDisplay &td){
    for(int i = 0; i < td.display.size(); i++){
        for(int j = 0; j < td.display[i].size(); j++){
            if(td.display[i][j] == '@' || td.display[i][j] == '\\') out << td.getcolor(td.display[i][j]) << td.display[i][j] << RESET;
            else out  << td.display[i][j];
        }
        out << std::endl;
    }
    return out;
}
