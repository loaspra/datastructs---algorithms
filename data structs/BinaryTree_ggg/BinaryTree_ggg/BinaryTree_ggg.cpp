#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

//ArrayList
template<typename E>
class ListaArreglo
{
private:
    int tamMax;//tamaño predeterminado
    int tamLista; //nro elementos ingresados hasta ahora
    int actual; //índice actual (equivalente al puntero actual en la lista enlazada)
    //Arreglo de elementos
    E* arreglo;
public:
    //Constructor
    ListaArreglo(int tamMax = 100) {
        this->tamMax = tamMax;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }

    //Destructor
    ~ListaArreglo() {
        delete[] this->arreglo;
    }

    void moverAInicio() {
        this->actual = 0;
    }

    void moverAlFinal() {
        this->actual = this->tamLista;
    }

    void siguiente() {
        if (this->actual < this->tamLista)
            this->actual++;
    }

    void anterior() {
        if (this->actual != 0) {
            this->actual--;
        }
    }

    void agregar(E elemento) {
        this->arreglo[this->tamLista++] = elemento;
    }

    void insertar(E elemento) {
        for (int i = tamLista; i > actual; i--) {
            this->arreglo[i] = this->arreglo[i - 1];
        }
        this->arreglo[actual] = elemento;
        this->tamLista++;
    }

    //Especial para la implementación del árbol
    void insertar(E elemento, int pos) {
        this->arreglo[pos] = elemento;
    }



    void limpiar() {
        delete[] this->arreglo;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }

    E eliminar() {
        E temp = this->arreglo[actual];
        for (int i = actual; i < this->tamLista - 1; i++) {
            this->arreglo[i] = this->arreglo[i + 1];
        }
        this->tamLista--;
        return temp;
    }

    int longitud() {
        return this->tamLista;
    }

    int posicionActual() {
        return this->actual;
    }

    void moverAPosicion(int pos) {
        if (pos >= 0 && pos < this->tamLista) {
            this->actual = pos;
        }
    }

    //Método útil para nuestro árbol
    void moverAPosicionSinRestriccion(int pos) {
        this->actual = pos;
    }

    E getValor() {
        return this->arreglo[this->actual];
    }
};


//Arbol Búsqueda Binaria
template<typename E>
class ArbolBinarioArreglo 
{
private:
    ListaArreglo<E>* lista;
    int tamMax; 

    void inicializacion() 
    {
        for (int i = 0; i < tamMax; i++) {
            this->lista->moverAPosicionSinRestriccion(i);
            this->lista->insertar(nullptr);
        }
    }

    int getHijoIzquierdo(int r) {
        return 2 * r + 1;
    }

    int getHijoDerecho(int r) {
        return 2 * r + 2;
    }
public:
    ArbolBinarioArreglo(int tamMax = 100) {
        this->tamMax = tamMax;
        this->lista = new ListaArreglo<E>(tamMax);
        //Inicialización
        inicializacion();
    }

    //Retornar el numero de registros en el arbol binario
    int longitud() {
        return this->lista->longitud();
    }



    void insertar(E e) {
        int hijo, r;
        this->lista->moverAInicio();
        r = this->lista->posicionActual();
        if (this->lista->getValor() == nullptr) {//Si raíz está libre
            this->lista->insertar(e, r);//ingreso e en la posición 0 que es la raíz
        }
        else {
            hijo = *e < *this->lista->getValor() ?
                this->getHijoIzquierdo(r) : this->getHijoDerecho(r);
            insertar(e, hijo);
        }
    }

    void insertar(E item, int nodo_actual) {
        int hijo, r;
        this->lista->moverAPosicionSinRestriccion(nodo_actual);
        r = this->lista->posicionActual();
        if (this->lista->getValor() == nullptr) {
            this->lista->insertar(item, nodo_actual);
        }
        else {
            hijo = *item < *this->lista->getValor() ?
                this->getHijoIzquierdo(r) : this->getHijoDerecho(r);
            insertar(item, hijo);
        }
    }

    int encontrar(E e) {
        int nodoActual = -1, hijo, r;
        this->lista->moverAInicio();
        r = this->lista->posicionActual();
        if (this->lista->getValor() != nullptr) {
            if (*e == *this->lista->getValor()) {
                nodoActual = this->lista->posicionActual();
            }
            else {
                hijo = *e < *this->lista->getValor() ?
                    this->getHijoIzquierdo(r) : this->getHijoDerecho(r);
                nodoActual = encontrar(e, hijo);
            }
        }
        return nodoActual;
    }

    int encontrar(E e, int nodo_actual) {
        int index = -1, hijo, r;
        this->lista->moverAPosicionSinRestriccion(nodo_actual);
        r = this->lista->posicionActual();
        if (this->lista->getValor() != nullptr) {
            if (*e == *this->lista->getValor()) {
                index = nodo_actual;
            }
            else {
                hijo = *e < *this->lista->getValor() ?
                    this->getHijoIzquierdo(r) : this->getHijoDerecho(r);
                index = encontrar(e, hijo);
            }
        }
        return index;
    }


    /*
    E remover (E e) {

    }*/

    //Reinicializar arbol binario
    void limpiar() {
        delete this->lista;
        this->lista = new ListaArreglo<E>(this->tamMax);
        inicializacion();
    }

    void reportarLinealmente() {
        int i = 0;
        this->lista->moverAInicio();
        for (; i < this->tamMax; lista->siguiente()) {
            if (lista->getValor()) {
                cout << "[" << i << "] = " << *lista->getValor() << endl;
            }
            i++;
        }
    }

    void pre_orden(int nodo_actual = 0) 
    {
        if (nodo_actual < this->tamMax) 
        {
            this->lista->moverAPosicionSinRestriccion(nodo_actual);
            if (this->lista->getValor() != nullptr) {
                cout << *this->lista->getValor() << endl;
                pre_orden(this->getHijoIzquierdo(nodo_actual));
                pre_orden(this->getHijoDerecho(nodo_actual));
            }
        }
    }
};




//--------------------------------------------------------------------
// Árboles con Nodos
//--------------------------------------------------------------------

//Clase Nodo para Binary Seahijo_deh Trees
template<typename Key, typename E>
class TNode 
{
public:
    Key* clave;
    E* valor;
    TNode* hijo_iz;
    TNode* hijo_de;

    TNode() 
    {
        valor = nullptr;
        clave = nullptr;
        hijo_iz = hijo_de = nullptr;
        valor = new E();
    }

    TNode(Key k, E value, TNode* left = nullptr, TNode* right = nullptr) {
        clave = new Key(k);
        valor = new E(value);
        hijo_iz = left;
        hijo_de = right;
    }

    ~TNode()     
    {
        this->hijo_iz = nullptr;
        this->hijo_de = nullptr;
        this->clave = nullptr;
        this->valor = nullptr;
    }

    E elemento() 
    {
        return this->valor;
    }

    void setValor(E e) 
    {
        this->valor = new E(e);
    }

    Key Clave() 
    { 
        return this->clave; 
    }

    void setClave(Key k) 
    { 
        clave = new Key(k); 
    }

    TNode* izquierda() 
    {
        return this->hijo_iz;
    }

    TNode* derecha() 
    {
        return this->hijo_de;
    }
};



template<typename Key, typename E>
class BST
{
private:
    int contarNodo; 
    void in_order_excluir(TNode<Key, E>* it, vector<TNode<Key, E>>& aux, Key k)
    {
        if (it != nullptr && it->clave != nullptr)
        {
            TNode<Key, E>* temp = it;
            in_order_excluir(temp->hijo_iz, aux, k);
            if (it->clave != nullptr && *it->clave != k)
                aux.push_back(*it);
            in_order_excluir(temp->hijo_de, aux, k);
        }
    }
    
    void in_order(TNode<Key, E>* it, vector<TNode<Key, E>*>& aux)
    {
        if (it != nullptr && it->clave != nullptr)
        {
            TNode<Key, E>* temp = it;
            in_order(temp->hijo_iz, aux);
            aux.push_back(it);
            in_order(temp->hijo_de, aux);
        }
    }
    
    TNode<Key, E>* balancear_(TNode<Key, E>* root, vector<TNode<Key, E>*> aux, int i, int f)
    {
        if (i > f)
            return nullptr;

        int medio = (i + f) / 2;
        TNode<Key, E>* nodo = aux[medio];
        nodo->hijo_iz = balancear_(nodo->hijo_iz, aux, i, medio - 1);
        nodo->hijo_de = balancear_(nodo->hijo_de, aux, medio + 1, f);
        return nodo;
    }

    TNode<Key, E>* balancear_(TNode<Key, E>* root, vector<TNode<Key, E>> aux, int i, int f)
    {
        if (i > f || ((i + f) / 2) >= aux.size())
            return nullptr;

        int medio = (i + f) / 2;
        TNode<Key, E>* nodo = new TNode<Key, E>(*aux[medio].clave, *aux[medio].valor, aux[medio].hijo_iz, aux[medio].hijo_de);
        nodo->hijo_iz = balancear_(nodo->hijo_iz, aux, i, medio - 1);
        nodo->hijo_de = balancear_(nodo->hijo_de, aux, medio + 1, f);
        return nodo;
    }


public:
    TNode<Key, E>* raiz;
    BST() 
    {
        this->raiz = nullptr;
        this->contarNodo = 0;
    }

    ~BST() 
    {
        this->raiz = nullptr;
    }

    void limpiar_(TNode<Key, E>* nodo)
    {
        if (nodo != nullptr)
        {
            limpiar_(nodo->hijo_de);
            limpiar_(nodo->hijo_iz);
            delete nodo;
        }
    }

    void limpiar()
    {
        limpiar_(this->raiz);
        this->raiz = nullptr;
        this->contarNodo = 0;
    }

    void insertar(Key k, E e) 
    {   
        if (this->raiz == nullptr)
        {
            this->raiz = new TNode<Key, E>(k, e);
        }            
        else
        {
            TNode<Key, E>* it;
            it = this->raiz;
            insertarAyuda(k, e, it);
        }
        this->contarNodo++;
    }

    void pre_order_print(TNode<Key, E>* it)
    {
        if (it != nullptr && it->clave != nullptr)
        {
            cout << *it->clave << "|" << *it->valor << endl;
            pre_order_print(it->hijo_iz);
            pre_order_print(it->hijo_de);
        }
    }

    void in_order_print(TNode<Key, E>* it)
    {
        if (it != nullptr && it->clave != nullptr)
        {
            in_order_print(it->hijo_iz);
            cout << *it->clave << "|" << *it->valor << endl;
            in_order_print(it->hijo_de);
        }
    }

    void pos_order_print(TNode<Key, E>* it)
    {
        if (it != nullptr && it->clave != nullptr)
            return;

        pos_order_print(it->hijo_iz);
        pos_order_print(it->hijo_de);
        cout << *it->clave << "|" << *it->valor << endl;
    }

    void balancear()
    {
        vector<TNode<Key, E>*> aux;
        in_order(this->raiz, aux);

        this->raiz = balancear_(this->raiz, aux, 0, aux.size() - 1);
    }

    E remover(Key k)
    {
        E re;
        TNode<Key, E>* nodo = this->raiz;
        TNode<Key, E>* aux = nodo;
        vector<TNode<Key, E>*> vec;
        bool direc;
        bool raiz = true;
        while (nodo != nullptr && nodo->clave != nullptr)
        {
            if (*nodo->clave > k)
            {
                aux = nodo;
                nodo = nodo->hijo_iz;
                direc = false;
                raiz = false;
            }
            else
            {
                if (*nodo->clave < k)
                {
                    aux = nodo;
                    nodo = nodo->hijo_de;
                    direc = true;
                    raiz = false;
                }
                else
                {
                    re = *nodo->valor;
                    in_order(nodo->hijo_iz, vec);
                    in_order(nodo->hijo_de, vec);

                    if (raiz)
                    {
                        this->raiz = balancear_(nodo, vec, 0, vec.size() - 1);
                        this->contarNodo--;
                        return re;
                    }
                    if (direc)
                    {
                        aux->hijo_de = balancear_(nodo, vec, 0, vec.size() - 1);
                    }
                    else
                    {
                        aux->hijo_iz = balancear_(nodo, vec, 0, vec.size() - 1);
                    }
                    this->contarNodo--;
                    return re;
                }
            }
        }
    }



    E remover_reor(Key k) 
    {
        TNode<Key, E> m;
        bool val = false;
        E hola;
        vector<TNode<Key, E>> aux;
        TNode<Key, E>* it = raiz;
        hola = *it->valor;
        in_order_excluir(this->raiz, aux, k);
        limpiar();
        this->raiz = balancear_(this->raiz, aux, 0, aux.size());
        return hola;
    }

    E removehijo_deualquiera() 
    {
        if (this->contarNodo == 0)
            return nullptr;
        return remover(*this->raiz->clave);
    }

    E encontrar(Key k, TNode<Key, E>* it)
    {
        if (*it->clave < k)
        {
            return encontrar(k, it->hijo_de);
        }
        else
        {
            if (*it->clave > k)
            {
                return encontrar(k, it->hijo_iz);
            }
            else
                return *it->valor;
        }
        return NULL;
    }

    int longitud() 
    {
        return this->contarNodo;
    }

    void insertarAyuda(Key k, E e, TNode<Key, E>* it, TNode<Key, E>* r, TNode<Key, E>* b, bool direccion);
};


template<typename Key, typename E>
void BST<Key, E>::insertarAyuda(Key k, E e, TNode<Key, E>* it, TNode<Key, E>* r, TNode<Key, E>* b, bool direccion)
{
    while (it != nullptr && it->clave != nullptr)
    {
        if (*it->clave < k)
        {
            insertarAyuda(k, e, it->hijo_de, it, true);
            return;
        }
        else
        {
            insertarAyuda(k, e, it->hijo_iz, it, false);
            return;
        }
    }
    if (direccion)
    {
        r->hijo_de = new TNode<Key, E>(k, e);
    }
    else
    {
        r->hijo_iz = new TNode<Key, E>(k, e);
    }
}

int main() 
{

    return 0;
}
