#include "particio.hpp"
#include<iostream>
using namespace std;



////////////////////// CONSTRUCTORA ////////////////
// Construeix una particio amb n elements com a màxim.
template <typename T>
particio<T>::particio(nat n) throw(error){
    n_max = n;
    n_elem = 0;
    max_grup = 0;
    _arrel = NULL;
}
////////////////////// CONSTRUCTORA COPIA ////////////////
//Metode auxiliar per copiar tots els representants després de la unió

template <typename T>
   void particio<T>::copia_repre(node* p, node* a, node* auxiliar){
        if(a!=NULL and p!=NULL){
            node* represent = find(p); //busca representante de p._arrel
            node *repreA=buscanode(auxiliar,represent->_k); //Busca el representante de antes en _arrel
            a->representant=repreA; //asigna a _arrel el repre encontrado
            copia_repre(p->_esq, a->_esq, auxiliar);
            copia_repre(p->_dret, a->_dret, auxiliar);
        }
    }
//Metode auxiliar copia
// La còpia es fa seguint un recorregut en preordre.
template <typename T>
typename particio<T>::node* particio<T>::copia_particio(node* p) {
  node* aux = NULL;
  if (p != NULL) {
    aux = new node;
    try {
      aux -> _k = p -> _k;
      aux -> alt_max = p -> alt_max;
      aux -> fills = p -> fills;
      aux -> _esq = aux -> _dret = NULL;
      aux -> representant = NULL;
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
    n_max = p.n_max;
    n_elem = p.n_elem;
    max_grup = p.max_grup;
    _arrel = copia_particio(p._arrel);
    copia_repre(p._arrel, _arrel, _arrel);
}
////////////////////// ASSIGNACIÓ ////////////////
template <typename T>
particio<T> & particio<T>::operator=(const particio & p) throw(error){

    if(this != &p){
        particio<T> tmp(p);
        destrueix_particio(_arrel);
        n_max = p.n_max;
        n_elem = p.n_elem;
        max_grup = p.max_grup;
        _arrel = tmp._arrel;
        tmp._arrel = NULL;
    }
    return *this;
}
////////////////////// DESTRUCTORA ////////////////
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
////////////////////// AFEGIR ////////////////
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
    node* n = new node;
    n -> _k = k;
    n -> _esq = NULL;
    n -> _dret = NULL;
    n -> alt_max = 1;
    n -> fills = 1;
    n -> representant = n;
    max_grup++;
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
        if(n_max == n_elem ) throw error(ParticioPlena);
        else return newNode(k);
    }
    else{
      if(k != n->_k){
        if(n_max == n_elem ) throw error(ParticioPlena);
        else if (k < n->_k) {
            n->_esq = insereix_avl(n->_esq, k);
        }else if (k > n->_k) {
            n->_dret = insereix_avl(n->_dret, k);
        }
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

return n;
}

// Afegeix un nou element a la particio. Aquest nou element formarà ell sol
// un nou grup. En cas que l'element ja estigués present a la partició llavors
// no es modifica la partició. Es produeix un error si la particio ja té el
// número màxim d'elements abans d'afegir aquest nou.
template <typename T>
void particio<T>::afegir(const T &x) throw(error){
    _arrel = insereix_avl(_arrel, x);
}
////////////////////// UNIR ////////////////
//metode si existeix o no l'element
template <typename T>
bool particio<T>:: existeix(node *n, T e, bool trobat) const throw(){
    if(n != NULL)
    {
        if(n -> _k == e) trobat = true;
        trobat = existeix(n->_esq,e,trobat);
        trobat = existeix(n->_dret,e,trobat);
    }
    return trobat;
}
//PREORDRE HOME JAAAAAAAAAA
template <typename T>
void particio<T>:: preOrder(node *n) const throw()
{
    if(n != NULL)
    {
        cout << n->_k<< " ";
        preOrder(n->_esq);
        preOrder(n->_dret);
    }
}
//Metode auxiliar retorna elements en format preOrdre
template <typename T>
typename particio<T>::node* particio<T>:: find(node *n)const throw(error){    //Busca si e és un representant
    //Es busca el pare del element donat
    while(n != n->representant){
        n = n->representant;
    }
    return n;
}
//Metode que busca el node pare per després contar els fills
template <typename T>
typename particio<T>::node* particio<T>::buscanode(node *n, T e) const throw(){
    while(n != NULL){
        //cout<<"n->_k*: "<<n->_k<<endl;
        if(e > n->_k){  //derecha
            n = n->_dret;
        }else if(e < n->_k){ //izq
            n = n->_esq;
        }else{
            return n;
        }
    }
    return n;
}
// Uneix els dos grups als quals pertanyen aquests dos elements. Si tots dos
// elements ja pertanyien al mateix grup no fa res.
// Es produeix un error si algun dels elements no pertany a la partició.
template <typename T>
void particio<T>::unir(const T & x, const T & y) throw(error){
    if(!existeix(_arrel,x,false) || !existeix(_arrel,y,false)) throw error(ElemInexistent);
    else{
        node *nx = buscanode(_arrel, x);     //node de x
        node *ny = buscanode(_arrel, y);    // node de y
        node* rx = find(nx);  //mira si l'element hi es al AVL / u representant de x
        //cout<<endl;
        node* ry = find(ny);  //mira si l'element hi es al AVL / v representant de y
        //cout<<"RX: "<<rx<<" RY: "<<ry<<endl;
        if(rx->_k != ry->_k){
            int cx,cy;
            //cout<<"REPRESENTANT NX: "<<rx -> representant -> _k<<endl;
            //cout<<"REPRESENTANT NY: "<<ry -> representant -> _k<<endl;
            cx = rx->fills;       //conta els fills del node x
            cy = ry->fills;      //conta els fills del node y
            //cout<<"CX: "<<cx<<" CY: "<<cy<<endl;
            if(cx > cy){ //unim els nodes de cy a cx
                ry -> representant = rx -> representant;
                cy = cy+cx;
                ry->fills = cy;
            }
            else if(cx < cy){ //unim els nodes de cx a cy
                rx -> representant = ry -> representant;
                cx = cy+cx;
                rx->fills = cx;
            }else{ //ens dona igual (escollir un)
                ry -> representant = rx -> representant;
                cy = cy+cx;
                ry->fills = cy;
            }
            max_grup--;
        }
    }
}
////////////////////// MATEIX GRUP ////////////////
// Retorna si els elements x i y pertanyen al mateix grup.
// Es produeix un error si algun dels dos elements no pertany a la partició.
template <typename T>
bool particio<T>::mateix_grup(const T & x, const T & y) const throw(error){
    bool trobat = false;
    if(!existeix(_arrel,x,false) || !existeix(_arrel,y,false)) throw error(ElemInexistent);
    else{
        node *nx = buscanode(_arrel, x);     //node de x
        node *ny = buscanode(_arrel, y);    // node de y
        node* rx = find(nx);  //mira si l'element hi es al AVL / u representant de x
        node* ry = find(ny);  //mira si l'element hi es al AVL / u representant de x
        if( rx -> _k == ry -> _k ) trobat = true;
    }
    return trobat;
}
////////////////////// MAXIM GRUP ////////////////
// Retorna el número de grups que té la particio.
template <typename T>
nat particio<T>::size() const throw(){
    return max_grup;
}
//////////////////////  NUM Elements ////////////////
// Retorna el número d'elements que té la particio.
template <typename T>
nat particio<T>::num_elements() const throw(){
  return n_elem;
}
//////////////////////  NUM MAXIM ////////////////
// Retorna el número màxim d'elements que pot tenir la particio.
template <typename T>
nat particio<T>::num_maxim() const throw(){
  return n_max;
}
