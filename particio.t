#include "particio.hpp"
#include<iostream>
using namespace std;



////////////////////// CONSTRUCTORA ////////////////
// Construeix una particio amb n elements com a màxim.
template <typename T>
particio<T>::particio(nat n) throw(error){
    n_max = n;
    n_elem = 0;
    _arrel = NULL;

}
////////////////////// CONSTRUCTORA COPIA ////////////////
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
////////////////////// ASSIGNACIÓ ////////////////
template <typename T>
particio<T> & particio<T>::operator=(const particio & p) throw(error){
    particio<T> tmp(p);
    node* aux = _arrel;
    _arrel = tmp._arrel;
    tmp._arrel = aux;
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
bool particio<T>:: existeix(node *n, T e, bool trobat){
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
        cout << n->_k << " ";
        preOrder(n->_esq);
        preOrder(n->_dret);
    }
}


//Metode auxiliar retorna elements en format preOrdre

template <typename T>
T particio<T>:: find(node *n,const T &e, T pare)const throw(error){    //Busca si e és un representant
    //Es busca el pare del element donat
    preOrder(n);
    cout<<endl;
    if (n != NULL){
        if (n->_k == e) {
            cout<<"PARE: "<<pare<<endl;
            return pare;
        }else{
            pare = find(n->_esq, e, n->_k);
            pare = find(n->_dret, e, n->_k);
        }
    }
    return pare;
}

//Metode que busca el node pare per després contar els fills
template <typename T>
typename particio<T>::node* particio<T>::buscanode(node *n, T e){
    node *pare;
    if(n != NULL){
        if(n -> _k == e){
            pare = n;
            return pare;
        }
        n->_esq = buscanode(n->_esq, e);
        n->_dret = buscanode(n->_dret, e);
    }
    return n;
}

//Metode auxiliar comptador de fills
template <typename T>
int particio<T>::contfills(node *n, int c){
    if(n != NULL){
        c++;
        c = contfills(n->_esq, c);
        c = contfills(n->_dret, c);
    }
    return c;
}
//Metode inserir ( unir en la sombra)
template <typename T>
void particio<T>::inserir(node *n1, node *n2){  //s'insereix a N1!!!!!
    if(n2 != NULL){
        n1 = insereix_avl(n1, n2 ->_k);
        inserir(n1,n2->_esq);
        inserir(n1,n2->_dret);
    }

}

// Uneix els dos grups als quals pertanyen aquests dos elements. Si tots dos
// elements ja pertanyien al mateix grup no fa res.
// Es produeix un error si algun dels elements no pertany a la partició.

template <typename T>
void particio<T>::unir(const T & x, const T & y) throw(error){
    if(!existeix(_arrel,x,false) || !existeix(_arrel,y,false)) throw error(ElemInexistent);
    else{
        T u = find(_arrel,x,-1);  //mira si l'element hi es al AVL / u representant de x
        cout<<endl;
        T v = find(_arrel,y,-1);  //mira si l'element hi es al AVL / v representant de y
        cout<<"U: "<<u<<" V: "<<v<<endl;
        if(u != v){
            int cu,cv;
            node *pu = buscanode(_arrel, u);
            node *pv = buscanode(_arrel, v);
            cu = contfills(pu,0);
            cv = contfills(pv,0);
            cout<<"CU: "<<cu<<" CV: "<<cv<<endl;
            if(cu > cv){ //unim els nodes de cu a cv
                inserir(pu,pv);
                //destrueix_particio(pu);
            }
            else if(cu < cv){ //unim els nodes de cv a cu
                inserir(pv,pu);
                //destrueix_particio(pv);
            }else{ //ens dona igual (escollir un)
                inserir(pu,pv);
                //destrueix_particio(pu);
            }
            cout<<"UNIOOOOOOOOOOOOON"<<endl;
            preOrder(_arrel);
            cout<<endl;

        }
    }
}

////////////////////// MATEIX GRUP ////////////////
// Retorna si els elements x i y pertanyen al mateix grup.
// Es produeix un error si algun dels dos elements no pertany a la partició.

template <typename T>
bool particio<T>::mateix_grup(const T & x, const T & y) const throw(error){
    T u,v;
    u = find(_arrel,x,-1);
    v = find(_arrel,y,-1);
    if( u == v ) return true;
    else return false;
}

////////////////////// MAXIM GRUP ////////////////
//Metode auxiliar recorregur pares aka numero de GRUPS
template <typename T>
nat particio<T>:: n_grups(node *n, nat cont) const throw(){

    if (n != NULL) {
        //if(n->_esq != NULL || n->_dret != NULL){
            cont++;
        //}
        cont = n_grups(n->_esq,cont);
        cont = n_grups(n->_dret,cont);
    }
    return cont;
}
// Retorna el número de grups que té la particio.
template <typename T>
nat particio<T>::size() const throw(){
    return n_grups(_arrel,0);
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
