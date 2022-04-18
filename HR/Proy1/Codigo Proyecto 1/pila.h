#pragma once
#include <iostream>
#include <vector>

using namespace std;

template<typename E> class Nodo {
public:
    E elemento;
    Nodo* siguiente;

    Nodo(E elemento, Nodo* siguiente = NULL) {
        this->elemento = elemento;
        this->siguiente = siguiente;
    }

    Nodo(Nodo* siguiente = NULL) {
        this->siguiente = siguiente;
        this->elemento = NULL;
    }

    ~Nodo()
    {

    }
};

template<typename E> class Pila {
private:
public:
    Pila() {}
    virtual ~Pila() {}

    virtual E pop() = 0;

    virtual void apilar(E elemento) = 0;

    virtual void limpiar() = 0;

    virtual E valorTop() = 0;

    virtual int longitud() = 0;
};

template<typename E> class APila : public Pila<E> {
private:
    int tamMaximo;
    int cima;
    E* arreglo;

public:

    APila(int tamanho = 100) {
        this->tamMaximo = tamanho;
        this->cima = 0;
        this->arreglo = new E[this->tamMaximo];
    }

    ~APila() {
        delete[] this->arreglo;
    }

    void resize()
    {
        vector<E> aux(0);
        for (size_t i = 0; i < this->cima; i++)
        {
            aux.push_back(this->arreglo[i]);
        }
        delete[] this->arreglo;
        this->tamMaximo = this->tamMaximo + 100;
        this->arreglo = new E[this->tamMaximo];
        int i = 0;

        for (auto e : aux)
        {
            this->arreglo[i] = e;
            i++;
        }
    }

    int buscar(int valor)
    {
        for (int i = 0; i <= this->cima; i++)
        {
            if (this->arreglo[i] == valor)
                return i;
        }
        return -1;
    }

    E eliminar(int valor)
    {
        int pos = buscar(valor);
        E temp = this->arreglo[pos];
        while (pos < this->cima)
        {
            this->arreglo[pos] = this->arreglo[pos + 1];
            pos++;
        }
        this->cima--;
        return temp;
    }

    E pop() {
        return this->arreglo[--cima];
    }

    void apilar(E elemento) {
        if (this->cima < tamMaximo)
            this->arreglo[cima++] = elemento;
        else
        {
            resize();
            this->arreglo[cima++] = elemento;
        }
    }

    void limpiar() {
        this->cima = 0;
    }

    E valorTop() {
        return this->arreglo[cima - 1];
    }

    int longitud() {
        return this->cima;
    }
};

template<typename E> class LPila : public Pila<E> {
private:
    Nodo<E>* cima;
    int tamanho;
public:

    LPila() {
        this->tamanho = 0;
        this->cima = NULL;
    }

    ~LPila() {
        limpiar();
    }


    E pop() {
        E elem = cima->elemento;
        Nodo<E>* temp = cima->siguiente;
        delete cima;
        cima = temp;
        tamanho--;
        return elem;
    }

    bool buscar(E valor) //retorna el indice
    {
        vector<E> aux(0);
        E iter = this->pop();
        while (iter != valor && this->tamanho > 0)
        {
            aux.push_back(iter);
            iter = this->pop();
        }

        if (iter != valor)
            return false;				// se rearma toda la estructura...
                                        // se debe de desencolar tooooda la queue para luego volver a encolarla, ya que no se 
        while (this->tamanho > 0)		// mantendria el orden si es que se volviera a encolar, y la unica manera de iterar dentro de 
        {								// esta estructura es desencolando, ya que no hay ningun nodo "actual" (si es que se implementase, 
            aux.push_back(iter);		// se comportaria como una lista enlazada
            iter = this->pop();
        }
        aux.push_back(iter);

        for (auto e : aux)
        {
            this->apilar(e);
        }

        return false;
    }

    void apilar(E elemento) {
        this->cima = new Nodo<E>(elemento, this->cima);
        this->tamanho++;
    }

    void eliminar(E valor)
    {
        vector<E> aux(0);
        E iter = this->pop();
        while (iter != valor && this->tamanho > 0)
        {
            aux.push_back(iter);
            iter = this->pop();
        }
        if (this->tamanho > 1)
            this->pop();

        if (this->tamanho > 1)
            iter = this->pop();

        while (this->tamanho > 0)
        {
            aux.push_back(iter);
            iter = this->pop();
        }
        aux.push_back(iter);

        for (auto e : aux)
        {
            this->apilar(e);
        }

        return;
    }


    void limpiar() {
        while (this->cima != NULL) {
            Nodo<E>* temp = cima;
            cima = cima->siguiente;
            delete temp;
        }
        tamanho = 0;
    }


    E valorTop() {
        return this->cima->elemento;
    }

    int longitud() {
        return this->tamanho;
    }

};
