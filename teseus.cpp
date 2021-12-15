#include "teseus.hpp"
#include <iostream>
using namespace std;
void teseus::buscar(const laberint & M,const posicio & inici, const posicio & final,std::list<posicio> & L) throw(error){
    posicio PosAct(inici.first, inici.second);
    posicio pos[2];
    pos[0] = PosAct;

    nat Ffila = final.first;
    nat Fcol = final.second;
    cambra c;

    if( inici == final) L.push_back(inici);
    else if (inici.first <= 0 || inici.first > M.num_files() || inici.second <= 0 || inici.second > M.num_columnes()
          || Ffila <= 0 || Ffila > M.num_files() || Fcol <= 0 || Fcol > M.num_columnes() ){
            throw error(IniciFinalNoValid);
    }
    else{
      while(PosAct != final){
            //cout<<"AAAAAAAAAAAAAAAAA"<<endl;
            //PosAct.first = i;
            //PosAct.second = j;
            posicio aux(PosAct.first, PosAct.second);
            c = M(PosAct);

      	     //pos[]
             //cout<<pos[0].first<<" "<<pos[0].second<<endl;
            if(c.porta_oberta(paret("nord")) == false && c.porta_oberta(paret("est")) == false && c.porta_oberta(paret("sud")) == false && c.porta_oberta(paret("oest")) == false){
                throw error(SenseSolucio);
            }
            else if(c.porta_oberta(paret("nord")) and (pos[0].first != aux.first-1 || pos[0].second != aux.second )){
                L.push_back(PosAct);
                pos[0] = PosAct;
                PosAct.first-=1;
                cout <<"PosActfirst1: "<<PosAct.first<<" PosActsecond1: "<<PosAct.second<<endl;
                //cout <<"Posfirst1: "<<pos.first<<" Possecond1: "<<pos.second<<endl;

            }else if(c.porta_oberta(paret("est")) and (pos[0].first != aux.first || pos[0].second != aux.second+1)){
                L.push_back(PosAct);
                pos[0] = PosAct;
                PosAct.second += 1;
                cout <<"Posfirst2: "<<PosAct.first<<" PosActsecond2: "<<PosAct.second<<endl;
                 //cout <<"Posfirst2: "<<pos.first<<" Possecond2: "<<pos.second<<endl;

            }else if(c.porta_oberta(paret("sud")) and (pos[0].first != aux.first+1 || pos[0].second != aux.second)){
                  L.push_back(PosAct);
                  pos[0] = PosAct;
                  PosAct.first += 1;
                  cout <<"Posfirst3: "<<PosAct.first<<" PosActsecond3: "<<PosAct.second<<endl;
                   //cout <<"Posfirst3: "<<pos.first<<" Possecond3: "<<pos.second<<endl;
            }else if(c.porta_oberta(paret("oest")) and (pos[0].first != aux.first || pos[0].second != aux.second-1)){

              L.push_back(PosAct);
              pos[0] = PosAct;
              PosAct.second -= 1;
              cout <<"Posfirst4: "<<PosAct.first<<" PosActsecond4: "<<PosAct.second<<endl;
               //cout <<"Posfirst4: "<<pos.first<<" Possecond4: "<<pos.second<<endl;

        }else{
          throw error(SenseSolucio);
        }
        pos[1]=PosAct;
      }
    L.push_back(final);
  }


}
