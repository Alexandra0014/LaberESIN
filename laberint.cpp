#include "laberint.hpp"
#include <iostream>

using namespace std;

// Constructora d'un laberint buit sense excavar (sense cap porta oberta)
// de la mida indicada. Totes les cambres del laberint no tenen cap porta.
// Es produeix un error si el número de files o de columnes del laberint és 0.

/* COST: O(posi.first) ja que com a màxim arriba fins al número de files indicat per
paràmetre*/
laberint::laberint(nat num_fil, nat num_col) throw(error){
  /*PRE: En passen el nombre de files i columnes respectivament*/
  /*POST: Creació dinàmica d'un laberint segons les mides passades per p.i
  amb totes les portes tancades*/

  if (num_fil != 0 && num_col != 0)
  {
    posi.first = num_fil;
    posi.second = num_col;
    _c = new cambra *[posi.first];
    /* COST: O(posi.first) ja que com a màxim arriba fins al número de files indicat per
    paràmetre*/
    for(nat i = 0; i < posi.first; i++){
      /*INV: Mentres que la i sigui menor a posi.first a la posició i de l'array _c,
      anem creant un array amb les columnes del laberint*/
        _c[i] = new cambra [posi.second];
    }
  }
  else throw error(FilsColsIncorrecte);

}

// Constructora d'un laberint a partir d'un istream (canal d'entrada) is.
// El format de l'istream seguirà l'exposat a l'apartat 2.3. Es presuposa que
// el laberint és correcte.
/* COST: */
laberint::laberint(std::istream & is) throw(error){
  /*PRE: */
  /*POST:*/

  int fila = 0, columna = 0;
  is >> fila >> columna;
  posi.first=fila;
  posi.second=columna;

  string s;
  bool trobat = true;

  laberint l = laberint(posi.first, posi.second);
  int contador = -1;
  /* COST: */
  while(getline(is, s)){
  int medida = s.size()-1;
  if(trobat){
    /* COST: O(medida)*/
  	for (int i = 0, fil = 0; i < medida; i+=2, fil++){
        /*INV:*/
  		if (s[i] != '*' ){
  			 l._c[contador][fil-1].obre_porta(paret("est"));
  			 l._c[contador][fil].obre_porta(paret("oest"));
  		}
  	}
  	trobat = false;
  	contador++;
  }
  else{
    /* COST: O(medida)*/
  	for (int i = 1, fil = 0; i < medida; i+=2, fil++){
        /*INV: Mentres que i sigui menor a medida */
  		if (s[i] != '*' ){
  			 l._c[contador][fil].obre_porta(paret("nord"));
         l._c[contador-1][fil].obre_porta(paret("sud"));
  		}
  	}
  trobat = true;
  }
}

*this = l;

}

// Constructora per còpia, assignació i destructora.
/* COST: O(posi.first*posi.second) ja que recorrem totes les posicions del laberint l per total
copiar-lo al nostre laberint*/
laberint::laberint(const laberint & l) throw(error){
  /*PRE: Ens passen un laberint l*/
  /*POST:*/

  posi.first = l.posi.first;
  posi.second = l.posi.second;
  _c = new cambra* [posi.first];
  /* COST: */
  for(nat i = 0; i < posi.first; i++){
      /*INV:*/
    _c[i] = new cambra[posi.second];
  }
  /* COST: */
  for(nat i = 0; i < posi.first; i++){
      for(nat j = 0; j < posi.second; j++){
          /*INV:*/
        _c[i][j] = l._c[i][j];
      }
  }
}

/* COST: */
laberint & laberint::operator=(const laberint & l) throw(error){
  /*PRE: */
  /*POST:*/

  if(this != &l){
    if(posi.first != l.posi.first ||  posi.second != l.posi.second){
       /* COST: */
      for(nat i = 0; i < posi.first; i++){
          /*INV:*/
          delete[] _c[i];
      }
      delete[] _c;
    }
      posi.first = l.posi.first;
      posi.second = l.posi.second;
      _c = new cambra* [posi.first];
      /* COST: */
      for(nat i = 0; i < posi.first; i++){
          /*INV:*/
          _c[i] = new cambra[posi.second];
      }
      /* COST: */
      for(nat i = 0; i < posi.first; i++){
          for(nat j = 0; j < posi.second; j++){
              /*INV:*/
            _c[i][j] = l._c[i][j];
          }
      }
  }
  return *this;
}

/* COST: */
laberint::~laberint() throw(){
  /*PRE: */
  /*POST:*/

  for(nat i = 0; i < posi.first; i++){
      /*INV:*/
      delete[] _c[i];
  }
  delete[] _c;
}

// Retornen el número de files i columnes que té el laberint, respectivament.
/* COST: */
nat laberint::num_files() const throw(){
  /*PRE: */
  /*POST:*/

  return posi.first;
}
/* COST: */
nat laberint::num_columnes() const throw(){
  /*PRE: */
  /*POST:*/

  return posi.second;
}

// Retorna la cambra situada a la posició especificada per pos.
// Aquest mètode permet utilitzar el laberint d'aquesta manera:
//   laberint l(3,4);   --> Es crea un laberint de 3x4
//   posicio pos(2,2);  --> Posicion que accedemos dentro del laberinto que hemos creado previamente
//   cambra c = l(pos); --> Se nombra la cabmra en tal pos.
// Es produeix un error si la posició donada no existeix al laberint.

/* COST: */
cambra laberint::operator()(const posicio & pos) const throw(error){
  /*PRE: */
  /*POST:*/

  int fila =  (int) pos.first-1;
  int col =  (int) pos.second-1;

  cambra res;
  if(fila >= 0 && fila < (int)posi.first && col >= 0 && col < (int)posi.second){
    /* COST: */
    for(int i = 0; i < (int)posi.first; i++){
        for(int j = 0; j < (int)posi.second; j++){
            /*INV:*/
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

/* COST: */
void laberint::obre_porta(paret p, const posicio & pos) throw(error){ //REVISAR CONDICIONES
  /*PRE: */
  /*POST:*/

  int fila = (int)pos.first-1;
  int col = (int)pos.second-1;
  if(fila >= 0 && fila < (int)posi.first && col >= 0 && col < (int)posi.second){
    /* COST: */
    for(int i = 0; i < (int)posi.first; i++){
        for(int j = 0; j < (int)posi.second; j++){
          /*INV:*/
          //BORDES
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

/* COST: */
void laberint::tanca_porta(paret p, const posicio & pos) throw(error){
  /*PRE: */
  /*POST:*/

  int fila = (int)pos.first-1;
  int col = (int)pos.second-1;
  if(fila >= 0 && fila < (int)posi.first && col >= 0 && col < (int)posi.second){
     /* COST: */
    for(int i = 0; i < (int)posi.first; i++){
        for(int j = 0; j < (int)posi.second; j++){
            /*INV:*/
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

/* COST: */
void laberint::print(std::ostream & os) const throw(){
    /*PRE: */
    /*POST:*/

    os<< (int)posi.first<<" "<<(int)posi.second<<'\n';
    /* COST: */
    for (int i = 0; i < (int)posi.first; i++){
    	for(int j=0; j<(int)posi.second; j++){
           /*INV:*/
    	   os << '*' << (_c[i][j].porta_oberta(paret("nord")) ? ' ' : '*');
    	}

    	os<<'*'<<'\n'<< (_c[i][0].porta_oberta(paret("oest")) ? ' ' : '*') << ' ';

    	for(int j=0; j<(int)posi.second; j++){
            /*INV:*/
            if(j == (int)posi.second-1){
              os << (_c[i][j].porta_oberta(paret("est")) ? ' ' : '*');
            }else{
               os << (_c[i][j].porta_oberta(paret("est")) ? ' ' : '*') << ' ';
             }
    	}
    	os<<'\n';
    }

 os<< string((int)posi.second*2+1, (_c[(int)posi.first-1][(int)posi.second-1].porta_oberta(paret("sud")) ? ' ' : '*')) <<'\n';

}
