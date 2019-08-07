#include "gamecell.h"
#include <iostream>
#include <gamefield.h>

GameCell::GameCell() : alive(false), neighbours(0), next_neighbours(0) {

}

bool GameCell::evolve() {
    if(neighbours==3 && !alive) {
        do
            (*c)->next_neighbours++;
        while(++*c!=*ce);
        alive=true;
    } else if(neighbours!=2 && neighbours!=3 && alive) {
        do
            (*c)->next_neighbours--;
        while(++*c!=*ce);
        alive=false;
    }
    return alive;
}

void GameCell::update()
{
    neighbours=next_neighbours;
}

GameCell &GameCell::operator=(circulator c)
{
    this->c.reset(new circulator(c));
    this->ce.reset(new circulator(c));
    return *this;
}

GameCell &GameCell::operator=(const char c) {
    if(c!='0' && c!=' ' && c!='o' && c!='O') {
        alive=true;
        do
            (*this->c)->next_neighbours++;
        while(++(*this->c)!=*ce);
    } else
        alive=false;
    return *this;
}

GameCell &GameCell::operator=(const GameCell &other)
{
    alive=other.alive;
    neighbours=other.neighbours;
    next_neighbours=other.next_neighbours;
    c.reset(new circulator(*other.c));
    ce.reset(new circulator(*other.ce));
    return *this;
}

std::ostream& operator<<(std::ostream& s, const GameCell&c) {
    if(c.alive)
        s<<"▮";//▮
    else
        s<<" ";
    return s;
}
