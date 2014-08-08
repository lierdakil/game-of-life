#ifndef GAMECELL_H
#define GAMECELL_H

#include <iostream>
#include <memory>

class circulator;

class GameCell {
private:
    bool alive;
    uint neighbours,next_neighbours;
    std::unique_ptr<circulator> c,ce;
public:
    GameCell();
    bool evolve();
    void update();
    GameCell& operator=(circulator c);
    GameCell& operator=(const char c);
    GameCell& operator=(const GameCell& other);
    friend std::ostream& operator<<(std::ostream& s, const GameCell&c);
};

#endif // GAMECELL_H
