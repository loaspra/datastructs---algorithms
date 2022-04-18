#include <iostream>
//#include <bits/stdc++.h> 
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

    E getValor() {
        return this->arreglo[this->actual];
    }

};










//Clase Abstracta: Set
template<typename Key>
class Set {
private:
public:
    //Constructor
    Set() {}
    //Base Destructor
    virtual ~Set() {}

    //Permite reinicializar el diccionario o tabla Hash
    virtual void limpiar() = 0;

    //k: la clave para el registro 
    //e: el registro siendo insertado
    virtual void insertar(Key k) = 0;

    //k: la clave para el registro a ser removido
    //retorno: un registro asociado a k. Si hay muchos registros 
    //que se asocian a k, hay que remover uno de manera arbitraria
    //Debe retornar NULL si no hay registros con la clave k
    virtual void remover(Key k) = 0;

    //Retornar y remover un registro arbitrario del diccionario
    //Retorna NULL si no hay registros en el diccionario
    virtual Key removerCualquiera() = 0;

    //Retornar un registro que se asocie con k (NULL si no existe)
    //Si múltiples registros se asocian con k, retornar uno 
    //de manera arbitraria
    //k: es la clave a encontrar
    //retorna un entero con la posicion actual de k
    virtual int encontrar(Key k) = 0;

    //Retornar el número de registros existentes en el diccionario
    virtual int longitud() = 0;
};


//SET_
template<typename Key>
class SET_ : public Set<Key> {
private:
    ListaArreglo<Key>* lista;
public:
    //Constructor
    SET_(int tamanho = 100) {
        lista = new ListaArreglo<Key>(tamanho);
    }

    ~SET_() {
        delete lista;
    }

    void limpiar() {
        this->lista->limpiar();
    }

    void insertar(Key k) {
        lista->moverAInicio();
        while (lista->getValor() != "") {
            if (lista->getValor() == k) {
                return;
            }
            else {
                lista->siguiente();
            }
        }
        lista->insertar(k);
    }
    /*void insertar(Key k) {
      int indice = hash(k);
      lista->moverAPosicion(indice);
      //....depende de separate chaining u open addressing
      lista->insertar(k);
    }*/

    int encontrar(Key k) {
        for (lista->moverAInicio(); lista->posicionActual() < lista->longitud(); lista->siguiente()) {
            if (k == lista->getValor()) {
                return lista->posicionActual();
            }
        }
        return -1;
    }

    void remover(Key k) {
        int indice = encontrar(k);
        if (indice != -1) {
            lista->moverAPosicion(indice);
            lista->eliminar();
        }
    }

    Key removerCualquiera() {
        lista->moverAlFinal();
        lista->anterior();
        Key temp = lista->eliminar();
        return temp;
    }


    int longitud() {
        return this->lista->longitud();
    }
};


int fac(int n) 
{
    if (n < 0) return 0;
    else if (n > 1) return n * fac(n - 1);
    return 1;
}


int main() 
{

    string p;
    int* N = new int;
    int* x = new int;
    int* y = new int;
    cin >> *N;
    
    for (size_t i = 0; i < *N; i++)
    {
        SET_<string>* a = new SET_<string>;
        SET_<string>* b = new SET_<string>;
        cin >> *x;
        cin >> *y;
        for (size_t j = 0; j < (*x + *y); j++)
        {
            cin >> p;
            if (j < *x)
                a->insertar(p);
            else
                b->insertar(p);
        }

        int* n = new int;
        *n = *x + *y;
        cout << "Case " <<i+1<<": "<< a->longitud() * b->longitud() << endl;
        delete a;
        delete b;
    }
    //i + 1 << " " << fac(*n) / (fac(*x) * (fac(*n - *x)))

}
