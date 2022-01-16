#include "teseus.hpp"

/** CLASSE TESEUS **/
/*
    Aquest mòdul té com a objectiu definir el namespace teseus que conté la funció buscar,
    la qual té la capacitat de resoldre laberints del sistema MAZE. La funcionalitat del mètode
    buscar és trobar el camí més curt, és a dir, el que passa per un nombre menor de cambres a partir
    d'un laberint donat, una posició d'una cambra inicial i una posició d'una cambra final. En el cas que hi hagi més d'un camí possible amb la mateixa mida retornen qualsevol dels camins.

    Per a la implementació del mòdul hem fet servir l'estructura de l'algoritme BFS actualitzat amb Dijkstra, explicada
    posteriorment al POST del mètode buscar. Hem decidit utilitzar aquest mètode, ja que és el més
    eficient donat que no tenim pesos a l'hora de recórrer el laberint.

*/

/* COST: O(1) El pitjor dels casos és cost constant, ja que només es té en compte el cost de la crida
a la funció porta_oberta a la classe cambra*/
void createAdjList(const laberint & M,std::list<posicio>&adjList,posicio u){
        /*PRE: Ens passen per paràmetre el laberint M, la llista d'adjacencia i la posició de la cambra que és vol inserir a la llista*/
        /*POST: Inserim a la llista la posició de la cambra adjacent de la passada per paràmetre, ja que aquesta llista reflexa
        les connexions de cambres que té el laberint*/

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

/* COST: Determinem que el cost total seria O(M.num_files()*M.num_columnes()), perquè en el pitjor dels casos sempre farem
el recorregut dels dos fors que tenim al principi, al contrari que el while que ve a continuació que es pot donar el cas que
adjList només contingui 1 únic element i, per tant, el seu cost es veuria reduït, ja que no recorreria la llista d'adjacència, per
tant, només es faria el while.*/
void teseus::buscar(const laberint & M,const posicio & inici, const posicio & final,std::list<posicio> & L) throw(error){
    /*PRE: Ens passen per paràmetre el laberint M, la posició de la cambra inicial del camí, el final del camí i finalment
    la llista de posicions buida del camí més curt*/
    /*POST: Fent ús de l'algoritme BFS, al final s'omple la llista L amb el camí més curt. El seu funcionament és el següent:
    1. Mirem si les posicions passades per paràmetre existeixen al laberint.
    2. En cas que si existeixen, inicialitzem 3 matrius d'arrays, una de les posicions de predecessors per a cada vegada que ens
    movem pel laberint, un altre de les distàncies que hi ha des de l'inici fins a cada cambra que recorrem i finalment una matriu
    de booleans per tenir rastreig de per on hem passat. El primer inicialitza a 0 totes les posicions, el segon a infinit i l'últim
    a false.
    3. Fem el primer cas per a la posició inicial i d'aquí ja comença el bucle que en resum el que fa és utilitzar una cua ( que en
    realitat és una llista) on el seu funcionament actua com una cua de prioritat. Aquesta llista es va omplint tenint en compte
    si hem visitat o no la posició de la cambra actual. També mentre fem això n'hem actualitzant les matrius. Aquest recorregut
    finalitzarà quan ja hàgim visitat l'última cambra del camí, és a dir, la posició final passada per paràmetre.
    4. Per acabar posem les posicions que tenim a la matriu de predecessors a la llista L de forma que el primer element posat és
    l'últim en treure per pantalla.
    5. Hi ha dos casos d'error, si no existeix les posicions passades per paràmetre o si no té solució, aquest últim se sabrà
    si la llista L no ha estat omplerta doncs mai s'ha trobat la posició final */

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
        /* COST: O(M.num_files()*M.num_columnes()) perquè en el cas pitjor fem tot el recorregut fins a arribar
        a M.num_files() i M.num_columnes()*/
        for(nat i = 0; i < M.num_files(); i++ ){
            for(nat j = 0; j < M.num_columnes(); j++ ){
                /*INV: Mentre que la i i la j siguin inferiors a M.num_files() i M.num_columnes()
                respectivament, anem inicialitzant cadascuna de les posicions de visited, dist i pred*/
                visited[i][j] = false;
                dist[i][j]= 9999;
                pred[i][j]= posEmpty;

            }
        }

        visited[inici.first-1][inici.second-1] = true; //primer element el inicial visitat el posem a true
        dist[inici.first-1][inici.second-1]=0; //primer element el inicial visitat distancia 0
        pred[inici.first-1][inici.second-1]=inici;
        Q.push_back(inici);

        /* COST: O(Q.size()*adjList.size()) ja que en el pitjor dels casos es fa el recorregut de tota la llista Q i
        de tota la llista adjList sense haver-hi trobat un final*/
        while(!Q.empty() and not trobat){
            /*INV: Mentre que la llista Q no es trobi buida i no s'hagi trobat la posició final dins de la llista d'adjacència,
            fem un recorregut de la llista adjList que generem.*/
            posicio u = Q.front();
            Q.pop_front();
            //LLista d'adjacència
            std::list<posicio>adjList;
            createAdjList(M,adjList,u);

            /* COST: O(adjList.size()) ja que en el cas pitjor recorrem tota la llista adjList*/
            for (std::list<posicio>::iterator v = adjList.begin(); v != adjList.end() and not trobat; v++) {
                /*INV: Mentre que l'iterador v no correspongui al final de la llista adjList i no s'hagi trobat la posició
                final dins de la llista adjList el que fem és mirar si he visitat aquella posició. En el cas que no s'hagi visitat
                actualitzem la informació de les matrius i introduïm a Q la posició visitada.*/
                posicio V = *v;
                if (visited[V.first-1][V.second-1] == false) {

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
                /* COST: O((M.num_files()*M.num_columnes())-1) El pitjor dels casos és el recorregut de tota la matriu
                d'array del predecessor menys l'element inicial*/
                while(pred[crawl.first-1][crawl.second-1]!=inici){
                    /*INV: Mentre que la matriu de predecessors sigui diferent de la posició inicial, és va
                    posant davant la posició actual del predecessor. Aquesta posició del predecessor que
                    estem mirant es va actualitzant per així mirar tots els elements.*/
                    L.push_front(pred[crawl.first-1][crawl.second-1]);
                    crawl = pred[crawl.first-1][crawl.second-1];
                }
                L.push_front(inici);
            }
        }
        if(L.empty()) throw error(SenseSolucio);
     }

}
