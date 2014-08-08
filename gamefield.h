#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include "../multiarray/multiarray.h"
#include "gamecell.h"

class GameField;

class circulator {
    const GameField* field;
    uint ci,cj;
    int di,dj;
public:
    circulator(GameField* f, uint ci, uint cj);
    circulator(const MultiArray<GameCell,2>::iterator& it);
    circulator& operator++();
    const GameCell& operator*();
    bool operator!=(const circulator &rhs);
};

class GameField : public MultiArray<GameCell,2> {
    friend class circulator;
    unsigned int w,h;
    bool xperiodic,yperiodic;
public:
    GameField(uint w, uint h, std::string init="", bool xperiodic=false, bool yperiodic=false);
    void evolve();
    friend std::ostream& operator<<(std::ostream& s, const GameField& f);
};

#endif // GAMEFIELD_H
