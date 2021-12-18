#include "particio.hpp"

//Inicialización
template <typename T>
particio<T>::node::node (const T &k, node* esq, node* dret) :
 _k(k), _esq(esq), _dret(dret), _n(1) {
}

// Construeix una particio amb n elements com a màxim.
template <typename T>
particio<T>::particio(nat n) throw(error){

}

// Constructora per còpia, assignació i destructora.
template <typename T>
particio<T>::particio(const particio & p) throw(error){
}
template <typename T>
particio<T> & particio<T>::operator=(const particio & p) throw(error){
  return *this;
}
//Metode auxiliar factor equilibri
template <typename T>
nat particio<T>::factor_eq(node *n){
    if (n == NULL) return 0;
    return altura_max(n->_esq) - altura_max(n->_dret);
}

template <typename T>
particio<T>::~particio() throw(){}
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

// Metode auxiliar d'afegir
template <typename T>
typename particio<T>::node* particio<T>::insereix_avl(node *n, const T &k){
    //BST
    if (n == NULL){
        n_elem++;
        return new node(k);
    }
    else{
        if (k < n->_k) {
            n->_esq = insereix_avl(n->_esq, k;
        }else if (k > n->_k) {
            n->_dret = insereix_avl(n->_dret, k);
        }
    }
    //Actualització altura maxima del node anterior
    n->alt_max = 1 + max(altura_max(n->_esq),altura_max(n->_dret));
    // Factor d'equilibri del node anterior pero comprovar si esta desequilibrat
    equilibri = factor_eq(n);
    // casos:


return n;
}

// Afegeix un nou element a la particio. Aquest nou element formarà ell sol
// un nou grup. En cas que l'element ja estigués present a la partició llavors
// no es modifica la partició. Es produeix un error si la particio ja té el
// número màxim d'elements abans d'afegir aquest nou.
template <typename T>
void particio<T>::afegir(const T &x) throw(error){
    if(n_max == n_elem) throw error(ParticioPlena);
    else _arrel = insereix_avl(_arrel, x);
}

// Uneix els dos grups als quals pertanyen aquests dos elements. Si tots dos
// elements ja pertanyien al mateix grup no fa res.
// Es produeix un error si algun dels elements no pertany a la partició.
template <typename T>
void particio<T>::unir(const T & x, const T & y) throw(error){

}

// Retorna si els elements x i y pertanyen al mateix grup.
// Es produeix un error si algun dels dos elements no pertany a la partició.
template <typename T>
bool particio<T>::mateix_grup(const T & x, const T & y) const throw(error){
  return true;
}

// Retorna el número de grups que té la particio.
template <typename T>
nat particio<T>::size() const throw(){
  return size;
}

// Retorna el número d'elements que té la particio.
template <typename T>
nat particio<T>::num_elements() const throw(){
  return n_elem;
}

// Retorna el número màxim d'elements que pot tenir la particio.
template <typename T>
nat particio<T>::num_maxim() const throw(){
  return n_max;
}
