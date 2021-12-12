#include "teseus.hpp"
void teseus::buscar(const laberint & M,
            const posicio & inici, const posicio & final,
            std::list<posicio> & L) throw(error){

              nat Ffila = final.first;
              nat Fcol = final.second;
              posicio PosAct;
              nat i = inici.first-1;
              nat j = inici.second-1;

              if( inici == final) L.push_back(inici);
              else if (inici.first <= 0 || inici.first > M.num_files() || inici.second <= 0 || inici.second > M.num_columnes()
                    || Ffila <= 0 || Ffila > M.num_files() && Fcol <= 0 || Fcol > M.num_columnes() ){
                      throw error(IniciFinalNoValid);
              }else{
                cambra c = M(inici);
                while(i < Ffila){
                  while( j < Fcol){
                      //PosAct.first = i;
                      //PosAct.second = j;
                      c = M(PosAct);
                      if(!c.porta_oberta(paret("nord")) || !c.porta_oberta(paret("est"))
                        || !c.porta_oberta(paret("sud")) || !c.porta_oberta(paret("oest")) ){
                          throw error(SenseSolucio);
                      }else if(c.porta_oberta(paret("nord"))){
                          L.push_back(PosAct);
                          PosAct.first = i-1;
                      }else if(c.porta_oberta(paret("est"))){
                          L.push_back(PosAct);
                          PosAct.second = j+1;
                      }else if(c.porta_oberta(paret("sud"))){
                          L.push_back(PosAct);
                          PosAct.first = i+1;
                      }else if(c.porta_oberta(paret("oest"))){
                        L.push_back(PosAct);
                        PosAct.second = j-1;
                      }
                  }
                }
              }
              std::list< posicio >::iterator it;
              for(it = L.begin(); it != L.end(); ++it){
                std::cout <<"[("<< (*it).first<<','<<(*it).second <<")]";
              }
              std::cout <<'\n';

}
