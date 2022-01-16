#include "cambra.hpp"

/* Construeix una cambra amb les portes als llocs indicats.*/
/* COST: O(1) Ja que només hi han assignacions*/
cambra::cambra(bool n, bool s, bool e, bool o) throw(error){
    /*PRE: Ens passen per paràmetre 4 booleans tots inicialitzats a false*/
    /*POST: Array complet amb portes tancades a totes les direccions*/

  _porta[0] = n;
  _porta[1] = e;
  _porta[2] = s;
  _porta[3] = o;
}

// Constructora per còpia, assignació i destructora.

/* Constructora on donada una cambra, es fa una còpia*/
/* COST: O(1) Ja que només hi han assignacions*/
cambra::cambra(const cambra & c) throw(error){
  /*PRE: Ens passen per paràmetre una cambra c*/
  /*POST: Copiem la cambra passada per paràmetre a la nostra*/

  _porta[0] = c._porta[0];
  _porta[1] = c._porta[1];
  _porta[2] = c._porta[2];
  _porta[3] = c._porta[3];
}

/* Assignació d'una cambra donada a la nostra*/
/* COST: O(1) Ja que només hi han assignacions*/
cambra & cambra::operator=(const cambra & c) throw(error){
  /*PRE: Ens passen per paràmetre una cambra c*/
  /*POST: Retorna l'assignació de la cambra passada per paràmetre a la nostra*/

  if(this != &c){
    _porta[0] = c._porta[0];
    _porta[1] = c._porta[1];
    _porta[2] = c._porta[2];
    _porta[3] = c._porta[3];
  }
  return *this;
}

/* Destructora automàtica de la nostra cambra */
/* COST: O(1)*/
cambra::~cambra() throw(){}

/* Retorna si l'habitació té una porta oberta a la paret indicada.*/
/* COST: O(1) Ja que només hi han assignacions i if's*/
bool cambra::porta_oberta(paret p) const throw(){
  /*PRE: Ens passen per paràmetre una direcció d'una paret*/
  /*POST: Retorna un booleà true si la porta en la paret indicada és oberta
  si no retorna false*/

  bool porta_open = false;
  if(p == 0)
  {
    porta_open = _porta[0];
  }
  else if ( p == 1)
  {
    porta_open = _porta[1];
  }
  else if( p == 2)
  {
    porta_open = _porta[2];
  }
  else if ( p == 3)
  {
    porta_open = _porta[3];
  }
  return porta_open;
}

// Obre una nova porta a la paret indicada. Si la porta ja està oberta no
// fa res. Es produeix un error si la paret és NO_DIR.
/* COST: O(1) Ja que només hi han assignacions i if's*/
void cambra::obre_porta(paret p) throw(error){
  /*PRE: Ens passen per paràmetre una direcció d'una paret */
  /*POST: Posem a true la porta indicada segons la direcció de la paret passada per paràmetre en
    cas que no hagi estat oberta abans, si no existeix la paret que ens passen, llancem
    l'error ParetInexistent*/

  if(p == 0)
  {
    _porta[0] = true;
  }
  else if ( p == 1)
  {
    _porta[1] = true;
  }
  else if( p == 2)
  {
    _porta[2] = true;
  }
  else if ( p == 3)
  {
    _porta[3] = true;

  }else{

    throw error(ParetInexistent);
  }

}

// Tanca la porta a la paret indicada. Si la porta ja estava tancada no
// fa res. Es produeix un error si la paret és NO_DIR.
/* COST: O(1) Ja que només hi han assignacions i if's*/
void cambra::tanca_porta(paret p) throw(error){
  /*PRE: Ens passen per paràmetre una direcció d'una paret */
  /*POST: Posem a false la porta indicada segons la direcció de la paret passada per paràmetre en
    cas que no hagi estat tancada abans, si no existeix la paret que ens passen, llancem
    l'error ParetInexistent*/

  if( p == 0)
  {
    _porta[0] = false;
  }
  else if ( p == 1)
  {
    _porta[1] = false;
  }
  else if( p == 2)
  {
    _porta[2] = false;
  }
  else if ( p == 3)
  {
    _porta[3] = false;
  }else{
    throw error(ParetInexistent);
  }

}

// Igualtat entre cambres. Dues cambres es consideren iguals
// si tenen les mateixes portes obertes a les mateixes parets.
/* COST: O(1) Ja que només hi han assignacions i if's*/
bool cambra::operator==(const cambra & c) const throw(){
  /*PRE: Ens passen per paràmetre una cambra c*/
  /*POST: Retorna true en cas que l'array de portes de la cambra passada per paràmetre
  sigui igual a la nostra */

  bool igual = false;
  if((_porta[0] == c._porta[0]) &&
  (_porta[1] == c._porta[1]) &&
  ( _porta[2] == c._porta[2]) &&
  ( _porta[3] == c._porta[3] )) igual = true;

  return igual;
}

// Desigualtat entre cambres. Dues cambres no es consideren iguals
// si no tenen les mateixes portes obertes a les mateixes parets.
/* COST: O(1) Ja que és una igualació negada*/
bool cambra::operator!=(const cambra & c) const throw(){
  /*PRE: Ens passen per paràmetre una cambra c*/
  /*POST:Retorna false en cas que l'array de portes de la cambra passada per paràmetre
  sigui diferent de la nostra. */

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

/* COST: O(4) És el nombre de posicions que té el array _porta*/
bool cambra::operator<(const cambra & c) const throw(){
  /*PRE: Ens passen per paràmetre una cambra c */
  /*POST: Retorna true en cas que la nostra cambra sigui més petita que la passada per paràmetre,
  false en cas contrari.*/

  int contT_nuestro = 0, contT_suyo = 0;
  bool menor_que = false;
  bool parar = false; // variable sentinella per parar l'execució una vegada trobada una porta tancada

  /* COST: O(4) És el nombre de posicions que té el array _porta*/
  for (int i = 0; i < 4; i++){
    /*INV: Mentres que la i sigui menor a 4 recorrem l'array _porta*/
    if(c._porta[i] == false) contT_suyo++;
    if(_porta[i] == false) contT_nuestro++;
  }

  if(contT_nuestro > contT_suyo) menor_que = true;
  else if( contT_nuestro == contT_suyo){
    int i =0;
    /* COST: O(4) És el nombre de posicions que té el array _porta */
    while(!parar &&  i < 4){
      /*INV: Mentres el booleà parar no sigui true i la i sigui menor a 4,
      anirem recorrent l'array _porta*/
      if(_porta[i] != c._porta[i]){
        if(_porta[i] == false) menor_que = true;
        parar = true;
      }
      i++;
    }
  }

  return menor_que;
}
