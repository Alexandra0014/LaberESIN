#include "dedalus.hpp"

// Excava el laberint, fent un laberint perfecte. Un laberint està excavat
// si i només si alguna de les seves cambres té alguna porta oberta.
// Es produeix un error si el laberint ja està excavat.
util::Random R;

int generaparetRandom(bool exterior, posicio prand, laberint & M){
  int rparet = R(0, 3);
  int p = rparet;
  while(exterior){
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

posicio generaposicioRandom(laberint & M){
  nat rfila = R(1,M.num_files());
  nat rcol =  R(1,M.num_columnes());
  posicio posi(rfila, rcol);
  return posi;
}

posicio generaAdjacent(posicio prand, int pared){
  posicio paux = prand;
  if(pared == 0) paux.first = prand.first-1; //NORD
  else if( pared == 1) paux.second = prand.second+1; //EST
  else if(pared == 2 ) paux.first = prand.first+1;//SUD
  else if (pared == 3) paux.second = prand.second-1; //OEST
  return paux;
}


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
