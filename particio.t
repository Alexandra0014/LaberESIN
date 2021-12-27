#include "particio.hpp"
#include<iostream>
using namespace std;



////////////////////// CONSTRUCTORA
// Construeix una particio amb n elements com a màxim.
template <typename T>
particio<T>::particio(nat n) throw(error){
    n_max = n;
    _arrel = new node;
    try {
      _arrel -> _esq = NULL;
      _arrel -> _dret = NULL;
    }
    catch (...) {
      delete _arrel;
      throw;
  }

}
////////////////////// CONSTRUCTORA COPIA
//Metode auxiliar copia
// La còpia es fa seguint un recorregut en preordre.
template <typename T>
typename particio<T>::node* particio<T>::copia_particio(node* p) {
  node* aux = NULL;
  if (p != NULL) {
    aux = new node;
    try {
      aux -> _k = p -> _k;
      aux -> _esq = aux -> _dret = NULL;
      aux -> _esq = copia_particio(p -> _esq);
      aux -> _dret = copia_particio(p -> _dret);
    }
    catch (...) {
      destrueix_particio(aux);
    }
  }
  return aux;
}

// Constructora per còpia, assignació i destructora.
template <typename T>
particio<T>::particio(const particio & p) throw(error){
    _arrel = copia_particio(p._arrel);
}
////////////////////// ASSIGNACIÓ
template <typename T>
particio<T> & particio<T>::operator=(const particio & p) throw(error){
    particio<T> tmp(p);
    node* aux = _arrel;
    _arrel = tmp._arrel;
    tmp._arrel = aux;
    return *this;
}
////////////////////// DESTRUCTORA
//Metode auxiliar Destructora
// La destrucció es fa seguint un recorregut en postordre.
template <typename T>
void particio<T>::destrueix_particio(node* p) {
  if (p != NULL) {
    destrueix_particio(p -> _esq);
    destrueix_particio(p -> _dret);
    delete p;
  }
}
template <typename T>
particio<T>::~particio() throw(){
    destrueix_particio(_arrel);
}

////////////////////// AFEGIR
//Metode auxiliar factor equilibri
template <typename T>
nat particio<T>::factor_eq(node *n){
    if (n == NULL) return 0;
    return altura_max(n->_esq) - altura_max(n->_dret);
}

//Metode auxiliar max:  retorna el maxim de dos element
template <typename T>
T particio<T>::max(T a, T b){
    return (a > b)? a : b;
}

//Metode auxiliar altura_max: retorna la clau màxima de la particio
template <typename T>
nat particio<T>::altura_max(node *n){
    if (n == NULL) return 0;
    return n->alt_max;
}
//Metode auxiliar per crear un nou node
template <typename T>
typename particio<T>::node* particio<T>:: newNode(T k){
    node* n = new node();
    n -> _k = k;
    n -> _esq = NULL;
    n -> _dret = NULL;
    n -> alt_max = 1;
    n_elem ++;
    return n;
}

//ROTACIONS
//Girar a la dreta el subarbre arrelat amb y
template <typename T>
typename particio<T>::node* particio<T>::rightRotate(node *y){
    node *x = y->_esq;
    node *aux = x->_dret;

    // Perform rotation
    x->_dret = y;
    y->_esq = aux;

    // Update heights
    y->alt_max = max(altura_max(y->_esq),
                    altura_max(y->_dret)) + 1;
    x->alt_max = max(altura_max(x->_esq),
                    altura_max(x->_dret)) + 1;

    // Return new root
    return x;
}
//Girar a la esquerra el subarbre arrelat amb x
template <typename T>
typename particio<T>::node* particio<T>::leftRotate(node *x){
    node *y = x->_dret;
    node *aux = y->_esq;

    // Perform rotation
    y->_esq = x;
    x->_dret = aux;

    // Update heights
    x->alt_max = max(altura_max(x->_esq),
                    altura_max(x->_dret)) + 1;
    y->alt_max = max(altura_max(y->_esq),
                    altura_max(y->_dret)) + 1;

    // Return new root
    return y;
}

// Metode auxiliar d'afegir
template <typename T>
typename particio<T>::node* particio<T>::insereix_avl(node *n, const T &k){
    //BST

    if (n == NULL){
        return newNode(k);
    }
    else{
        if (k < n->_k) {
            n->_esq = insereix_avl(n->_esq, k);
        }else if (k > n->_k) {
            n->_dret = insereix_avl(n->_dret, k);
        }
    }

    //Actualització altura maxima del node anterior
    n->alt_max = 1 + max(altura_max(n->_esq),altura_max(n->_dret));

    // Factor d'equilibri del node anterior pero comprovar si esta desequilibrat
    int equilibri = factor_eq(n);

    // casos si està descompensat

    // Left Left Case
    if (equilibri > 1 && k < n->_esq->_k)
        return rightRotate(n);

    // Right Right Case
    if (equilibri < -1 && k > n->_dret->_k)
        return leftRotate(n);

    // Left Right Case
    if (equilibri > 1 && k > n->_esq->_k)
    {
        n->_esq = leftRotate(n->_esq);
        return rightRotate(n);
    }

    // Right Left Case
    if (equilibri < -1 && k < n->_dret->_k)
    {
        n->_dret = rightRotate(n->_dret);
        return leftRotate(n);
    }
cout<<"TENGOOOOOOOOO: "<<n -> _k<<endl;
cout<<"n_elem: "<<n_elem<<endl;

return n;
}

// Afegeix un nou element a la particio. Aquest nou element formarà ell sol
// un nou grup. En cas que l'element ja estigués present a la partició llavors
// no es modifica la partició. Es produeix un error si la particio ja té el
// número màxim d'elements abans d'afegir aquest nou.
template <typename T>
void particio<T>::afegir(const T &x) throw(error){
    if(n_max +1 == n_elem ) throw error(ParticioPlena);
    else{
        _arrel = insereix_avl(_arrel, x);
    }
}

////////////////////// UNIR
// Uneix els dos grups als quals pertanyen aquests dos elements. Si tots dos
// elements ja pertanyien al mateix grup no fa res.
// Es produeix un error si algun dels elements no pertany a la partició.

template <typename T>
void particio<T>::unir(const T & x, const T & y) throw(error){
    cout<<x<<y<<endl;
}

////////////////////// MATEIX GRUP
// Retorna si els elements x i y pertanyen al mateix grup.
// Es produeix un error si algun dels dos elements no pertany a la partició.

template <typename T>
bool particio<T>::mateix_grup(const T & x, const T & y) const throw(error){
    cout<<x<<y<<endl;
    return true;
}

////////////////////// MAXIM GRUP
// Retorna el número de grups que té la particio.
template <typename T>
nat particio<T>::size() const throw(){
  return max_grup;
}

//////////////////////  NUM Elements
// Retorna el número d'elements que té la particio.
template <typename T>
nat particio<T>::num_elements() const throw(){
  return n_elem;
}
//////////////////////  NUM MAXIM
// Retorna el número màxim d'elements que pot tenir la particio.
template <typename T>
nat particio<T>::num_maxim() const throw(){
  return n_max;
}
