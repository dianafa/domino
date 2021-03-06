#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <string>
#include "game.h"

using namespace std;


/*========================== GLOWNA FUNKCJA ==========================*/
int main(){
    Game gra;
    Handling nadzor;
    nadzor.setPlay(false);
    gra.CzyjRuch=1;
    gra.antypetla=0;
    char RUCH1[6], RUCH2[6];
    srand(time(NULL));
    string default_console = "\033[0m";
    string color1 = "\033[031m",color2 = "\033[032m";
	char ODP;

	system("clear");
	std::cout << "\n\t\tZechcesz zagrac w Domino? [T/N]" << std::endl;
	while(nadzor.getPlay()==0){
		fgets(&ODP,50,stdin);
		if((ODP == 84)||(ODP==116)){gra.PrzydzielDomina(); nadzor.setPlay(true);}
		else if((ODP == 78) || (ODP==110))return 0;
		else std::cout << "\t\tZla komenda. Chcesz grac? [T/N]" << std::endl;
	}

	while(nadzor.getPlay()){
		system("clear");
	    printf("\n*************************************************************************");
	    switch(gra.CzyjRuch){
        case 1:
            gra.WypiszStol();
            if(gra.SprawdzRuch(gra.gracz1)==1){
				std::cout<<color1;
                gra.WypiszDomina(gra.gracz1);
                fgets(RUCH1,50,stdin);
				if((RUCH1[0]==90) || (RUCH1[0]==122)){ //jesli nacisnelam 'z', cofam sie do sytuacji sprzed chwili
					if(gra.stol.size()>1){
					Domino kloc=Domino(0,0);
					kloc=nadzor.getTop();
					list<Domino> nowa;
					nowa=nadzor.CofnijRuch(gra.gracz2);
					gra.gracz2=nowa;
					gra.ZdejmijZeStolu(kloc);//sciagnac ze stolu
					gra.CzyjRuch=2; //oddaje poprzedniemu graczowi jego ruch
					}
					else{
					  printf("Cofnelismy się do poczatku gry!");
					}
				}
				else{
					gra.gracz1=gra.ZrobRuch(RUCH1, gra.gracz1);
					nadzor.ZapiszRuch(RUCH1[0]-48,RUCH1[2]-48);} //zapisz ruch do historii
					cout<<default_console<<std::endl;
			}
			if(gra.antypetla<3) gra.CzyjRuch=2;
			else {gra.CzyjRuch=0; nadzor.setPlay(false);}
			break;

		case 2:
            gra.WypiszStol();
		    if(gra.SprawdzRuch(gra.gracz2)==1){
			std::cout<<color2;
		        gra.WypiszDomina(gra.gracz2);
		        fgets(RUCH2,50,stdin);
                if((RUCH2[0]==90) || (RUCH2[0]==122)){ //jesli nacisnelam 'z', cofam sie do sytuacji sprzed chwili
			      if(gra.stol.size()>1){
			      Domino kloc=Domino(0,0);
			      kloc=nadzor.getTop();
			      list<Domino> nowa;
			      nowa=nadzor.CofnijRuch(gra.gracz1);
			      gra.gracz1=nowa;
			      gra.ZdejmijZeStolu(kloc);//sciagnac ze stolu
			      gra.CzyjRuch=1; //oddaje poprzedniemu graczowi jego ruch
			      }
			      else{
				    printf("Cofnelismy się do poczatku gry!");
				    
				  }
			      
			    }
                else{
                    gra.gracz2=gra.ZrobRuch(RUCH2, gra.gracz2);
                    nadzor.ZapiszRuch(RUCH2[0]-48,RUCH2[2]-48);
                } //zapisz ruch do historii
                cout<<default_console<<std::endl;
            }
            if(gra.antypetla<3) gra.CzyjRuch=1;
            else {gra.CzyjRuch=0; nadzor.setPlay(false);}
            break;
	    }
        if(gra.gracz1.size()==0 || gra.gracz2.size()==0) nadzor.setPlay(false); //jesli ktorys gracz pozbyl sie wszystkich domin, to game na false
	}
	gra.PodliczPunkty();

	return 0;
}
