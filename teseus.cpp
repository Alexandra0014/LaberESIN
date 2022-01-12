#include "teseus.hpp"
#include <iostream>
using namespace std;

//LLista d'adjacència
std::list<posicio>*adjList;


void createAdjList(const laberint & M){
    posicio Pos(M.posi.first, M.posi.second);
    adjList = new std::list<posicio> *[M.posi.first];
    for(nat i = 0; i< M.posi.first; i++){
            adjList[i] = new std::list<posicio>[M.posi.second];
    }

}
void teseus::buscar(const laberint & M,const posicio & inici, const posicio & final,std::list<posicio> & L) throw(error){
    nat tamanyL = M.num_files() * M.num_columnes();
    int prev[(int)tamanyL];
    int d[(int)tamanyL];
    int distance = -1;
    for(nat i = 0; i<tamanyL; i++){
        d[i]= 9999; //inf
        p[i]= -1;
    }
    d[inici]=0;
    std::list<bool> S(tamanyL,false);
    std::list<posicio> Q;
    for(nat i = 1; i <= inici; i++){
      for(nat j = 1; j <= final; j++){
        posicio pos(i, j);
        Q.push_back(pos); //afegim cada node a la queue
      }
    }
    while(!Q.empty()){
        nat u = Q.top().second;
        Q.pop();

        if(!S[u]){
            S[u] = true;
            if(u == final){
                distance = d[u];
                return;
            }
            int m =
        }
    }

}
