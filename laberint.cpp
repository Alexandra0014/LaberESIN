#include "laberint.hpp"
#include <iostream>

using namespace std;

// Constructora d'un laberint buit sense excavar (sense cap porta oberta)
// de la mida indicada. Totes les cambres del laberint no tenen cap porta.
// Es produeix un error si el número de files o de columnes del laberint és 0.
laberint::laberint(nat num_fil, nat num_col) throw(error){
  if (num_fil != 0 && num_col != 0)
  {
    posi.first = num_fil;
    posi.second = num_col;
    _c = new cambra *[posi.first];
    for(nat i = 0; i < posi.first; i++){
        _c[i] = new cambra [posi.second];
    }
  }
  else throw error(FilsColsIncorrecte);

}

// Constructora d'un laberint a partir d'un istream (canal d'entrada) is.
// El format de l'istream seguirà l'exposat a l'apartat 2.3. Es presuposa que
// el laberint és correcte.
laberint::laberint(std::istream & is) throw(error){

}

// Constructora per còpia, assignació i destructora.
laberint::laberint(const laberint & l) throw(error){
  posi.first = l.posi.first;
  posi.second = l.posi.second;
  _c = new cambra* [posi.first];
  for(nat i = 0; i < posi.first; i++){
    _c[i] = new cambra[posi.second];
  }
  for(nat i = 0; i < posi.first; i++){
      for(nat j = 0; j < posi.second; j++){
        _c[i][j] = l._c[i][j];
      }
  }
}

laberint & laberint::operator=(const laberint & l) throw(error){
  if(this != &l){
    posi.first = l.posi.first;
    posi.second = l.posi.second;
    _c = new cambra* [posi.first];
    for(nat i = 0; i < posi.first; i++){
      _c[i] = new cambra[posi.second];
    }
    for(nat i = 0; i < posi.first; i++){
        for(nat j = 0; j < posi.second; j++){
          _c[i][j] = l._c[i][j];
        }
    }
  }
  return *this;
}

laberint::~laberint() throw(){
  for(nat i = 0; i < posi.first; i++){
        delete[] _c[i];
  }
  delete[] _c;
}

// Retornen el número de files i columnes que té el laberint, respectivament.
nat laberint::num_files() const throw(){
  return posi.first;
}
nat laberint::num_columnes() const throw(){
  return posi.second;
}

// Retorna la cambra situada a la posició especificada per pos.
// Aquest mètode permet utilitzar el laberint d'aquesta manera:
//   laberint l(3,4);   --> Es crea un laberint de 3x4
//   posicio pos(2,2);  --> Posicion que accedemos dentro del laberinto que hemos creado previamente
//   cambra c = l(pos); --> Se nombra la cabmra en tal pos.
// Es produeix un error si la posició donada no existeix al laberint.
cambra laberint::operator()(const posicio & pos) const throw(error){

  cout << "/* pos.first:  */" <<pos.first<< endl;
  cout << "/* posi.first:  */" <<posi.first<< endl;
  nat r_fila = pos.first;
  nat r_col = pos.second;

  cambra res;

  for(nat i = 0; i < pos.first; i++){
    for(nat j = 0; j < pos.second; j++ ){
      cout<<"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA"<<endl;
        if(_c[i][j] == _c[r_fila-1][r_col-1]){
          res = _c[i][j];
        }else{
          throw error(PosicioInexistent);
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
  if(fila >= 1 && fila <= posi.first && col >= 1 && col <= posi.second){
    for(nat i = 0; i < fila; i++){
        for(nat j = 0; j < col; j++){
           if(i == 0 && p == 'S') throw error(PortaExterior);
           else if(i == pos.first && p == 'N') throw error(PortaExterior);
           else if(j == 0 && p == 'O') throw error(PortaExterior);
           else if(j == pos.second && p == 'E') throw error(PortaExterior);
           else {
              _c[i][j].obre_porta(p);
              //parets adjacents
              if(p == 0 || p == 1) _c[i][j+1].obre_porta(p+2);
              else if(p == 2 || p == 3) _c[i][j+1].obre_porta(p-2);
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
void laberint::tanca_porta(paret p, const posicio & pos) throw(error){
  nat fila = pos.first;
  nat col = pos.second;
  if(fila >= 1 && fila <= posi.first && col >= 1 && col <= posi.second){
    for(nat i = 0; i < fila; i++){
        for(nat j = 0; j < col; j++){
              _c[i][j].tanca_porta(p);
              //parets adjacents
              if(p == 0 || p == 1) _c[i][j+1].tanca_porta(p+2);
              else if(p == 2 || p == 3) _c[i][j+1].tanca_porta(p-2);
          }
    }
  }else{
    throw error(PosicioInexistent);
  }
}

// Escriu el laberint a l'ostream (canal de sortida) os. El format per escriure
// el laberint seguirà l'exposat a l'apartat 2.3.
void laberint::print(std::ostream & os) const throw(){
  os << posi.first << " " << posi.second <<'\n';
  for(nat i = 0; i < posi.first; i++){
    for(nat j = 0; j < posi.second; j++ ){
      os<<"i: "<<i<<"j: "<<j<<'\n';
      os << '*' << (_c[i][j].porta_oberta(paret("nord")) ? ' ' : '*') << '*' << '\n';
      os << (_c[i][j].porta_oberta(paret("oest")) ? ' ' : '*') << ' ';
      os << (_c[i][j].porta_oberta(paret("est")) ? ' ' : '*') << '\n';
      os << '*' << (_c[i][j].porta_oberta(paret("sud")) ? ' ' : '*') << '*';

    }
    os<<'\n';
  }
  //os<<'\n';
}
