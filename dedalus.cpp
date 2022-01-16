#include "dedalus.hpp"

/** CLASSE DEDALUS **/
/*
    Aquest mòdul té com a objectiu definir el namespace dedalus el qual conté la funció
    construir. Aquesta funció cal que tingui la capacitat de generar laberints del sistema
    MAZE. Aquesta funcionalitat es desenvolupa a partir del laberint que rep per paràmetre i
    excava fins a adquirir un laberint que sigui perfecte. Considerem laberint perfecte tot aquell
    que no tingui àrees inaccessibles com cambres tancades ni tampoc es formin cicles.

    Per a la realització del mòdul s'ha fet ús d'un atribut global d'un random. Aquest atribut
    és necessari per a l'excavació del laberint per escollir posicions i per a l'elecció
    de la paret a excavar.

    IMPORTANT!: Per motius de la randomització de les posicions de la cambra i de les parets,
    els costos d'aquesta classe es fan des de la perspectiva mínima, és a dir, Ω. Aquesta
    decisió ve donada, ja que en ser un random el cost O tendeix a infinit, i el cost mitjà
    és difícil de calcular.

*/



util::Random R; 

/* COST: Ω(1) ja que en el millor dels casos únicament generarà una paret random i només entrarà un cop al while,
en el qual saltarà directament al else, ja que no correspon aquesta paret a una exterior*/
int generaparetRandom(bool exterior, posicio prand, laberint & M){
  /*PRE: Ens passen un booleà exterior inicialitzat a true, una posició random i el laberint M que ens passen
  a la funció construir. */
  /*POST: Retorna un integer corresponent a una paret random generada i que no pertany a l'exterior del
  laberint*/
  int rparet = R(0, 3);
  int p = rparet;
  while(exterior){
    /*INV: Mentre exterior no sigui false contínua generant parets randoms*/
    if((prand.first == 1 && p == 0 )|| (prand.first == M.num_files() && p == 2)
    || (prand.second == 1 && p == 3 ) || (prand.second == M.num_columnes() && p == 1)){
     rparet = R(0, 3);
     p = rparet;
    }
    else {
    exterior = false;
    }
  }
    return p;
}

/*COST: Ω(1) ja que en el millor dels casos només retorna una posició random que es genera
amb dos nats random*/
posicio generaposicioRandom(laberint & M){
  /*PRE: Ens passen el laberint M que ens ve donat a la funció construir */
  /*POST: Retorna una posició random entre 1 i el número de files i número de
  columnes respectivament*/
  nat rfila = R(1,M.num_files());
  nat rcol =  R(1,M.num_columnes());
  posicio posi(rfila, rcol);
  return posi;
}

/*COST: Ω(1) ja que només es realitzen if's i assignacions*/
posicio generaAdjacent(posicio prand, int pared){
  /*PRE: Ens passen una posició random que hem generat prèviament i una paret
  random pertanyent a la cambra que hi ha en la posició prand*/
  /*POST: Retorna una posició equivalent a l'adjacent de prand i que comparteixin
  la paret passada per paràmetre*/
  posicio paux = prand;
  if(pared == 0) paux.first = prand.first-1; //NORD
  else if( pared == 1) paux.second = prand.second+1; //EST
  else if(pared == 2 ) paux.first = prand.first+1;//SUD
  else if (pared == 3) paux.second = prand.second-1; //OEST
  return paux;
}

// Excava el laberint, fent un laberint perfecte. Un laberint està excavat
// si i només si alguna de les seves cambres té alguna porta oberta.
// Es produeix un error si el laberint ja està excavat.

/*COST: En el millor dels casos per motiu dels randoms ens quedem amb el cost mínim dels bucles que tenim,
és a dir, ens quedem amb el cost del while que és Ω(M.num_files()*M.num_columnes()) o cosa que és el mateix que dir
Ω(n^2)*/
void dedalus::construir(laberint & M) throw(error){
     /*PRE: Ens passen per paràmetre un laberint M*/
     /*POST: El laberint passat per paràmetre, en cas que inicialment no hagi estat excavat, s'excava.
     Es para d'excavar una vegada s'hagi format un laberint perfecte.*/

    nat tamanyL = M.num_files() * M.num_columnes();
    particio<posicio> conjunt(tamanyL); //partició de posicions amb size del total de cambres

    /*COST: Ω(num_files()*num_columnes())*Ω(log(n)) és a dir Ω(n^2)*Ω(log(n)) ja que recorre tot el laberint i va afegint
    les posicions a la partició */
    for(nat i = 1; i <= M.num_files(); i++ ){
        for(nat j = 1; j <= M.num_columnes(); j++ ){
          /*INV: Mentre la i i la j siguin inferior a M.num_files() i M.num_columnes() respectivament,
          anem afegint posicions a la partició prèviament creada anomenada conjunt.*/
            posicio cambr(i, j);
            cambra c = M(cambr);
            if(c.porta_oberta(paret("nord")) || c.porta_oberta(paret("sud")) ||
            c.porta_oberta(paret("est")) || c.porta_oberta(paret("oest"))) {
                throw error(EstaExcavat);
            }
            conjunt.afegir(cambr);
        }
    }

    //Inicialitzacions
    //Cambra a l'atzar:
    posicio prand = generaposicioRandom(M);
    cambra C = M(prand); //cambra a l'atzar inicial
    int pared = generaparetRandom(true, prand, M); //Paret inicial
    posicio paux = generaAdjacent(prand, pared); //Posicio adjacent inicial

    /*COST: Pel motiu dels randoms en aquest cas el seu cost seria mínim, és a dir, Ω(1). Tenint en compte això,
    el cost del while en el millor dels casos seria Ω(M.num_files()*M.num_columnes()) que equivaldria a Ω(n^2), ja que
    la funció obre_porta, si entra una vegada, si o si recorre tot el laberint. Per tant, el cost total d'aquest while
    és Ω(n^2)*Ω(1) per tant Ω(n^2). No hi ha forma d'evitar passar per la funció de obre_porta, ja que el while no para
    fins que tot estigui en el mateix grup.*/
    while(conjunt.size() != 1){
        /*INV: Mentre que la partició de posicions no estigui tota unida, és a dir, que el size de la partició
        sigui igual a 1, anem mirant si les posicions generades estan dins del mateix grup. En cas que no ho estiguin
        es mira si està la porta oberta i en cas de porta tancada s'obre i s'uneix a la partició. Seguidament amb aquesta
        posició s'actualitza la cambra i finalment es generen noves posicions i parets. Si ja pertanyen al mateix grup, per exemple
        si es dóna el cas de ser parets adjacents, es creen directament noves posicions. */
        if(!conjunt.mateix_grup(prand,paux)){
            if(!C.porta_oberta(pared)){
                 M.obre_porta(pared,prand);

                 conjunt.unir(prand,paux);
            }
            cambra cnew = M(prand);
            C=cnew;
        }

        prand = generaposicioRandom(M);
        pared = generaparetRandom(true, prand, M);
        paux = generaAdjacent(prand, pared);

    }

}
