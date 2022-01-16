#include "laberint.hpp"
#include <iostream>

using namespace std;

// Constructora d'un laberint buit sense excavar (sense cap porta oberta)
// de la mida indicada. Totes les cambres del laberint no tenen cap porta.
// Es produeix un error si el número de files o de columnes del laberint és 0.

/* COST: O(posi.first) ja que, en els pitjors dels casos, entra al if i com a màxim arriba
fins al nombre de files indicat per paràmetre*/
laberint::laberint(nat num_fil, nat num_col) throw(error){
  /*PRE: Ens passen el nombre de files i columnes respectivament*/
  /*POST: Creació dinàmica d'un laberint segons les mides passades per paràmetre
  amb totes les portes tancades*/

  if (num_fil != 0 && num_col != 0)
  {
    posi.first = num_fil;
    posi.second = num_col;
    _c = new cambra *[posi.first];
    /* COST: O(posi.first) ja que com a màxim arriba fins al nombre de files indicat per paràmetre*/
    for(nat i = 0; i < posi.first; i++){
      /*INV: Mentre que la i sigui menor a posi.first, a la posició i de l'array _c,
      anem creant un array amb les columnes del laberint.*/
        _c[i] = new cambra [posi.second];
    }
  }
  else throw error(FilsColsIncorrecte);

}
// Constructora d'un laberint a partir d'un istream (canal d'entrada) is.
// El format de l'istream seguirà l'exposat a l'apartat 2.3. Es presuposa que
// el laberint és correcte.

/* COST: O(is*medida), ja que fem tantes iteracions com strings ens passin pel canal d'entrada i
dins farem tantes interacions fins a medida, és a dir, s.size()-1 la mida del string que ens passen per paràmetre menys 1  */
laberint::laberint(std::istream & is) throw(error){
  /*PRE: Ens passen pel canal d'entrada is la primera línea que correspon al nombre de files i columnes,
    després la representació d'un laberint */
  /*POST: Un laberint correctament construit a través del elements entrats per la variable is*/

  int fila = 0, columna = 0;
  is >> fila >> columna;
  posi.first=fila;
  posi.second=columna;

  string s;

  /*Aquest booleà indicarà si hem de tractar el cas d'obrir porta est-oest o nord-sud.*/
  bool trobat = true;

  /*Generem un laberint l auxiliar sense cap porta oberta i amb les mides indicades.
  Aquest laberint ens serveix perquè a continuació anirem obrint les portes que ens interessen, segons
  n'hi hagi un asterisc o un espai en blanc al laberint que ens entren per is*/
  laberint l = laberint(posi.first, posi.second);
  int contador = -1;

  /* COST: O(is*medida), ja que fem tantes iteracions com strings ens passin pel canal d'entrada i
  dins farem tantes interacions fins a medida, és a dir, s.size()-1 la mida del string que ens passen per paràmetre menys 1  */
  while(getline(is, s)){
  int medida = s.size()-1;
  if(trobat){
    /* COST: O(medida) ja que recorrerà com màxim fins a medida que equival a s.size()-1, és a dir la mida del string
    que ens passen per paràmetre menys 1 perquè l'ultima posició sempre serà un asterisc i al ser paret exterior
    no n'hi ha opció de que hagi cap porta oberta*/
  	for (int i = 0, fil = 0; i < medida; i+=2, fil++){
      /*INV: Mentre que la i sigui inferior a medida recorrem les posicions del string s que ens passen pel canal d'entrada.*/
  		if (s[i] != '*' ){
         /* Tractem el cas en que n'hi hagi un espai en blanc en l'string que ens passen.
         En aquest cas volem obrir porta i ho fem també per a la paret adjacent*/
  			 l._c[contador][fil-1].obre_porta(paret("est"));
  			 l._c[contador][fil].obre_porta(paret("oest"));
  		}
  	}
  	trobat = false;
  	contador++;
  }
  else{

    /* COST: O(medida) ja que recorrerà com màxim fins a medida que equival a s.size()-1, és a dir la mida del string
    que ens passen per paràmetre menys 1 perquè l'ultima posició sempre serà un asterisc i al ser paret exterior
    no n'hi ha opció de que hagi cap porta oberta*/
  	for (int i = 1, fil = 0; i < medida; i+=2, fil++){
      /*INV: Mentre que la i sigui inferior a medida recorrem les posicions del string s que ens passen pel canal d'entrada.*/
  		if (s[i] != '*' ){
  			 l._c[contador][fil].obre_porta(paret("nord"));
         l._c[contador-1][fil].obre_porta(paret("sud"));
  		}
  	}
  trobat = true;
  }
}

*this = l; //Copiem l'informació del laberint auxiliar l al nostre laberint.

}

// Constructora per còpia
/* COST: O(posi.first*posi.second) ja que recorrem totes les posicions del laberint l per
copiar-lo al nostre*/
laberint::laberint(const laberint & l) throw(error){
  /*PRE: Ens passen un laberint l*/
  /*POST:A nostra array cambra( o sigui nostre laberint) se li copien tots els elements
  del laberint passat per paràmetre*/

  posi.first = l.posi.first;
  posi.second = l.posi.second;
  _c = new cambra* [posi.first];
  /* COST: O(posi.first) ja que com a màxim arriba fins al nombre de files */
  for(nat i = 0; i < posi.first; i++){
      /*INV: Mentre que la i sigui menor a posi.first, a la posició i de l'array _c,
      anem creant un array amb les columnes del laberint.*/
    _c[i] = new cambra[posi.second];
  }
  /* COST: O(posi.first*posi.second) ja que recorrem totes les posicions del laberint l per
  copiar-lo al nostre*/
  for(nat i = 0; i < posi.first; i++){
      for(nat j = 0; j < posi.second; j++){
          /*INV: Mentre que la i, j sigui menor a posi.first i posi.second, a la posició [i][j] de l'array _c,
          anem copiant els elements [i][j] del laberint passat per paràmetre*/
        _c[i][j] = l._c[i][j];
      }
  }
}

//Assignació.
/* COST: O(posi.first*posi.second) ja que, en els pitjors dels casos, recorrem totes les posicions del laberint l per
assignar-lo al nostre */
laberint & laberint::operator=(const laberint & l) throw(error){
  /*PRE: Ens passen un laberint l*/
  /*POST: A nostra array cambra( o sigui el nostre laberint) li esborrem el contingut i li assignem tots els elements
  del laberint passat per paràmetre*/

 if(this != &l){
    if(posi.first != l.posi.first ||  posi.second != l.posi.second){
        /* COST: O(posi.first) ja que com a màxim arriba fins al nombre de files */
      for(nat i = 0; i < posi.first; i++){
          /*INV: Mentres que la i sigui menor a posi.first, anem esborrant l'array _c */
          delete[] _c[i];
      }
      delete[] _c;
    }
      posi.first = l.posi.first;
      posi.second = l.posi.second;
      _c = new cambra* [posi.first];
      /* COST: O(posi.first) ja que com a màxim arriba fins al nombre de files */
      for(nat i = 0; i < posi.first; i++){
          /*INV: Mentre que la i sigui menor a posi.first, a la posició i de l'array _c,
          anem creant un array amb les columnes del laberint*/
          _c[i] = new cambra[posi.second];
      }
      /* COST: O(posi.first*posi.second) ja que recorrem totes les posicions del laberint l per
      assignar-lo al nostre */
      for(nat i = 0; i < posi.first; i++){
          for(nat j = 0; j < posi.second; j++){
              /*INV: Mentre que la i, j sigui menor a posi.first i posi.second, a la posició [i][j] de l'array _c,
              anem assignant els elements [i][j] del laberint passat per paràmetre*/
            _c[i][j] = l._c[i][j];
          }
      }
  }
  return *this;
}

//Destructora.
 /* COST: O(posi.first) ja que com a màxim arriba fins al nombre de files */
laberint::~laberint() throw(){
  /*PRE:  Cert */
  /*POST: Nostra laberint, és a dir, el punter de cambres, és esborrat*/
  /* COST: O(posi.first) ja que com a màxim arriba fins al nombre de files */
  for(nat i = 0; i < posi.first; i++){
       /*INV: Mentre que la i sigui menor a posi.first, anem esborrant l'array _c */
      delete[] _c[i];
  }
  delete[] _c;
}

/* COST: O(1) Només és un return, per tant es cost constant*/
nat laberint::num_files() const throw(){
  /*PRE:  Cert */
  /*POST:Retorna el nombre de files del nostre laberint*/

  return posi.first;
}
/* COST: O(1) Només és un return, per tant es cost constant*/
nat laberint::num_columnes() const throw(){
    /*PRE: Cert */
    /*POST:Retorna el nombre de columnes del nostre laberint*/

  return posi.second;
}

// Retorna la cambra situada a la posició especificada per pos.
// Aquest mètode permet utilitzar el laberint d'aquesta manera:
//   laberint l(3,4);   --> Es crea un laberint de 3x4
//   posicio pos(2,2);  --> Posicion que accedemos dentro del laberinto que hemos creado previamente
//   cambra c = l(pos); --> Se nombra la cabmra en tal pos.
// Es produeix un error si la posició donada no existeix al laberint.

/* COST: O(posi.first*posi.second) ja que en el pitjor dels casos, si entrem al if, recorrem totes les posicions del laberint */
cambra laberint::operator()(const posicio & pos) const throw(error){
  /*PRE: Ens passen per paràmetre una posició especifica d'una cambra */
  /*POST: De la posició específica passada per paràmetre, retornem la cambra situada dins del laberint */

  int fila =  (int) pos.first-1;
  int col =  (int) pos.second-1;

  cambra res;
  if(fila >= 0 && fila < (int)posi.first && col >= 0 && col < (int)posi.second){
    /* COST: O(posi.first*posi.second) ja que recorrem totes les posicions del laberint */
    for(int i = 0; i < (int)posi.first; i++){
        for(int j = 0; j < (int)posi.second; j++){
            /*INV: Mentre que la i, j sigui menor a posi.first i posi.second, en el cas en què [i][j]
            coincideixi amb les posicions passades per paràmetre, assignar la cambra trobada en aquella posició a
            la variable resultat.*/
            if(_c[i][j] == _c[fila][col]){
              res = _c[fila][col];
            }
        }
    }
  }else{
    throw error(PosicioInexistent);
  }

 return res;
}

// Obre la porta en la paret donada de la cambra que està especificada per pos.
// També obre la porta corresponent en la cambra adjacent. Es produeix un error
// si la posició no existeix o no es pot obrir una porta en la direcció
// indicada perquè dóna a l'exterior.

/* COST: O(posi.first*posi.second) ja que, en el pitjor dels casos, si entra en el if, recorrem
totes les posicions del laberint */
void laberint::obre_porta(paret p, const posicio & pos) throw(error){
  /*PRE: Ens passen per paràmetre una direcció d'una paret d'una cambra donada a
  la posició especificada per paràmetre*/
  /*POST: Tant per a la cambra adjacent com a l'especificada per paràmetre, s'obre la porta corresponent.
  En cas que la posició no existeixi o la porta no es pugui obrir, salta un error*/

  int fila = (int)pos.first-1;
  int col = (int)pos.second-1;
  if(fila >= 0 && fila < (int)posi.first && col >= 0 && col < (int)posi.second){
    /* COST: O(posi.first*posi.second) ja que recorrem totes les posicions del laberint */
    for(int i = 0; i < (int)posi.first; i++){
        for(int j = 0; j < (int)posi.second; j++){
          /*INV: Mentre que la i, j sigui menor a posi.first i posi.second, anem mirant si les posicions donen a l'exterior.
            En cas que donin, salta un error, en cas contrari s'obre la porta de la cambra de la posició passada per paràmetre i
            la seva adjacent.*/

          //Exteriors
           if(fila == 0 && p == 0) throw error(PortaExterior);
           else if(fila == (int)posi.first-1 && p == 2) throw error(PortaExterior);
           else if(col == 0 && p == 3) throw error(PortaExterior);
           else if(col == (int)posi.second-1 && p == 1) throw error(PortaExterior);
           else {
             if( i == fila && j == col){
               _c[i][j].obre_porta(p);
               //parets adjacents
               if(p == 0) _c[i-1][j].obre_porta(p+2);
               else if( p == 1) _c[i][j+1].obre_porta(p+2);
               else if(p == 2) _c[i+1][j].obre_porta(p-2);
               else if (p == 3) _c[i][j-1].obre_porta(p-2);
             }
          }
        }
    }
  }else{
    throw error(PosicioInexistent);
  }

}

// Tanca la porta en la paret donada de la cambra que està especificada per pos.
// També tanca la porta corresponent en la cambra adjacent. Es produeix un error
// si la posició no existeix.

/* COST: O(posi.first*posi.second) ja que, en el pitjor dels casos, si entra en el if, recorrem
totes les posicions del laberint */
void laberint::tanca_porta(paret p, const posicio & pos) throw(error){
    /*PRE: Ens passen per paràmetre una direcció d'una paret d'una cambra donada a
    la posició especificada per paràmetre*/
    /*POST: Tant per a la cambra adjacent com a l'especificada per paràmetre, es tanca la porta corresponent.
    En cas que la posició no existeixi salta un error*/

  int fila = (int)pos.first-1;
  int col = (int)pos.second-1;
  if(fila >= 0 && fila < (int)posi.first && col >= 0 && col < (int)posi.second){
     /* COST: O(posi.first*posi.second) ja que recorrem totes les posicions del laberint */
    for(int i = 0; i < (int)posi.first; i++){
        for(int j = 0; j < (int)posi.second; j++){
            /*INV: Mentre que la i, j sigui menor a posi.first i posi.second, anem mirant si les posicions coincideix amb la
            donada per paràmetre. En cas que coincideixi, tanca la porta especificada a la paret donada per paràmetre.
            */
            if( i == fila && j == col){
               _c[i][j].tanca_porta(p);
               //parets adjacents
               if(p == 0) _c[i+1][j].tanca_porta(p+2);
               else if( p == 1) _c[i][j+1].tanca_porta(p+2);
               else if(p == 2 && fila != (int)posi.first-1) _c[i+1][j].tanca_porta(p-2);
               else if (p == 3) _c[i][j-1].tanca_porta(p-2);
             }
        }
    }
  }else{
    throw error(PosicioInexistent);
  }

}

// Escriu el laberint a l'ostream (canal de sortida) os. El format per escriure
// el laberint seguirà l'exposat a l'apartat 2.3.

/* COST: O(posi.first*posi.second) ja que com a màxim reocorrera fins a tantes files per columnes hi hagi*/
void laberint::print(std::ostream & os) const throw(){
    /*PRE: Considerem que el laberint nostre es correcte*/
    /*POST:Imprimeix per pantalla la representació gràfica del laberint en qüestió*/

    os<< (int)posi.first<<" "<<(int)posi.second<<'\n';

    /* COST total: O(posi.first*posi.second) ja que com a màxim reocorrera fins a tantes files per columnes hi hagi*/
    for (int i = 0; i < (int)posi.first; i++){
      /*INV: Mentres la i sigui menor a posi.first recorrerà per tantes files hi hagi.*/

      /* COST: O(posi.second) ja que farà com a màxim posi.second iteracions*/
    	for(int j=0; j<(int)posi.second; j++){
         /*INV: Mentres la j sigui menor a posi.second mira si n'hi ha cap porta oberta a les parets nords,
         si n'hi ha una oberta no treu per pantalla l'asterisc*/
    	   os << '*' << (_c[i][j].porta_oberta(paret("nord")) ? ' ' : '*');
    	}

      /*Posem l'últim asterisc de les parets nords, fem salt de línea i passem a mirar la paret oest que considerem
      la primera columna d'asteriscs després de la fila nord*/
    	os<<'*'<<'\n'<< (_c[i][0].porta_oberta(paret("oest")) ? ' ' : '*') << ' ';

      /* COST: O(posi.second) ja que farà com a màxim posi.second iteracions*/
    	for(int j=0; j<(int)posi.second; j++){
          /*INV: Mentres la j sigui menor a posi.second mira si n'hi ha cap porta oberta a les parets ests (que considerem aquelles
          que venen a continuació de la oest i es van alternant amb les files nord), si n'hi ha una oberta no treu per pantalla l'asterisc*/

          if(j == (int)posi.second-1){// Si estem a la última posició no volem que tregui un espai a continuació de l'asterisc, si no que faci el salt de línea
            os << (_c[i][j].porta_oberta(paret("est")) ? ' ' : '*');
          }else{
             os << (_c[i][j].porta_oberta(paret("est")) ? ' ' : '*') << ' ';
           }
    	}
    	os<<'\n';
    }

    /*Sabem que la última fila a ser exterior només podrà ser tots asteriscs seguits, ja que no hi ha possibilitat de tenir cap porta oberta.
     Per tant, si sabem que una cambra la seva paret sud ve representada per 3 asteriscs i les seves adjacents comparteixen asteriscs, podem
     determinar que hi haurà el doble + 1 d'asteriscs que el nombre de columnes, és a dir posi.second*2+1.

     Llavors ens limitem a treure per pantalla tants asteriscs com posi.second*2+1*/
    os<< string((int)posi.second*2+1, (_c[(int)posi.first-1][(int)posi.second-1].porta_oberta(paret("sud")) ? ' ' : '*')) <<'\n';

}
