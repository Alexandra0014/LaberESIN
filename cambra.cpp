#include "cambra.hpp"

// Construeix una cambra amb les portes als llocs indicats.
// bool n = false, s = false, e = false, o=false -> no hay puertas
//si no hay puertas = no hay paredes?
//enum {NORD, EST, SUD, OEST, NO_DIR};
explicit cambra::cambra(bool n=false, bool s=false, bool e=false, bool o=false) throw(error){
  //0 --> nord, 1 --> sud, 2 --> est, 3 --> oest

  _cambra._porta[cambra._p = 0] = n; //NORD = n
  _cambra._porta[cambra._p = 1] = e; //EST = e
  _cambra._porta[cambra._p = 2] = s; //SUD = s
  _cambra._porta[cambra._p = 3] = o; //OEST = o
  if(_cambra._p == NO_DIR) throw error(ParetInexistent);

}

// Constructora per còpia, assignació i destructora.
cambra::cambra(const cambra & c) throw(error){
  _cambra._porta[cambra._p = 0] = c._cambra._porta[cambra._p = 0]; //NORD = n
  _cambra._porta[cambra._p = 1] = c._cambra._porta[cambra._p = 1];
  _cambra._porta[cambra._p = 2] = c._cambra._porta[cambra._p = 2];
  _cambra._porta[cambra._p = 3] = c._cambra._porta[cambra._p = 3];
}

cambra & cambra::operator=(const cambra & c) throw(error){
  if(this != &c){
    _cambra._porta[cambra._p = 0] = c._cambra._porta[cambra._p = 0]; //NORD = n
    _cambra._porta[cambra._p = 1] = c._cambra._porta[cambra._p = 1];
    _cambra._porta[cambra._p = 2] = c._cambra._porta[cambra._p = 2];
    _cambra._porta[cambra._p = 3] = c._cambra._porta[cambra._p = 3];
  }
  return *this;
}

cambra::~cambra() throw(){}

// Retorna si l'habitació té una porta oberta a la paret indicada.
// oberta == true
// En p nos dirá si es NORD,SUD,EST,OEST,NO_DIR
bool cambra::porta_oberta(paret p) const throw(){
  cambra._p = p;
  bool porta_open = false;
  if(_cambra._porta[cambra._p = 0]) //NORD
  {
    porta_open = oberta;
  }
  else if ( _cambra._porta[cambra._p = 1]) //EST
  {
    porta_open = oberta;
  }
  else if( _cambra._porta[cambra._p = 2]) //SUD
  {
    porta_open = oberta;
  }
  else if ( _cambra._porta[cambra._p = 3]) //OEST
  {
    porta_open = oberta;
  }
  return porta_open;
}

// Obre una nova porta a la paret indicada. Si la porta ja està oberta no
// fa res. Es produeix un error si la paret és NO_DIR.
void cambra::obre_porta(paret p) throw(error){
  cambra._p = p;
  if( cambra._p == 0) //NORD
  {
    _cambra._porta[cambra._p = 0] = oberta;
  }
  else if ( cambra._p == 1) //EST
  {
    _cambra._porta[cambra._p = 1] = oberta;
  }
  else if( cambra._p == 2) //SUD
  {
    _cambra._porta[cambra._p = 2] = oberta;
  }
  else if ( cambra._p == 3) //OEST
  {
    _cambra._porta[cambra._p = 3] = oberta;
  }else{
    throw error(ParetInexistent);
  }

}

// Tanca la porta a la paret indicada. Si la porta ja estava tancada no
// fa res. Es produeix un error si la paret és NO_DIR.
void cambra::tanca_porta(paret p) throw(error){
  cambra._p = p;
  if(cambra._p = 4) throw error(ParetInexistent);
  }else{
    !obre_porta(*this cambra._p);
  }

}

// Igualtat i desigualtat entre cambres. Dues cambres es consideren iguals
// si tenen les mateixes portes obertes a les mateixes parets.
bool cambra::operator==(const cambra & c) const throw(){

  if((_cambra._porta[cambra._p = 0] == c._cambra._porta[cambra._p = 0])) &&
      (_cambra._porta[cambra._p = 1] == c._cambra._porta[cambra._p = 1]) &&
      (  _cambra._porta[cambra._p = 2] == c._cambra._porta[cambra._p = 2]) &&
      ( _cambra._porta[cambra._p = 3] == c._cambra._porta[cambra._p = 3] )) return true;
  else return false;

}
bool cambra::operator!=(const cambra & c) const throw(){
    return not(*this == c);
}

// Operador "menor que" entre cambres. Una cambra és més petita que una
// altra si té més portes tancades que l'altra. Tenint en compte que una
// porta tancada és més petita que una porta oberta, en cas que tinguin el
// mateix número de portes tancades, per decidir qui és més petit es miraran
// les portes en aquest ordre NORD, EST, SUD i OEST. Per exemple:
//   cambra c1, c2(true,true), c3(true, false, true);
//   cout << (c1 < c2); // escriu 'true'
//   cout << (c2 < c3); // escriu 'true'
bool cambra::operator<(const cambra & c) const throw(){
  int cont1, cont2 = 0;
  bool menor_que = false;
  for(int i = 0; i < DIR_MAX; i++){
    if(c._cambra._porta[cambra._p = i] == tancat) cont1++;
    if(_cambra._porta[cambra._p = i] == tancat) cont2++;
  }
  if(cont1 < cont2) menor_que = true;
}
