#include "dedalus.hpp"
#include <iostream>
using namespace std;
// Excava el laberint, fent un laberint perfecte. Un laberint està excavat
// si i només si alguna de les seves cambres té alguna porta oberta.
// Es produeix un error si el laberint ja està excavat.
int generaparetRandom(bool exterior, cambra C, posicio prand, laberint & M){
  util::Random Rp;
  int rparet = Rp(0, 3);
  int p = rparet;
  while(exterior && C.porta_oberta(p)){
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
  if(pared == 0) paux.first = prand.first+1; //NORD
  else if( pared == 1) paux.second = prand.second+1; //EST
  else if(pared == 2 ) paux.first = prand.first-1;//SUD
  else if (pared == 3) paux.second = prand.second-1; //OEST
  return paux;
}
bool mirarCambra(cambra c, util::vector<cambra> llistacambres){
    bool trobat = false;
    for(unsigned int i=0; i < llistacambres.size(); i++){  //mirar si en el vector de cambres ya hemos mirado esa cambra
        if(llistacambres[i] == c) trobat = true;
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
    //1. Cal crear tants conjunts com cambres hi ha, i a cada conjunt hi haurà una cambra diferent.
    /*2. Sel·leccionar una cambra a l’atzar que anomenarem C, i una de les parets d’aquesta
    cambra a l’atzar, sempre i quan aquesta paret no tingui ja una porta oberta i no
    sigui una paret que doni a l’exterior.*/
    /*3. Anomenem C' a la cambra adjacent a C que estan separades per la paret que hem
    triat. Si les dues cambres C i C' no estan comunicades (pertanyen a 2 conjunts diferents),
    llavors cal comunicar-les. Hem de crear una porta a la paret triada i unir els 2 conjunts.*/
    /*4. En cas contrari, no fem res perquè ja existeix un camí per arribar d’una cambra a
    l’altra.*/

    //cout<<"holu";
    nat tamanyL = M.num_files() * M.num_columnes();
    particio<nat> conjunt(tamanyL); //partició de posicions amb size del total de cambres
    for(nat i = 1; i <= M.num_files(); i++ ){
        for(nat j = 1; j <= M.num_columnes(); j++ ){
            int combi = combinacionumeros(i, j);
            conjunt.afegir(combi);    //afegim posicions de cambres diferents
            cout<<"combi"<<combi<<endl;
        }
    }
    
    //Inicialitzacions
    //Cambra al atzar:
    posicio prand = generaposicioRandom(M);
    int prandi = combinacionumeros(prand.first, prand.second);
    cout<<"prandi: "<<prandi<<endl;
    cambra C = M(prand); ////cambra a l'atzar inicial
    int pared = generaparetRandom(true, C, prand, M); //Paret inicial
    cout<<"pared: "<<pared<<endl;
    posicio paux = generaAdjacent(prand, pared); //Posicio adjacent inicial
    cout<<"paux: "<<paux.first<<" "<<paux.second<<endl;
    int pauxi = combinacionumeros(paux.first, paux.second);
    cout<<"pauxi: "<<pauxi<<endl;
    util::vector<cambra> llistacambres;

    while(!conjunt.mateix_grup(prandi,pauxi) && tamanyL!=llistacambres.size()){    //Mientras no esten en ele mismo conj i no haya mirado todas las cambras
        //cout<<"AAAAAAAAA"<<endl;
        //Fer obrir porta passant la pared i el prand --> te abre camino a dos cambres adjacents
        M.obre_porta(pared,prand);
        //Donada la cambra que tenim (amb obre porta  tamb obrim el seu adjacent) i una vegada tenim un camino
        // fem union
        conjunt.unir(prandi,pauxi); //unim AVL
        //Canvies de prand i paux
        llistacambres.push_back(C);
        prand = generaposicioRandom(M);
        prandi = combinacionumeros(prand.first, prand.second);
        cambra cnew = M(prand); ////cambra a l'atzar
        while(mirarCambra(cnew,llistacambres)){
            prand = generaposicioRandom(M);
            prandi = combinacionumeros(prand.first, prand.second);
            cnew = M(prand); ////cambra a l'atzar
        }
        C=cnew;
        pared = generaparetRandom(true, C, prand, M); //Paret
        paux = generaAdjacent(prand, pared); //Posicio adjacent
        pauxi = combinacionumeros(paux.first, paux.second);

    }
    //throw error(EstaExcavat);

}
