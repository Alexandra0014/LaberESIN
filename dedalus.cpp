#include "dedalus.hpp"
#include <iostream>
using namespace std;
// Excava el laberint, fent un laberint perfecte. Un laberint està excavat
// si i només si alguna de les seves cambres té alguna porta oberta.
// Es produeix un error si el laberint ja està excavat.
int generaparetRandom(bool exterior, posicio prand, laberint & M){
  util::Random Rp;
  int rparet = Rp(0, 3);
  int p = rparet;
  while(exterior){
    if((prand.first == 1 && p == 0 )|| (prand.first == M.num_files() && p == 2)
    || (prand.second == 1 && p == 3 ) || (prand.second == M.num_columnes() && p == 1)){
     rparet = Rp(0, 3);
     p = rparet;
    }
    else {
    exterior = false;
    }
  }
    return p;
}

posicio generaposicioRandom(laberint & M){
  util::Random Rc;
  nat rfila = Rc(1,M.num_files());
  nat rcol =  Rc(1,M.num_columnes());
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
bool mirarCambra(int pos, util::vector<int> llistacambres){
    bool trobat = false;
    for(unsigned int i=0; i < llistacambres.size(); i++){  //mirar si en el vector de cambres ya hemos mirado esa cambra
        if(llistacambres[i] == pos) trobat = true;
    }
    return trobat;
}

int combinacionumeros(int i, int j) {
   int cont = 1;
   while (cont <= j)
      cont *= 10;
   return i*cont + j;
}

void dedalus::construir(laberint & M) throw(error){

    nat tamanyL = M.num_files() * M.num_columnes();
    particio<nat> conjunt(tamanyL); //partició de posicions amb size del total de cambres

    for(nat i = 1; i <= M.num_files(); i++ ){
        for(nat j = 1; j <= M.num_columnes(); j++ ){
            posicio cambr(i, j);
            cambra c = M(cambr);
            int combi = combinacionumeros(i, j);
            if(c.porta_oberta(paret("nord")) || c.porta_oberta(paret("sud")) ||
            c.porta_oberta(paret("est")) || c.porta_oberta(paret("oest"))) {
                throw error(EstaExcavat);
            }
            conjunt.afegir(combi);    //afegim posicions de cambres diferents
        }
    }

    //Inicialitzacions
    //Cambra al atzar:
    posicio prand = generaposicioRandom(M);
    int prandi = combinacionumeros(prand.first, prand.second);
    cambra C = M(prand); ////cambra a l'atzar inicial
    int pared = generaparetRandom(true, prand, M); //Paret inicial
    posicio paux = generaAdjacent(prand, pared); //Posicio adjacent inicial
    int pauxi = combinacionumeros(paux.first, paux.second);
    util::vector<int> llistacambres;
    bool para = false;

    while( tamanyL!=llistacambres.size() || !conjunt.mateix_grup(prandi,pauxi)){    //Mientras no esten en ele mismo conj i no haya mirado todas las cambras
        cout<<"prandi: "<<prandi<<endl;
        cout<<"pared: "<<pared<<endl;
        bool bucle = false;
        //Fer obrir porta passant la pared i el prand --> te abre camino a dos cambres adjacents

        if(!C.porta_oberta(pared)){
             M.obre_porta(pared,prand);
             //Donada la cambra que tenim (amb obre porta  tamb obrim el seu adjacent) i una vegada tenim un camino
             // fem union
             conjunt.unir(prandi,pauxi); //unim AVL
             //Canvies de prand i paux
        }else{
            if(!mirarCambra(prandi,llistacambres)) llistacambres.push_back(prandi);
        }

        while((mirarCambra(prandi,llistacambres) && conjunt.mateix_grup(prandi,pauxi) && !para)){ //si ja esta al vector --> ja l'hem fet
            bucle = true;
            if(tamanyL == llistacambres.size()) para = true;
            prand = generaposicioRandom(M);
            prandi = combinacionumeros(prand.first, prand.second);
            pared = generaparetRandom(true, prand, M); //Paret
            paux = generaAdjacent(prand, pared); //Posicio adjacent
            pauxi = combinacionumeros(paux.first, paux.second);

        }
        cambra cnew = M(prand); ////cambra a l'atzar
        C=cnew;
        if(!bucle){
            prand = generaposicioRandom(M);
            prandi = combinacionumeros(prand.first, prand.second);
            pared = generaparetRandom(true, prand, M); //Paret
            paux = generaAdjacent(prand, pared); //Posicio adjacent
            pauxi = combinacionumeros(paux.first, paux.second);
        }
        cout<<"prandi333: "<<prandi<<endl;

    }
    for(unsigned int i = 0; i < llistacambres.size(); i++){
        cout<<llistacambres[i]<<" ";
    }
    cout<<endl;

}
