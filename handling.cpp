#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <utility>
#include "handling.h"
#include "game.h"

using namespace std;

bool Handling::getPlay(){
  return play;
}

void Handling::setPlay(bool stan){
  play=stan;
}

Domino Handling::getTop(){
  //printf("handling get top \n");
  return kladzione.top();
}

void Handling::ZapiszRuch(int a, int b){
  Domino klocek= Domino(a,b);
  kladzione.push(klocek);
}

std::list<Domino> Handling::CofnijRuch(std::list<Domino> lista){
  printf("Procedura cofniecia ruchu.\n");

  Domino klocek=Domino(0,0);
  klocek.A = kladzione.top().A; //zapisuje wartosc klocka
  klocek.B = kladzione.top().B;

  kladzione.pop(); //usuwam go z kladzione

  lista.push_back(klocek); //oddaje poprzedniemu graczowi jego klocek
  return lista;
}
