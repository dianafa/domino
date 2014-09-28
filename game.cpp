#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include <utility>
#include "game.h"

using namespace std;

/*========================== PRZYDZIEL DOMINA ==========================*/
//Tworzenie list z przydzialem domin dla kazdego z graczy. Uzywana w funkcji main tylko raz przy zaczeciu nowej gry.
void Game::PrzydzielDomina(){
    int gdzie;
    int x=0;
    for(int i=0; i<=6; i++){
        for(int j=x; j<=6; j++){
            gdzie=rand() % 3;
            switch(gdzie){
            case 0:{
                if(gracz1.size()<7){
                    Domino tmp1= Domino(i,j);
                    gracz1.push_back(tmp1);
                }
                else if(niczyje.size()<14){ //gdyby tego nie bylo, gdzies byloby za malo klockow
                    Domino tmp3 = Domino(i,j);
                    niczyje.push_back(tmp3);
                }
                break;
            }
            case 1:{
                if(gracz2.size()<7){
                    Domino tmp2= Domino(i,j);
                    gracz2.push_back(tmp2);
                }
                else if(gracz1.size()<7){ //gdyby tego nie bylo, gdzies byloby za malo klockow
                    Domino tmp1= Domino(i,j);
                    gracz1.push_back(tmp1);
                }
                break;
            }
            case 2:{
                if(niczyje.size()<14){
                    Domino tmp3= Domino(i,j);
                    niczyje.push_back(tmp3);
                }
                else if(gracz2.size()<7){
                    Domino tmp2= Domino(i,j);
                    gracz2.push_back(tmp2);
                }
                break;
            }
            }
        }
        x++;
    }
    x=rand() % 14; //poczatkowy klocek rzucony na stół to randomowy z niczyich
    list<Domino>::iterator poz;
    poz=niczyje.begin();
    for(; x>0; x--)
       poz++;
    Domino start=Domino(poz->A,poz->B);
    stol.push_back(start); //kladziemy pierwsze domino na stol
    X=poz->A;
    Y=poz->B;
    niczyje.erase(poz); //usuwamy je z listy niczyje
}
/*========================== DODAWANIE DOMIN ==========================*/
int Game::DodawanieDomin(std::list<Domino> lista_gracza){

    bool czy_juz_moze=0;

    if(niczyje.size()<1){ //jesli w puli niewykorzystanych nie ma juz klockow
        cout << "\n\t\tSkonczyly sie wolne domina. Brak ruchu. Gra skonczona.\n" << std::endl;
        setPlay(false); //konczymy gre
        return 0;
    }
    while((niczyje.size()>0)&&(czy_juz_moze==0)){ //tu dodalam ze usuwa pierwszy z listy niczyje i dodaje go + sprawdzenie, czy juz teraz moze wykonac ruch
        list<Domino>::iterator poz;
        poz=niczyje.begin();
        Domino tmp2=Domino(poz->A,poz->B);
        lista_gracza.push_back(tmp2); //dajemy domino graczowi
        niczyje.erase(poz); //usuwamy je z listy niczyje
        printf("Gracz %d otrzymal wlasnie klocek: [%d|%d].\n", CzyjRuch,poz->A,poz->B);
        list<Domino>::iterator tmp;
        for(tmp=lista_gracza.begin(); tmp!=lista_gracza.end(); tmp++)
            if ((tmp->A==X) || (tmp->B==X) || (tmp->A==Y) || (tmp->B==Y)) czy_juz_moze=1;
       (CzyjRuch==1)? (gracz1=lista_gracza) : (gracz2=lista_gracza);
    }
    return 1;
}

/*========================== SPRAWDZ RUCH ==========================*/
//Sprawdza, czy w puli domin danego gracza jest domino, ktore mozna przylozyc do koncowki X lub Y. Jesli nie, to wywoluje funkcje dodawania wolnych domin.
int Game::SprawdzRuch(std::list<Domino> lista_gracza){
	list<Domino>::iterator tmp;
	for(tmp=lista_gracza.begin(); tmp!=lista_gracza.end(); tmp++){ //moze wykonac ruch
        if((tmp->A==X) || (tmp->B==X) || (tmp->A==Y) || (tmp->B==Y)){
            antypetla=0;
            return 1;
        }
	}
    cout << "\nGracz "<<CzyjRuch<<" nie moze zrobic ruchu.\n";
    if(niczyje.size()>0){
        DodawanieDomin(lista_gracza);
        return 1;
    }
    else{
        cout<<"\nBrak wolnych klockow do przydzielenia graczowi."<<endl;
	    if(CzyjRuch==1 && antypetla==0) antypetla=1;
        else if(CzyjRuch==2 && antypetla==0) antypetla=2;
        else if((CzyjRuch==2 && antypetla==1) || (CzyjRuch==1 && antypetla==2)) antypetla=3;

        return -1;
    }
    return 0;
}

/*========================== WYPISZ STOL ==========================*/
//Wypisuje domina aktualnie polozone na stole.
void Game::WypiszStol(){
	list<Domino>::iterator tmp;
    cout << "\n \t \t \t A TYMCZASEM NA STOLE:" << std::endl;
    cout << "\t \t \t" << std::endl;
	for(tmp=stol.begin(); tmp!=stol.end(); tmp++)
        cout << "["<<tmp->A<<"|"<<tmp->B<<"]";
	cout << "\n \t \t \t ~~~~~~~~~~~~~~~~~~~~\n" << std::endl;
}

/*========================== WYPISZ DOMINA ==========================*/
//Wypisuje domina aktualnie dostepne dla danego gracza(x).
void Game::WypiszDomina(list<Domino> lista_){
	list<Domino>::iterator tmp;
	std::cout << "\nDomina Gracza " << CzyjRuch << ":\t";
	for(tmp=lista_.begin(); tmp!=lista_.end(); tmp++)
	  cout << "["<<tmp->A<<"|"<<tmp->B<<"]" << "  ";
	cout << "\nCzyn swoj ruch, Graczu " << CzyjRuch << "..." << std::endl;
}

/*========================== ZROB RUCH ==========================*/
//Sprawdza, czy wybrane przez gracza domino jest w puli jego klocków oraz czy mozna je przylozyc do koncowki X lub Y.
list<Domino> Game::ZrobRuch(char tab[], std::list<Domino> lista_gracza){
    int posiada_wylozony=0; //sprawdza, czy gracz faktycznie posiada wypisany klocek
    list<Domino>::iterator tmp;
    list<Domino>::iterator cousun;
    tmp=lista_gracza.begin();
    for(; tmp!=lista_gracza.end(); tmp++){ //jesli posiadamy.A jest rowny znakowi wpisanemu itd...
        if((posiada_wylozony==0)&&(((tmp->A==tab[0]-48) && (tmp->B==tab[2]-48)) || ((tmp->A==tab[2]-48) && (tmp->B==tab[0]-48)))){
            posiada_wylozony=1;
            tmp=lista_gracza.erase(tmp); //zabieramy graczowi ten klocek
        }
    }
    if(posiada_wylozony){ //dopasowuje wybrany przez gracza klocek do koncowek weza
        if(tab[0]-48==Y){ //dodaj na koncu: A B
            Domino klocek=Domino(Y,tab[2]-48);
            stol.push_back(klocek);//dodaj na stol
	        Y=tab[2]-48;
        }
        else if(tab[2]-48==X){ //dodaj na poczatku: A B
            Domino klocek=Domino(tab[0]-48,X);
            stol.push_front(klocek);//dodaj na stol
            X=tab[0]-48;
        }
        else if((tab[0]-48==X)){ //trzeba zmienic kolejnosc klocka //dodaj na poczatku: B A
            Domino klocek=Domino(tab[2]-48,X);
            stol.push_front(klocek);//dodaj na stol
            X=tab[2]-48;
        }
        else if(tab[2]-48==Y){ //dodaj na koncu: B A
            Domino klocek=Domino(Y,tab[0]-48);
            stol.push_back(klocek);//dodaj na stol
            Y=tab[0]-48;
        }
        else{ //posiada wylozony, ale nie pasuje on do zadnej z koncowek
		  cout << "\nWybrane domino nie pasuje do zadnej z koncowek! Wybierz jeszcze raz." << endl;
		  fgets(tab,50,stdin);
		  Game::ZrobRuch(tab,lista_gracza);
	    }
    }
    else{ //nie posiada wypisanego klocka
        cout << "\nNiewlasciwie dobrane domino. Wybierz ponownie. [Nalezy wpisac w postaci:  A.B  (gdzie A i B to cyfry).]" << endl; //
        fgets(tab,50,stdin);
        Game::ZrobRuch(tab,lista_gracza);
    }

  posiada_wylozony=0;
  return lista_gracza;
}

/*========================== PODLICZ PUNKTY ==========================*/
//W przypadku remisu zwyciezca wybierany jest na podstawie mniejszej sumy oczek wszystkich jego pozostalych domin.
void Game::PodliczPunkty(){
    int suma1=0, suma2=0;
    list<Domino>::iterator tmp;
    for(tmp=gracz1.begin(); tmp!=gracz1.end(); tmp++)
        suma1=suma1+tmp->A+tmp->B;
    for(tmp=gracz2.begin(); tmp!=gracz2.end(); tmp++)
        suma2=suma2+tmp->A+tmp->B;

	if(suma1 < suma2) std::cout << "\n\n\n\nSuma punktow: \n Gracz 1:" << suma2 <<"\nGracz 2: "<< suma1 << "\n\n\n\t\t Chwalebne zwyciestwo Gracza 1!\n\n\n" << std::endl;
	else if(suma1 > suma2) std::cout << "\n\n\n\nSuma punktow: \n Gracz 1:" << suma2 <<"\nGracz 2: "<< suma1 << "\n\n\n\t\t Chwalebne zwyciestwo Gracza 2!\n\n\n" << std::endl;
	else std::cout << "\n\n\n\nSuma punktow: \n \t Gracz 1:" << suma1 <<"\nGracz 2: "<< suma2<< "\n\n\n\t\t Remis!\n\n\n" << std::endl;
}

/*========================== ZDEJMIJ ZE STOLU ==========================*/
void Game::ZdejmijZeStolu(Domino co){
    list<Domino>::iterator tmp; 
    tmp=stol.begin();
    for(; tmp!=stol.end(); tmp++){
        if(((tmp->A==co.A) && (tmp->B==co.B)) || (tmp->B==co.A) && (tmp->A==co.B))
        tmp=stol.erase(tmp);
    }
}
