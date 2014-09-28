#ifndef OBSLUGA_H_INCLUDED
#define OBSLUGA_H_INCLUDED

#include <list>
#include <stack>
#include "domino.h"

class Handling{
private:
     bool play;
     std::stack<Domino> kladzione;
public:
    void ZapiszRuch(int a, int b);
    std::list<Domino> CofnijRuch(std::list<Domino>);
    bool getPlay();
    void setPlay(bool);
    Domino getTop();

};

#endif // OBSLUGA_H_INCLUDED
