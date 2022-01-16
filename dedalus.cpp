#include "dedalus.hpp"

/** CLASSE DEDALUS **/
/*
    Aquest mòdul té com a objectiu definir el namespace dedalus el qual conté la funció
    construir. Aquesta funció cal que tingui la capacitat de generar laberints del sistema
    MAZE. Aquesta funcionalitat es desenvolupa a partir del laberint que rep per paràmetre i
    excava fins adquir un laberint que sigui perfecte. Considerem laberint perfecte tot aquell
    que no tingui àrees inaccessibles com cambres tancades ni tampoc es formin cicles.

*/


util::Random R;

/* COST: */
int generaparetRandom(bool exterior, posicio prand, laberint & M){
  /*PRE: Ens passen un booleà exterior inicialitzat a true, una posició random i el laberint M que ens passen
  a la funció construir */
  /*POST: Retorna un integer corresponent a una paret random generada i que no pertany a l'exterior del
  laberint*/
  int rparet = R(0, 3);
  int p = rparet;
  while(exterior){
    /*INV: Mentre exterior no sigui false continua generant parets randoms*/
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

/*COST: */
posicio generaposicioRandom(laberint & M){
  /*PRE: Ens passen el laberint M que ens ve donat a la funció construir */
  /*POST: Retorna una posició random entre 1 i el número de files i número de
  columnes respectivament*/
  nat rfila = R(1,M.num_files());
  nat rcol =  R(1,M.num_columnes());
  posicio posi(rfila, rcol);
  return posi;
}

/*COST: O(1) ja que només es realitzen if's i assignacions*/
posicio generaAdjacent(posicio prand, int pared){
  /*PRE: Ens passen una posició random que hem generat prèviament i una paret
  random pertanyent a la cambra que hi ha en la posició prand*/
  /*POST: Retorna una posició equivalent a l'adjacent de prand i que comparteixin
  la paret pasada per paràmetre*/
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
/*COST: */
void dedalus::construir(laberint & M) throw(error){

    nat tamanyL = M.num_files() * M.num_columnes();
    particio<posicio> conjunt(tamanyL); //partició de posicions amb size del total de cambres

    for(nat i = 1; i <= M.num_files(); i++ ){
        for(nat j = 1; j <= M.num_columnes(); j++ ){
            posicio cambr(i, j);
            cambra c = M(cambr);
            if(c.porta_oberta(paret("nord")) || c.porta_oberta(paret("sud")) ||
            c.porta_oberta(paret("est")) || c.porta_oberta(paret("oest"))) {
                throw error(EstaExcavat);
            }
            conjunt.afegir(cambr);    //afegim posicions de cambres diferents
        }
    }

    //Inicialitzacions
    //Cambra al atzar:
    posicio prand = generaposicioRandom(M);
    cambra C = M(prand); ////cambra a l'atzar inicial
    int pared = generaparetRandom(true, prand, M); //Paret inicial
    posicio paux = generaAdjacent(prand, pared); //Posicio adjacent inicial

    while(conjunt.size() != 1){    //mentres no estigui tot a 1 sol conjunt de la particio
        if(!conjunt.mateix_grup(prand,paux)){
            if(!C.porta_oberta(pared)){
                 M.obre_porta(pared,prand);
                 //Donada la cambra que tenim (amb obre porta  tamb obrim el seu adjacent) i una vegada tenim un cami fem union
                 conjunt.unir(prand,paux); //unim AVL
            }
            cambra cnew = M(prand); ////cambra a l'atzar
            C=cnew;
        }

        prand = generaposicioRandom(M);
        pared = generaparetRandom(true, prand, M); //Paret nova
        paux = generaAdjacent(prand, pared); //Posicio adjacent nova

    }

}
