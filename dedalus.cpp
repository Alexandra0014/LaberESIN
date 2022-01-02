#include "dedalus.hpp"
// Excava el laberint, fent un laberint perfecte. Un laberint està excavat
// si i només si alguna de les seves cambres té alguna porta oberta.
// Es produeix un error si el laberint ja està excavat.

void dedalus::construir(laberint & M) throw(error){
    //1. Cal crear tants conjunts com cambres hi ha, i a cada conjunt hi haurà una cambra diferent.
    nat tamanyL = M.num_files() * M.num_columnes();
    particio<posicio> conjunt(tamanyL); //partició de posicions amb size del total de cambres
    for(nat i = 1; i <= M.num_files(); i++ ){
        for(nat j = 1; j <= M.num_columnes(); j++ ){
            posicio pos(i, j);
            conjunt.afegir(pos);    //afegim posicions de cambres diferents
        }
    }
    /*2. Sel·leccionar una cambra a l’atzar que anomenarem C, i una de les parets d’aquesta
    cambra a l’atzar, sempre i quan aquesta paret no tingui ja una porta oberta i no
    sigui una paret que doni a l’exterior.*/

    //Cambra al atzar:
    Random Rc;
    nat rfila = Rc(1,M.num_files());
    nat rcol =  Rc(1,M.num_columnes());
    posicio prand(rfila,rcol); //pos a l'atzar
    cambra C = M(prand); ////cambra a l'atzar

    //Paret al atzar:
    Random Rp;
    int rparet = Rp(0, 3);
    paret p = rparet;

    //Caso: Mirar si estem a un exterior
    bool exterior = false;
    if(prand.first == 1 && C.p == 0) exterior = true;
    else if(prand.first == M.num_files() && C.p == 2) exterior = true;
    else if(prand.second == 1 && C.p == 3) exterior = true;
    else if(prand.second == M.num_columnes() && C.p == 1) exterior = true;

    //Mentres que sigui un borde o tingui la porta oberta --> fer randoms de paret
    while(exterior || C.porta_oberta(p)){
      int rparet = Rp(0, 3);
      paret p = rparet;
    }

    /*3. Anomenem C' a la cambra adjacent a C que estan separades per la paret que hem
    triat. Si les dues cambres C i C' no estan comunicades (pertanyen a 2 conjunts diferents),
    llavors cal comunicar-les. Hem de crear una porta a la paret triada i unir els 2 conjunts.*/





}
