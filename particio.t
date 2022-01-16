#include "particio.hpp"


// Construeix una partició amb n elements com a màxim.
/* COST: O(1) Perquè només hi han assignacions*/
template <typename T>
particio<T>::particio(nat n) throw(error){
    /*PRE: Ens passen per paràmetre el nùmero màxim d'elements que pot tenir la partició*/
    /*POST: S'inicialitzen els atributs privats*/

    n_max = n;
    n_elem = 0;
    max_grup = 0;
    _arrel = NULL;
}

//Mètode auxiliar per copiar tots els representants després de la unió
/* COST: O(n_elem) ja que el pitjor dels casos és quan fa la funció find i aquesta té cost O(n_elem), que seria equivalent a dir
cost O(n) */
template <typename T>
   void particio<T>::copia_repre(node* p, node* a, node* auxiliar){
       /*PRE: Ens passen tres punters a nodes p, a i auxiliar, el primer pertany a la partició p que ens donen
        al mètode còpia de partició i els altres dos pertanyen a la nostra partició*/
       /*POST: Fa la còpia de tots els representants amb les unions que s'hagin fet fins al moment*/

        if(a!=NULL and p!=NULL){
            node* represent = find(p);
            node *repreA=buscanode(auxiliar,represent->_k);
            a->representant=repreA;
            copia_repre(p->_esq, a->_esq, auxiliar);
            copia_repre(p->_dret, a->_dret, auxiliar);
        }
    }
//Mètode auxiliar còpia
// La còpia es fa seguint un recorregut en preordre.
/* COST: O(log(n_elem)) ja que tant en les crides recursives com a la crida de la funció destrueix_particio, hi ha
un cost de O(log(n_elem)), per tant, aquest seria el seu cost */
template <typename T>
typename particio<T>::node* particio<T>::copia_particio(node* p) {
    /*PRE: Ens passen un punter a node p el qual pertany a la partició p que ens donen
     al mètode còpia de partició*/
    /*POST: Còpia la informació del node* p a un node* aux */

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
// Constructora per còpia
/* COST: O(n_elem) ja que el pitjor dels casos és quan fa la funció copia_repre i aquesta té cost O(n_elem), que seria equivalent a dir
cost O(n) */
template <typename T>
particio<T>::particio(const particio & p) throw(error){
    /*PRE: Ens passen per paràmetre una partició p. */
    /*POST: Tots els elements de la partició passada per paràmetre els copiem sobre la nostra*/

    n_max = p.n_max;
    n_elem = p.n_elem;
    max_grup = p.max_grup;
    _arrel = copia_particio(p._arrel);
    copia_repre(p._arrel, _arrel, _arrel);
}

//Assignació
/* COST: O(log(n_elem)) ja que el pitjor cas és la crida a la funció de destrueix_particio, on té un cost
O(log(n_elem)) que seria el mateix que dir cost O(log(n))*/
template <typename T>
particio<T> & particio<T>::operator=(const particio & p) throw(error){
    /*PRE: Ens passen per paràmetre una partició p */
    /*POST: Eliminem tots els elements de la nostra partició per després assignar-li tots els elements de la partició
    passada per paràmetre. */

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

//Mètode auxiliar destructora
// La destrucció es fa seguint un recorregut en postordre.
/* COST: O(log(n_elem)) ja que va recorrent la meitat de l'avl a cada crida recursiva, que seria el mateix que dir cost O(log(n))*/
template <typename T>
void particio<T>::destrueix_particio(node* p) {
    /*PRE: Ens passen per paràmetre en node inicial de la partició que volem eliminar*/
    /*POST: De forma recursiva es van eliminant tots els nodes de l'arbre*/

  if (p != NULL) {
    destrueix_particio(p -> _esq);
    destrueix_particio(p -> _dret);
    delete p;
  }
}
//Destructora.
/* COST: O(log(n_elem)) ja que només fa la crida a la funció auxiliar i agafa el seu cost, que seria el mateix que dir cost O(log(n))*/
template <typename T>
particio<T>::~particio() throw(){
    /*PRE: Cert*/
    /*POST: Destrueix la partició en la seva totalitat*/

    destrueix_particio(_arrel);
}


//Mètode auxiliar factor equilibri
/* COST: O(1) ja que la crida a la funció altura_max és cost O(1), i encara que es facin dues crides, s'ha d'agafar el màxim
i com costen el mateix el resultat es O(1)*/
template <typename T>
nat particio<T>::factor_eq(node *n){
    /*PRE: Ens passen un punter a node n que ve donat de la funció insereix_avl*/
    /*POST: Retorna la diferència entre altures màximes dels fills esquerres i fills drets, si és 0 és
    que està en equilibri*/

    if (n == NULL) return 0;
    return altura_max(n->_esq) - altura_max(n->_dret);
}
//Mètode auxiliar max:
/* COST: O(1) perquè es fa una simple comparació com si fos un if */
template <typename T>
nat particio<T>::max(nat a, nat b){
    /*PRE: Ens passen per paràmetre dos elements de tipus nat*/
    /*POST: Retorna l'element màxim entre els dos nats a i b*/

    return (a > b)? a : b;
}
//Mètode auxiliar altura_max: retorna la clau màxima de la partició
/* COST: O(1) Ja que només fa un if en el pitjor dels casos*/
template <typename T>
nat particio<T>::altura_max(node *n){
    /*PRE: Ens passen per paràmetre un node de la partició */
    /*POST: Retorna l'altura màxima a la que està aquest node agafant la info del struct*/

    if (n == NULL) return 0;
    return n->alt_max;
}
//Mètode auxiliar per crear un nou node
/* COST: O(1) ja que es fan únicament assignacions*/
template <typename T>
typename particio<T>::node* particio<T>:: newNode(T k){
    /*PRE: Ens passen un tipus T k que fa referència a la clau que ha de tenir el nou node*/
    /*POST: Retorna un nou node amb tota la seva informació corresponent*/

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


//Girar a la dreta el subarbre arrelat amb y
/* COST: O(1) ja que es criden a les funcions de max i altura_max les quals tenen O(1), per tant, seguint
la regla del màxim cost, aquesta funció és O(1)*/
template <typename T>
typename particio<T>::node* particio<T>::rightRotate(node *y){
    /*PRE: Ens passen un punter a node y que ens ve donat per la funció insereix_avl*/
    /*POST: Retorna una nova arrel després d'haver fet la rotació pertinent i actualitzar
    les altures*/

    node *x = y->_esq;
    node *aux = x->_dret;

    //Fa la rotació
    x->_dret = y;
    y->_esq = aux;

    //Actualitza les altures
    y->alt_max = max(altura_max(y->_esq),
                    altura_max(y->_dret)) + 1;
    x->alt_max = max(altura_max(x->_esq),
                    altura_max(x->_dret)) + 1;

    return x;
}
//Girar a la esquerra el subarbre arrelat amb x
/* COST: O(1) ja que es criden a les funcions de max i altura_max les quals tenen O(1), per tant, seguint
la regla del màxim cost, aquesta funció és O(1)*/
template <typename T>
typename particio<T>::node* particio<T>::leftRotate(node *x){
  /*PRE: Ens passen un punter a node x que ens ve donat per la funció insereix_avl*/
  /*POST: Retorna una nova arrel després d'haver fet la rotació pertinent i actualitzar
  les altures*/

    node *y = x->_dret;
    node *aux = y->_esq;

    //Fa la rotació
    y->_esq = x;
    x->_dret = aux;

    //Actualitza les altures
    x->alt_max = max(altura_max(x->_esq),
                    altura_max(x->_dret)) + 1;
    y->alt_max = max(altura_max(y->_esq),
                    altura_max(y->_dret)) + 1;

    return y;
}

// Mètode auxiliar d'afegir
/* COST: O(log(n_elem)) ja que el pitjor cas és si entra al if per recorre una part de l'avl, el que suposaria un
cost de O(log(n)) */
template <typename T>
typename particio<T>::node* particio<T>::insereix_avl(node *n, const T &k){
    /*PRE: Ens passen un punter a node n que ens ve de la funció afegir i un tipus T
    equivalent a la clau del node que volem afegir a l'AVL*/
    /*POST: Retorna l'AVL amb el nou element introduit*/

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

    //Actualització altura màxima del node anterior
    nat i = altura_max(n->_esq);
    nat j = altura_max(n->_dret);
    n->alt_max = 1 + max(i,j);

    // Factor d'equilibri del node anterior pero comprovar si esta desequilibrat
    int equilibri = factor_eq(n);

    // Casos si està descompensat

    // Esuqerra esquerra cas
    if (equilibri > 1 && k < n->_esq->_k)
        return rightRotate(n);

    // Dreta dreta cas
    if (equilibri < -1 && k > n->_dret->_k)
        return leftRotate(n);

    // Esquerra dreta cas
    if (equilibri > 1 && k > n->_esq->_k)
    {
        n->_esq = leftRotate(n->_esq);
        return rightRotate(n);
    }

    // Dreta esquerra cas
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

/* COST: O(log(n_elem)) ja que és fa una crida a la funció de insereix_avl i s'agafa el seu cost*/
template <typename T>
void particio<T>::afegir(const T &x) throw(error){
    /*PRE: Ens passen per paràmetre un nou element per introduir a la partició. */
    /*POST: Un nou element és introduït de forma recursiva passant-li per paràmetre
    el node inicial de la partició i el nou element que volem introduïr.*/

    _arrel = insereix_avl(_arrel, x);
}

//metode si existeix o no l'element
/* COST: O(log(n_elem))ja que va recorrent la meitat de l'AVL a cada crida recursiva, que seria el mateix que dir cost O(log(n))*/
template <typename T>
bool particio<T>:: existeix(node *n, T e, bool trobat) const throw(){
    /*PRE: Ens passen per paràmetre el node inicial per recórrer l'arbre, l'element que volem buscar i finalment
    un booleà inicialitzat a false per saber si existeix o no l'element.*/
    /*POST: Retorna true o false si l'element s'ha trobat o no. En cas que no s'hagi trobat significa que
    no existeix dins de la partició.*/

    if(n != NULL)
    {
        if(n -> _k == e) trobat = true;
        trobat = existeix(n->_esq,e,trobat);
        trobat = existeix(n->_dret,e,trobat);
    }
    return trobat;
}

/* COST: O(n_elem) ja que en el pitjor dels casos recorrem tot l'arbre per trobar el representant de n*/
template <typename T>
typename particio<T>::node* particio<T>:: find(node *n)const throw(error){
    /*PRE: Ens passen un punter a node n que ve donat per la funció unir*/
    /*POST: Retorna el punter al node representant de n*/

    /* COST: O(n_elem) ja que en el pitjor dels casos recorrem tot l'arbre per trobar el representant de n*/
    while(n != n->representant){
        /*INV: Va recorrent l'arbre buscant per tots els nodes el representant del node passat per paràmetre*/
        n = n->representant;
    }
    return n;
}

/* COST: O(log(n_elem)) ja que va recorrent l'AVL fent esquerra o dreta*/
template <typename T>
typename particio<T>::node* particio<T>::buscanode(node *n, T e) const throw(){
    /*PRE: Ens passen per paràmetre el punter del node inicial de la partició i un element d'aquesta*/
    /*POST: Retorna el punter node dins de la partició on es troba l'element passat per paràmetre*/

    /* COST: O(log(n_elem)) ja que va recorrent el AVL fent esquerra o dreta*/
    while(n != NULL){
         /*INV: Mentre que el punter actual no apunti a NULL, va fent un recorregut postordre, tenint en compte que un AVL
        va mirant si el valor clau de l'element és més gran o més petit dins d'un arbre equilibrat. Si és més gran se n'anirà cap
        a la dreta i si és més petit se n'anirà cap a l'esquerra.*/
        if(e > n->_k){
            n = n->_dret;
        }else if(e < n->_k){
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

/* COST: O(n_elem) ja que el pitjor dels casos és quan fa la funció find i aquesta té cost O(n_elem), que seria equivalent a dir
cost O(n) */
template <typename T>
void particio<T>::unir(const T & x, const T & y) throw(error){
    /*PRE: Ens passen dos tipus T x i y que representen els dos elements que volem unir*/
    /*POST: Fa la unió d'aquests dos elements de la partició*/

    if(!existeix(_arrel,x,false) || !existeix(_arrel,y,false)) throw error(ElemInexistent);
    else{
        node *nx = buscanode(_arrel, x);     //node de x
        node *ny = buscanode(_arrel, y);    // node de y
        node* rx = find(nx);  //mira si l'element hi es al AVL / u representant de x
        node* ry = find(ny);  //mira si l'element hi es al AVL / v representant de y
        if(rx->_k != ry->_k){
            int cx,cy;
            cx = rx->fills;       //conta els fills del node x
            cy = ry->fills;      //conta els fills del node y
            if(cx > cy){
                ry -> representant = rx -> representant;
                cy = cy+cx;
                ry->fills = cy;
            }
            else if(cx < cy){
                rx -> representant = ry -> representant;
                cx = cy+cx;
                rx->fills = cx;
            }else{
                ry -> representant = rx -> representant;
                cy = cy+cx;
                ry->fills = cy;
            }
            max_grup--;
        }
    }
}

// Retorna si els elements x i y pertanyen al mateix grup.
// Es produeix un error si algun dels dos elements no pertany a la partició.

/* COST: O(n_elem) ja que el pitjor dels casos és quan fa la funció find i aquesta té cost O(n_elem), que seria equivalent a dir
cost O(n) */
template <typename T>
bool particio<T>::mateix_grup(const T & x, const T & y) const throw(error){
    /*PRE: Ens passen per paràmetre dos elements de tipus T */
    /*POST: Retorna true o false segons si aquests dos elements pertanyen al mateix grup*/

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

// Retorna el número de grups que té la particio.
/* COST: O(1) ja que retorna directament el valor de max_grup*/
template <typename T>
nat particio<T>::size() const throw(){
    /*PRE: Cert */
    /*POST: Retorna la quantitat de grups que conté la partició*/

    return max_grup;
}

// Retorna el número d'elements que té la particio.
/* COST: O(1) ja que retorna directament el valor de n_elem*/
template <typename T>
nat particio<T>::num_elements() const throw(){
    /*PRE: Cert */
    /*POST: Retorna el nombre d'elements que hi ha a partició*/

  return n_elem;
}

// Retorna el número màxim d'elements que pot tenir la particio.
/* COST: O(1) ja que retorna directament el valor de n_max*/
template <typename T>
nat particio<T>::num_maxim() const throw(){
    /*PRE: Cert */
    /*POST: Retorna el nombre màxim d'elements que pot contenir la partició*/

  return n_max;
}
