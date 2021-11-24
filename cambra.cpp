#include "cambra.hpp"

// Construeix una cambra amb les portes als llocs indicats.
// bool n = false, s = false, e = false, o=false -> no hay puertas
//si no hay puertas = no hay paredes?
//enum {NORD, EST, SUD, OEST, NO_DIR};
cambra::cambra(bool n, bool s, bool e, bool o) throw(error){
  //0 --> nord, 1 --> sud, 2 --> est, 3 --> oest
  _porta[0] = n; //NORD = n
  _porta[1] = e; //EST = e
  _porta[2] = s; //SUD = s
  _porta[3] = o; //OEST = o
}

// Constructora per còpia, assignació i destructora.
cambra::cambra(const cambra & c) throw(error){

  _porta[0] = c._porta[0]; //NORD = n
  _porta[1] = c._porta[1];
  _porta[2] = c._porta[2];
  _porta[3] = c._porta[3];
}

cambra & cambra::operator=(const cambra & c) throw(error){
  if(this != &c){
    _porta[0] = c._porta[0]; //NORD = n
    _porta[1] = c._porta[1];
    _porta[2] = c._porta[2];
    _porta[3] = c._porta[3];
  }
  return *this;
}

cambra::~cambra() throw(){
  delete[] this;
}

// Retorna si l'habitació té una porta oberta a la paret indicada.
// oberta == true
// En p nos dirá si es NORD,SUD,EST,OEST,NO_DIR
bool cambra::porta_oberta(paret p) const throw(){
  bool porta_open = true;
  if(p == 0) //NORD
  {
    porta_open = _porta[0];
  }
  else if ( p == 1) //EST
  {
    porta_open = _porta[1];
  }
  else if( p == 2) //SUD
  {
    porta_open = _porta[2];
  }
  else if ( p == 3) //OEST
  {
    porta_open = _porta[3];
  }
  return porta_open;
}

// Obre una nova porta a la paret indicada. Si la porta ja està oberta no
// fa res. Es produeix un error si la paret és NO_DIR.
void cambra::obre_porta(paret p) throw(error){

  if(p == 0) //NORD
  {
    _porta[0] = true;
  }
  else if ( p == 1) //EST
  {
    _porta[1] = true;
  }
  else if( p == 2) //SUD
  {
    _porta[2] = true;
  }
  else if ( p == 3) //OEST
  {
    _porta[3] = true;

  }else{
    throw error(ParetInexistent);
  }

}

// Tanca la porta a la paret indicada. Si la porta ja estava tancada no
// fa res. Es produeix un error si la paret és NO_DIR.
void cambra::tanca_porta(paret p) throw(error){
  if( p == 0) //NORD
  {
    _porta[0] = false;
  }
  else if ( p == 1) //EST
  {
    _porta[1] = false;
  }
  else if( p == 2) //SUD
  {
    _porta[2] = false;
  }
  else if ( p == 3) //OEST
  {
    _porta[3] = false;
  }else{
    throw error(ParetInexistent);
  }

}

// Igualtat i desigualtat entre cambres. Dues cambres es consideren iguals
// si tenen les mateixes portes obertes a les mateixes parets.
bool cambra::operator==(const cambra & c) const throw(){
  bool igual = false;
  if((_porta[0] == c._porta[0]) &&
      (_porta[1] == c._porta[1]) &&
      ( _porta[2] == c._porta[2]) &&
      ( _porta[3] == c._porta[3] )) igual = true;

return igual;
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
  int contT_nuestro, contT_suyo;
  bool menor_que = false;
  bool parar = false;
  for (int i = 0; i < 4; i++){
    if(c._porta[i] == false) contT_suyo++;
    else if(_porta[i] == false) contT_nuestro++;
  }
  if(contT_nuestro > contT_suyo) menor_que = true;
  else if( contT_nuestro == contT_suyo){
    int i =0;
    while(!parar &&  i < 4){
      if(_porta[i] != c._porta[i]){
        if(_porta[i] == false) menor_que = true;
        parar = true;
      }
      i++;
    }
  }

  return menor_que;
}
