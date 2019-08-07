#include "gamefield.h"
#include <iostream>
#include <cmath>

circulator::circulator(MultiArray<GameCell,2>::iterator &it) : field(static_cast<GameField*>(it.parent())),
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
    if((ci+di>=field->h && !field->yperiodic) || (cj+dj>=field->w && !field->xperiodic))
        ++(*this);
    return *this;
}

GameCell &circulator::operator*(){
    return (*field)(
                field->yperiodic?(ci+di+field->h)%field->h:ci+di,
                field->xperiodic?(cj+dj+field->w)%field->w:cj+dj
                                 );
}

GameCell *circulator::operator->()
{
    return &(**this);
}

bool circulator::operator!=(const circulator &rhs) {
    return ci!=rhs.ci || cj!=rhs.cj || di!=rhs.di || dj!=rhs.dj;
}

GameField::GameField(uint w, uint h, std::string init, bool xperiodic, bool yperiodic) :
    MultiArray<GameCell,2>(h,w),
    w(w),
    h(h),
    xperiodic(xperiodic),
    yperiodic(yperiodic)
{
    for(iterator i=begin(); i!=end(); ++i)
        *i=circulator(i);
    std::copy(init.begin(),init.end(),begin());
}

void GameField::evolve() {
    for(auto& i : *this)
        i.update();
    for(auto& i : *this)
        i.evolve();
}

std::ostream& operator<<(std::ostream& s, const GameField& f) {
    s<<"╔";
    for(uint i=0; i<f.w; ++i) {
        s<<"═";
    }
    s<<"╗";
    for(auto i=f.const_begin(); i!=f.const_end(); ++i) {
        if(i.index()[1]==0)
            s<<(i==f.const_begin()?"":"║")<<std::endl<<"║";
        s<<*i;
    }
    s<<"║"<<std::endl<<"╚";
    for(uint i=0; i<f.w; ++i) {
        s<<"═";
    }
    s<<"╝"<<std::endl;
    return s;
}
