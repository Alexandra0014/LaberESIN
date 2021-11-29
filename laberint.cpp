#include "laberint.hpp"

// Constructora d'un laberint buit sense excavar (sense cap porta oberta)
// de la mida indicada. Totes les cambres del laberint no tenen cap porta.
// Es produeix un error si el número de files o de columnes del laberint és 0.
laberint::laberint(nat num_fil, nat num_col) throw(error){
  if (num_fil != 0 && num_col != 0)
  {
    pos.first = num_fil;
    pos.second = num_col;
    _fila = pos.first;
    _columna = pos.second;
    _c = new cambra *[_fila];
    for(nat i = 1; i <= pos.first; i++){
        _c[i] = new cambra [_columna];
    }
  }
  else throw error(FilsColsIncorrecte);

}

// Constructora d'un laberint a partir d'un istream (canal d'entrada) is.
// El format de l'istream seguirà l'exposat a l'apartat 2.3. Es presuposa que
// el laberint és correcte.
laberint::laberint(std::istream & is) throw(error){
  //is>>*this;
}

// Constructora per còpia, assignació i destructora.
laberint::laberint(const laberint & l) throw(error){
  pos.first = l.pos.first;
  pos.second = l.pos.second;
  for(nat i = 1; i <= pos.first; i++){
    for(nat j = 1; j <= pos.second; j++ ){
        _c[i][j] =l._c[i][j];
    }
  }
}
laberint & laberint::operator=(const laberint & l) throw(error){
  if(this != &l){
    pos.first = l.pos.first;
    pos.second = l.pos.second;
    for(nat i = 1; i <= pos.first; i++){
      for(nat j = 1; j <= pos.second; j++ ){
          _c[i][j] =l._c[i][j];
      }
    }
  }
  return *this;
}
laberint::~laberint() throw(){
  for(nat i = 1; i <= pos.first; i++){
        delete[] _c[i];
  }
  delete [] _c;
}

// Retornen el número de files i columnes que té el laberint, respectivament.
nat laberint::num_files() const throw(){
  return pos.first;
}
nat laberint::num_columnes() const throw(){
  return pos.second;
}

// Retorna la cambra situada a la posició especificada per pos.
// Aquest mètode permet utilitzar el laberint d'aquesta manera:
//   laberint l(3,4);   --> Es crea un laberint de 3x4
//   posicio pos(2,2);  --> Posicion que accedemos dentro del laberinto que hemos creado previamente
//   cambra c = l(pos); --> Se nombra la cabmra en tal pos.
// Es produeix un error si la posició donada no existeix al laberint.
cambra laberint::operator()(const posicio & pos) const throw(error){
  cambra res;
  nat r_fila = pos.first;
  nat r_col = pos.second;
  for(nat i = 1; i <= pos.first; i++){
    for(nat j = 1; j <= pos.second; j++ ){
        if(_c[i][j] == _c[r_fila][r_col]){
          res = _c[i][j];
        }
    }
  }
  return res;
}

// Obre la porta en la paret donada de la cambra que està especificada per pos.
// També obre la porta corresponent en la cambra adjacent. Es produeix un error
// si la posició no existeix o no es pot obrir una porta en la direcció
// indicada perquè dóna a l'exterior.
void laberint::obre_porta(paret p, const posicio & pos) throw(error){
  nat fila = pos.first;
  nat col = pos.second;
  if(fila >= 1 && fila <= pos.first && col >= 1 && col <= pos.second){
    if(fila == 1 && p == 'S') throw error(PortaExterior);
    else if(fila ==  pos.first && p == 'N') throw error(PortaExterior);
    else if(col == 1 && p == 'O') throw error(PortaExterior);
    else if(col == pos.second && p == 'E') throw error(PortaExterior);
    else {
        _c[fila][col].obre_porta(p);
    }

  }else throw error(FilsColsIncorrecte);

}

// Tanca la porta en la paret donada de la cambra que està especificada per pos.
// També tanca la porta corresponent en la cambra adjacent. Es produeix un error
// si la posició no existeix.
void laberint::tanca_porta(paret p, const posicio & pos) throw(error){
  nat fila = pos.first;
  nat col = pos.second;
  if(fila >= 1 && fila <= pos.first && col >= 1 && col <= pos.second){
    if(fila == 1 && p == 'S') throw error(PortaExterior);
    else if(fila ==  pos.first && p == 'N') throw error(PortaExterior);
    else if(col == 1 && p == 'O' ) throw error(PortaExterior);
    else if(col ==  pos.second && p == 'E') throw error(PortaExterior);
    else{
        _c[fila][col].tanca_porta(p);
    }

  }else throw error(FilsColsIncorrecte);
}

// Escriu el laberint a l'ostream (canal de sortida) os. El format per escriure
// el laberint seguirà l'exposat a l'apartat 2.3.
void laberint::print(std::ostream & os) const throw(){
  for(nat i = 1; i <= pos.first; i++){
    for(nat j = 1; j <= pos.second; j++ ){
      os << '*' << (_c[i][j].porta_oberta(paret("nord")) ? ' ' : '*') << '*' << '\n';
      os << (_c[i][j].porta_oberta(paret("oest")) ? ' ' : '*') << ' ';
      os << (_c[i][j].porta_oberta(paret("est")) ? ' ' : '*') << '\n';
      os << '*' << (_c[i][j].porta_oberta(paret("sud")) ? ' ' : '*') << '*';
    }
  }
}
