#include <iostream>
using namespace std;

template<typename E> class Lista {
private:
    void operator = (const Lista&) {} //Asignación
    Lista(const Lista&) {} // Copia de constructor
public:
    Lista() {} //Constructor por defecto
    virtual ~Lista() {} //destructor base

    //Limpiar contenidos desde la lista, para hacerla vacía
    virtual void limpiar() = 0;

    //Insertar un elemento al final de la lista
    //item: el elemento a ser insertado
    virtual void insertar(E item) = 0;

    //Agregar un elemento al final de la lista
    //item: el elemento a ser agregado
    virtual void agregar(E item) = 0;

    //Eliminar y retornar el elemento actual
    //retornar: el elemento que fue eliminado
    virtual E eliminar() = 0;

    // Modificar la posici'on actual al inicio de la lista
    virtual void moverAInicio() = 0;

    //Modificar la posición al final de la lista
    virtual void moverAlFinal() = 0;

    //Mover la posición actual un paso a la izquierda.
    //No cambia si ya est'a al inicio
    virtual void anterior() = 0;

    //Mover la posición actual un paso a la derecha.
    //No cambia si ya está al final
    virtual void siguiente() = 0;

    //Retornar: el número de elementos en la lista
    virtual int longitud() = 0;

    //Retornar: la posición del elemento actual
    virtual int posicionActual() = 0;

    //Modificar la posición actual
    //pos: la posición para hacer actual
    virtual void moverAPosicion(int pos) = 0;

    //Retornar: el elemento actual
    virtual E getValor() = 0;
};


//ArrayList
template<typename E>
class ListaArreglo : public Lista<E> {
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


template <typename Key, typename E>
class Diccionario {
private:
    //void operator = (const Diccionario&) {}
    //Diccionario(const Diccionario&) {}

public:
    Diccionario() {} //Constructor
    virtual ~Diccionario() {} //Base destructor

    //Reinicializar Diccionario
    virtual void limpiar() = 0;

    //Insertar un registro
    //k: la clave para el registro fue insertada
    //e: El registro siendo insertado
    virtual void insertar(Key K, E e) = 0;

    //Remover y retornar un registro
    //k: la clave para el registro a ser removido
    //Retornar: Un registro maquina. Si muchos registros //se empatan con "K", remover uno arbitrario.
    //Retornar NULL si ningun registro con la clave "k"
    //Existe
    //virtual E remover (Key K) = 0;

    //remover y retornar un registro arbitrario del diccionario.
    //retornar: el registro removido, o o NULL si no existe
    //virtual E removerCualquiera() = 0;

    //Return: un registro maquina "k" (NULL si no existe)
    //Si multiples registros se empatan, retornar uno de ellos arbitrariamente
    //K: la clave del registro a encontrar
    //virtual E encontrar( Key K) =0;

    //Retornar el numero de registros en el diccionario
    virtual int longitud() = 0;
};






template <typename E>
class ArbolBinario {
private:
public:
    ArbolBinario() {} //Constructor
    //virtual ~ArbolBinario(){} //Base destructor

    virtual void insertar(E e) = 0;

    //virtual void remover (E e) = 0;
    //Reinicializar arbol binario
    virtual void limpiar() = 0;

    virtual int encontrar(E eK) = 0;

    //Retornar el numero de registros en el arbol binario
    virtual int longitud() = 0;
};


//Arbol Búsqueda Binaria
template<typename E>
class ArbolBinarioArreglo : ArbolBinario<E> {
private:
    ListaArreglo<E>* lista;
    int tamMax; //el tamaño del arreglo fijo

    void inicializacion() {
        //Inicialización
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

    //Parámetro por defecto
    void pre_orden(int nodo_actual = 0) {
        if (nodo_actual < this->tamMax) {//validar no exceder los límites del arreglo
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
//Clase abstracta de un nodo árbol binario
template<typename E> class NodoBin {
public:
    virtual ~NodoBin() {}//destructor
    //Retornar el valor del nodo
    virtual E elemento() = 0;
    //Modificar el valor del nodo
    virtual void setElemento(E) = 0;
    //Retornar el nodo hijo izquierdo
    virtual NodoBin* izquierda() = 0;
    //Modificar el nodo hijo izquierdo
    virtual void setIzquierda(NodoBin*) = 0;
    //Retornar el nodo hijo derecho
    virtual NodoBin* derecha() = 0;
    //Modificar el nodo hijo derecho
    virtual void setDerecha(NodoBin*) = 0;
};

//Clase Nodo para Binary Search Trees
template<typename Key, typename E>
class BSTNode : public NodoBin<E> {
private:
    Key k; //clave del nodo
    E it; //valor del nodo
    BSTNode* lc;//puntero al hijo izquierdo
    BSTNode* rc;//puntero al hijo derecho
public:
    //Constructor: sin valores iniciales
    BSTNode() {
        lc = rc = NULL;
    }

    //Constructor: con valores iniciales
    BSTNode(Key k, E e, BSTNode* l = NULL, BSTNode* r = NULL) {
        this->k = k;
        this->it = e;
        this->lc = l;
        this->rc = r;
    }

    //Destructor
    ~BSTNode() {
    }

    //Retornar el valor del nodo
    E elemento() {
        return this->it;
    }

    //Modificar el valor del nodo
    void setElemento(E e) {
        this->it = e;
    }

    //Retornar la clave del nodo
    Key clave() { return this->k; }

    //Modificar la clave del nodo
    void setClave(Key k) { this->k = k; }

    //Retornar el nodo hijo izquierdo
    BSTNode* izquierda() {
        return this->lc;
    }

    //Modificar el nodo hijo izquierdo
    void setIzquierda(NodoBin<E>* b) {
        this->lc = (BSTNode*)b;
    }

    //Retornar el nodo hijo derecho
    BSTNode* derecha() {
        return this->rc;
    }

    //Modificar el nodo hijo derecho
    void setDerecha(NodoBin<E>* b) {
        this->rc = (BSTNode*)b;
    }
};



template<typename Key, typename E>
class BST : public Diccionario<Key, E> {
private:
    BSTNode<Key, E>* raiz; //raíz del Diccionario Arbol BST
    int contarNodo; //número de nodos en el BST

    //Prototipo de Métodos de apoyo o complementarios
    BSTNode<Key, E>* insertarAyuda(Key K, E e, BSTNode<Key, E>* raiz);
    void limpiarAyuda(BSTNode<Key, E>* raiz);
    void imprimirAyuda(BSTNode<Key, E>* raiz, int nivel);
public:
    //Constructor: Inicialización de atributos
    BST() {
        this->raiz = NULL;
        this->contarNodo = 0;
    }

    //Destructor
    ~BST() {
        this->limpiarAyuda(this->raiz);
    }

    //Reinicializar Diccionario
    void limpiar() {
        this->limpiarAyuda(this->raiz);
        this->raiz = NULL;
        this->contarNodo = 0;
    }

    //Insertar un registro
    //k: la clave para el registro fue insertada
    //e: El registro siendo insertado
    void insertar(Key K, E e) {
        this->raiz = insertarAyuda(K, e, raiz);
        this->contarNodo++;
    }

    //Remover y retornar un registro
    //k: la clave para el registro a ser removido
    //Retornar: Un registro maquina. Si muchos registros //se empatan con "K", remover uno arbitrario.
    //Retornar NULL si ningun registro con la clave "k"
    //Existe
    E remover(Key K) {

    }

    //remover y retornar un registro arbitrario del diccionario.
    //retornar: el registro removido, o o NULL si no existe
    E removerCualquiera() {

    }

    //Return: un registro maquina "k" (NULL si no existe)
    //Si multiples registros se empatan, retornar uno de ellos arbitrariamente
    //K: la clave del registro a encontrar
    E encontrar(Key K) {

    }

    //Retornar el numero de registros en el diccionario
    int longitud() {
        return this->contarNodo;
    }

    //Imprime el contenido del TreeMap
    void imprimir() {
        if (this->raiz == NULL) {
            cout << "TreeMap vacío";
        }
        else {
            imprimirAyuda(raiz, 0);
        }
    }
};



//Sobrecargar método insertar que trabaja recursivamente
template<typename Key, typename E>
BSTNode<Key, E>* BST<Key, E>::insertarAyuda(Key K, E e, BSTNode<Key, E>* raioz) {
    if (raioz == NULL) {//la raíz está libre
        return new BSTNode<Key, E>(K, e, NULL, NULL);
    }

    if (K < raioz->clave()) {
        raioz->setIzquierda(insertarAyuda(K, e, raioz->izquierda()));
    }
    else {
        raioz->setDerecha(insertarAyuda(K, e, raioz->derecha()));
    }
    return this->raiz;
}

template<typename Key, typename E>
void BST<Key, E>::limpiarAyuda(BSTNode<Key, E>* raioz) {
    if (raioz == NULL) return;
    limpiarAyuda(raioz->izquierda());
    limpiarAyuda(raioz->derecha());
    delete raioz;
}


//Recorrido in-orden
template<typename Key, typename E>
void BST<Key, E>::imprimirAyuda(BSTNode<Key, E>* raioz, int nivel) {
    if (raioz == NULL) return;
    imprimirAyuda(raioz->izquierda(), nivel + 1);
    cout << *raiz->clave() << "\n";
    imprimirAyuda(raioz->derecha(), nivel + 1);
}



int main() {
    BST<int*, string*>* treemap = new BST<int*, string*>();
    treemap->insertar(new int(1092), new string("Luis"));
    treemap->insertar(new int(1828), new string("Juan"));
    treemap->insertar(new int(1726), new string("Ana"));
    treemap->insertar(new int(1625), new string("Alberto"));

    treemap->imprimir();
    delete treemap;

    return 0;
}





























int main1() {
    ArbolBinarioArreglo<int*>* arbol = new ArbolBinarioArreglo<int*>;
    arbol->insertar(new int(16));
    arbol->insertar(new int(12));
    arbol->insertar(new int(17));
    arbol->insertar(new int(20));
    arbol->insertar(new int(11));
    arbol->reportarLinealmente();
    cout << "Recorrido en Pre-orden" << endl;
    arbol->pre_orden();
    cout << "Buscando 11" << endl;
    cout << "El indice donde se encuentra es: " << arbol->encontrar(new int(11));
    delete arbol;


    cout << endl;
    ArbolBinarioArreglo<string*>* arbol2 = new ArbolBinarioArreglo<string*>;
    arbol2->insertar(new string("Ana"));
    arbol2->insertar(new string("Juan"));
    arbol2->insertar(new string("Luis"));
    arbol2->insertar(new string("Pablo"));
    arbol2->insertar(new string("Oscar"));
    arbol2->reportarLinealmente();
    cout << "Recorrido en Pre-orden" << endl;
    arbol2->pre_orden();
    cout << "Buscando Luis" << endl;
    cout << "El indice donde se encuentra es: " << arbol2->encontrar(new string("Luis"));
    delete arbol2;

    return 0;
}
