#include "gamefield.h"
#include <iostream>
#include <cmath>

circulator::circulator(const MultiArray<GameCell,2>::iterator &it) : field(static_cast<const GameField*>(it.parent())),
    ci(it.index()[0]), cj(it.index()[1]), di(0), dj(1)
{
    ++(*this);
}

circulator::circulator(GameField *f, uint ci, uint cj) : field(f), ci(ci), cj(cj), di(0), dj(1) {
    ++(*this);
}

circulator &circulator::operator++() {
    double phi=std::atan2(dj,di)+M_PI_4;
    dj=1.5*sin(phi);
    di=1.5*cos(phi);
//    if(ci+di>=field->h || cj+dj>=field->w)
//        ++(*this);
    return *this;
}

const GameCell &circulator::operator*(){
    return (*field)((ci+di+field->h)%field->h,(cj+dj+field->w)%field->w);
}

bool circulator::operator!=(const circulator &rhs) {
    return ci!=rhs.ci || cj!=rhs.cj || di!=rhs.di || dj!=rhs.dj;
}

GameField::GameField(uint w, uint h, std::string init) :
    MultiArray<GameCell,2>(h,w),
    w(w),
    h(h)
{
    std::copy(init.begin(),init.end(),begin());
}

void GameField::evolve() {
    for(iterator i=begin(); i!=end(); ++i)
        i->calcNeighbours(circulator(i));
    for(auto& i : *this)
        i.evolve();
}

std::ostream& operator<<(std::ostream& s, const GameField& f) {
    for(uint i=0; i<f.w+1; ++i) {
        s<<'-';
    }
    for(auto i=f.const_begin(); i!=f.const_end(); ++i) {
        if(i.index()[1]==0)
            s<<"|"<<std::endl<<"|";
        s<<*i;
    }
    s<<"|"<<std::endl<<"|";
    for(uint i=0; i<f.w+1; ++i) {
        s<<'-';
    }
    s<<std::endl;
    return s;
}
