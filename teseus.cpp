#include "teseus.hpp"
#include <iostream>
using namespace std;

void createAdjList(const laberint & M,std::list<posicio>&adjList,posicio u){ //creem una llista amb les connexions de les cambres
        cambra c = M(u);

        if(c.porta_oberta(paret("nord"))) {
          posicio aux = u;
          aux.first = u.first-1;
          adjList.push_back(aux);
        }
        if(c.porta_oberta(paret("est"))) {
          posicio aux = u;
          aux.second = u.second+1;
          adjList.push_back(aux);
        }
        if(c.porta_oberta(paret("sud"))) {
          posicio aux = u;
          aux.first = u.first+1;
          adjList.push_back(aux);
        }
        if(c.porta_oberta(paret("oest"))) {
          posicio aux = u;
          aux.second = u.second-1;
          adjList.push_back(aux);
        }

}

void teseus::buscar(const laberint & M,const posicio & inici, const posicio & final,std::list<posicio> & L) throw(error){
nat Ffila = final.first;
nat Fcol = final.second;

cout<<"aaaaaa?"<<endl;

if (inici.first <= 0 || inici.first > M.num_files() || inici.second <= 0 || inici.second > M.num_columnes()
                      || Ffila <= 0 || Ffila > M.num_files() || Fcol <= 0 || Fcol > M.num_columnes() ){
                        throw error(IniciFinalNoValid);
}else{
    posicio pred[M.num_files()][M.num_columnes()];
    nat dist[M.num_files()][M.num_columnes()];
    std::list<posicio> Q;
    bool visited[M.num_files()][M.num_columnes()];
    bool trobat = false;
    posicio posEmpty;
    posEmpty.first = 0;
    posEmpty.second = 0;
    for(nat i = 1; i <= M.num_files(); i++ ){
        for(nat j = 1; j <= M.num_columnes(); j++ ){
        visited[i][j] = false;
        dist[i][j]= 9999; //inf
        pred[i][j]= posEmpty;
        }
    }

    visited[inici.first][inici.second] = true; //primer element el inicial visitat aka = true
    dist[inici.first][inici.second]=0; //primer element el inicial visitat distancia 0, si mateix
    pred[inici.first][inici.second]=inici;
    Q.push_back(inici);

    while(!Q.empty()){
        posicio u = Q.front();
        Q.pop_front();
        //LLista d'adjacència
        std::list<posicio>adjList;
        createAdjList(M,adjList,u);
        //QUE HAY EN adjList
        /*cout << "adjList contains:";
        for (std::list<posicio>::iterator v = adjList.begin(); v != adjList.end(); v++){
           posicio V = *v;
           cout << ' ' << V.first<< ' ' <<V.second;
        }*/
         //cout <<endl;

        for (std::list<posicio>::iterator v = adjList.begin(); v != adjList.end(); v++) {
            posicio V = *v;
            //cout<<"aaaaaa?"<<endl;
            if (visited[V.first][V.second] == false) {
                //al sumatorio de distancias se le añade el nuevo vertice actual+ahora el predecesor será este vertice visitado+ actualiza cola vertice adj
                visited[V.first][V.second] = true;
                dist[V.first][V.second] = dist[u.first][u.second] + 1;
                pred[V.first][V.second] = u;
                Q.push_back(V);
                if(V == final){
                    //cout<<"aaaaaa?"<<endl;
                    trobat = true;
                }
            }
        }

    }

    if(inici == final)L.push_front(inici);
    else{
        if(trobat){
            posicio crawl = final;
            L.push_front(crawl);
            while(pred[crawl.first][crawl.second]!=inici){
               // cout<<"entro?"<<endl;
                L.push_front(pred[crawl.first][crawl.second]);
                crawl = pred[crawl.first][crawl.second];
            }
            L.push_front(inici);
        }else{
            throw error(SenseSolucio);
        }
    }

 }



}
