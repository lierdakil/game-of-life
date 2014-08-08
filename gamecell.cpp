#include "gamecell.h"
#include <iostream>
#include <gamefield.h>

GameCell::GameCell() : alive(false), neighbours(0) {

}

void GameCell::calcNeighbours(circulator c) {
    circulator ce(c);
    uint& n=neighbours=0;
    do
        if((*c).alive)n++;
    while(++c!=ce);
}

bool GameCell::evolve() {
    uint& n=neighbours;
    if(n>=2 && n<=3 && (alive || n==3))
        return alive=true;
    else
        return alive=false;
    n=0;
}

GameCell &GameCell::operator=(const char c) {
    if(c!='0' && c!=' ' && c!='o' && c!='O')
        alive=true;
    else
        alive=false;
    return *this;
}

std::ostream& operator<<(std::ostream& s, const GameCell&c) {
    if(c.alive)
        s<<'x';
    else
        s<<' ';
    return s;
}
