#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <list>
#include "domino.h"
#include "handling.h"

class Game : public Handling{
public:
    std::list<Domino> stol;
    std::list<Domino> gracz1;
    std::list<Domino> gracz2;
    std::list<Domino> niczyje;// kladzione do prywatnych

    int CzyjRuch;
    int X; //przechwuje poczatek weza
    int Y; //przechwuje koniec weza
    int antypetla; //przeciwdziala petli spowodowanej brakiem mozliwosci ruchu obu graczy

    void PrzydzielDomina(); //rozdziela domina na poczatku nowej gry
    int SprawdzRuch(std::list<Domino>); //sprawdza, czy dany gracz moze wykonac ruch
    void WypiszDomina(std::list<Domino>); //po kazdym dodaniu domina trzeba odswiezyc weza
    void WypiszStol(); //wypisuje wszyskie domina, jakie do tej pory zostaly polozone na 'stole' przez graczy
    void ZdejmijZeStolu(Domino); //w przypadku cofniecia ruchu
    int DodawanieDomin(std::list<Domino>); //dodaje karne domina z puli 'niczyich', gdy gracz nie ma mozliwosci ruchu
    std::list<Domino> ZrobRuch(char[], std::list<Domino>); //sprawdza, czy wpisanym przez gracza dominem moze on wykonac ruch
    void PodliczPunkty(); //rozstrzyga zwyciezce w przypadku remisu - podlicza punkty, mniejsza liczba oczek = mniej punktow = zwyciestwo

};

#endif // GAME_H_INCLUDED
