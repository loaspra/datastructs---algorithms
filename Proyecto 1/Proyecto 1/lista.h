#pragma once
#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;

void quicksort(int A[], int izq, int der)
{
    int i, j, x, aux;
    i = izq;
    j = der;
    x = A[(izq + der) / 2];
    do {
        while ((A[i] < x) && (j <= der))
        {
            i++;
        }

        while ((x < A[j]) && (j > izq))
        {
            j--;
        }

        if (i <= j)
        {
            aux = A[i]; A[i] = A[j]; A[j] = aux;
            i++;  j--;
        }

    } while (i <= j);

    if (izq < j)
        quicksort(A, izq, j);
    if (i < der)
        quicksort(A, i, der);
}

void quicksort(vector<int> &A, int izq, int der)
{
    int i, j, x, aux;
    i = izq;
    j = der;
    x = A[(izq + der) / 2];
    do {
        while ((A[i] < x) && (j <= der))
        {
            i++;
        }

        while ((x < A[j]) && (j > izq))
        {
            j--;
        }

        if (i <= j)
        {
            aux = A[i]; A[i] = A[j]; A[j] = aux;
            i++;  j--;
        }

    } while (i <= j);

    if (izq < j)
        quicksort(A, izq, j);
    if (i < der)
        quicksort(A, i, der);
}

template<typename E> class Lista {
private:
    void operator = (const Lista&) {}
    Lista(const Lista&) {}
public:
    Lista() {}
    virtual ~Lista() {}

    virtual void limpiar() = 0;

    virtual void insertar(E item) = 0;

    virtual void agregar(E item) = 0;

    virtual E eliminar() = 0;

    virtual void moverAInicio() = 0;
    
    virtual void moverAlFinal() = 0;

    virtual void anterior() = 0;

    virtual void siguiente() = 0;

    virtual int longitud() = 0;

    virtual int posicionActual() = 0;

    virtual void moverAPosicion(int pos) = 0;

    virtual E getValor() = 0;

    friend void quicksort(int A[], int izq, int der);
};

template<typename E>
class ListaArreglo : public Lista<E> {
private:
    int tamMax;
    int tamLista;
    int actual;
    E* arreglo;
public:

    ListaArreglo(int tamMax = 100) {
        this->tamMax = tamMax;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }

    ~ListaArreglo() 
    {
        delete[] this->arreglo;
    }

    void resize()
    {
        vector<E> aux(0);
        for (size_t i = 0; i < this->tamLista; i++)
        {
            aux.push_back(this->arreglo[i]);
        }
        delete[] this->arreglo;
        this->tamMax = this->tamMax + 100;
        this->arreglo = new E[this->tamMax];
        int i = 0;

        for (auto e : aux)
        {
            this->arreglo[i] = e;
            i++;
        }
    }

    void moverAInicio() {
        this->actual = 0;
    }

    void moverAlFinal() {
        this->actual = this->tamLista;
    }

    void ordenar()
    {
        quicksort(this->arreglo, 0, this->tamLista - 1);
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

    void agregar(E elemento) 
    {
        if (this->tamLista == this->tamMax)
            resize();
        this->arreglo[this->tamLista++] = elemento;
    }

    void insertar(E elemento) 
    {
        if (this->tamLista == this->tamMax)
            resize();
        for (int i = tamLista; i > actual; i--) {
            this->arreglo[i] = this->arreglo[i - 1];
        }
        this->arreglo[actual] = elemento;
        this->tamLista++;
    }

    int buscar(E elemento)
    {
        for (int i = 0; i < this->tamLista; i++) 
        {
            if (this->arreglo[i] == elemento)
                return i;
        }
        return -1;
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

    E eliminar(int e) 
    {
        actual = buscar(e);
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

    E getValor_pos(int pos)
    {
        return this->arreglo[pos];
    }

    void putValue(int pos, int value)
    {
        this->arreglo[pos] = value;
    }
};


template<typename E>
class ListaEnlazada : public Lista<E> {
private:
    Nodo<E>* cola;
    Nodo<E>* head;
    Nodo<E>* actual;
    int cantidad;

    void inicializar()
    {
        this->head = this->actual = this->cola = new Nodo<E>(NULL);
        this->cantidad = 0;
    }

public:
    ListaEnlazada()
    {
        inicializar();
    }

    ~ListaEnlazada()
    {
        limpiar();
    }

    void agregar(E elemento)
    {
        this->cola = this->cola->siguiente = new Nodo<E>(elemento, NULL);
        if (cantidad == 0)
            this->head = this->actual = this->cola;
        cantidad++;
    };

    int buscar(E ele)
    {
        this->actual = this->head;
        while (this->actual != NULL)
        {
            if (this->actual->elemento == ele)
            {
                return posicionActual();
            }
                
            this->actual = this->actual->siguiente;
        }
        
        return -1;
    }

    void push_front(E item)
    {
        auto aux = new Nodo<E>(item, NULL);
        aux->siguiente = head->siguiente;
        head->siguiente = aux;
    }

    void moverAInicio()
    {
        this->actual = this->head;
    }

    void moverAlFinal()
    {
        this->actual = this->cola;
    }

    void moverAPosicion(int pos)
    {

        this->actual = this->head;
        for (auto e = 0; e < pos; e++)
        {
            this->actual = this->actual->siguiente;
        }
    }

    void insertar(E item)
    {
        auto aux = new Nodo<E>(item, actual->siguiente);

        actual->siguiente = aux;
        if (aux->siguiente == NULL)
        {
            cola = cola->siguiente;
        }
        this->cantidad = this->cantidad + 1;
    }


    int posicionActual()
    {
        int r = 0;
        for (auto e = actual; e != NULL; e = e->siguiente)
        {
            r++;
        }
        return longitud() - r;
    }

    int longitud()
    {
        return this->cantidad;
    }

    void siguiente()
    {
        this->actual = this->actual->siguiente;
    }

    E getValor()
    {
        return this->actual->elemento;
    }

    void anterior()
    {
        this->moverAPosicion(this->posicionActual() - 1);
    }

    void limpiar()
    {
        while (this->head != NULL)
        {
            Nodo<E>* temp = this->head;
            this->head = this->head->siguiente;
            delete temp;
        }
        Nodo<E>* temp = this->cola;
        this->cola = this->head = new Nodo<E>(NULL);
       // delete this->actual;
    }

    void ordenar()
    {
        vector<E> aux(0);
        this->moverAInicio();
        
        while (this->head != this->cola)
        {
            aux.push_back(this->head->elemento);
            this->head = this->head->siguiente;
        }
        aux.push_back(this->cola->elemento);
        this->limpiar();
        quicksort(aux, 0, aux.size() - 1);
        for (auto e : aux)
        {
            this->agregar(e);
        }
        return;
    }

    E eliminar(E valor)
    {
        int pos;
        pos = this->buscar(valor);
        this->moverAPosicion(pos);
        Nodo<E>* aux = new Nodo<E>(this->actual->siguiente);
        this->moverAPosicion(this->posicionActual() - 1);
        this->actual->siguiente = aux;
        E* temp = new E(aux->elemento);
        cantidad--;
        return *temp;
    }


    E eliminar()
    {
        Nodo<E>* aux = new Nodo<E>(this->actual->siguiente);
        this->moverAPosicion(this->posicionActual() - 1);
        this->actual->siguiente = aux;
        E* temp = new E(aux->elemento);
        delete aux;
        return *temp;
    }


};