#ifndef GAMECELL_H
#define GAMECELL_H

#include <iostream>

class circulator;

class GameCell {
private:
    bool alive;
    uint neighbours;
public:
    GameCell();
    void calcNeighbours(circulator c);
    bool evolve();
    GameCell& operator=(const char c);
    friend std::ostream& operator<<(std::ostream& s, const GameCell&c);
};

#endif // GAMECELL_H
