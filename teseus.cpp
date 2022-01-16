#include "teseus.hpp"

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
    for(nat i = 0; i < M.num_files(); i++ ){
        for(nat j = 0; j < M.num_columnes(); j++ ){
        visited[i][j] = false;
        dist[i][j]= 9999; //inf
        pred[i][j]= posEmpty;

        }
    }

    visited[inici.first-1][inici.second-1] = true; //primer element el inicial visitat aka = true
    dist[inici.first-1][inici.second-1]=0; //primer element el inicial visitat distancia 0, si mateix
    pred[inici.first-1][inici.second-1]=inici;
    Q.push_back(inici);

    while(!Q.empty() and not trobat){

        posicio u = Q.front();
        Q.pop_front();
        //LLista d'adjacència
        std::list<posicio>adjList;
        createAdjList(M,adjList,u);

        for (std::list<posicio>::iterator v = adjList.begin(); v != adjList.end() and not trobat; v++) {
            posicio V = *v;

            if (visited[V.first-1][V.second-1] == false) {
                //al sumatorio de distancias se le añade el nuevo vertice actual+ahora el predecesor será este vertice visitado+ actualiza cola vertice adj
                visited[V.first-1][V.second-1] = true;
                dist[V.first-1][V.second-1] = dist[u.first-1][u.second-1] + 1;
                pred[V.first-1][V.second-1] = u;
                Q.push_back(V);
                if(V == final){
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
            while(pred[crawl.first-1][crawl.second-1]!=inici){
                L.push_front(pred[crawl.first-1][crawl.second-1]);
                crawl = pred[crawl.first-1][crawl.second-1];
            }
            L.push_front(inici);
        }
    }
    if(L.empty()) throw error(SenseSolucio);
 }

}
