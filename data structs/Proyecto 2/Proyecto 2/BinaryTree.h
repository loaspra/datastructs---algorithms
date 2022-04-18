#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <chrono>
#include "TNode.h"
using namespace std;

//--------------------------------------------------------------------
// Árboles con Nodos
//--------------------------------------------------------------------

template<typename E>
class BST
{
private:
    int contarNodo;
    void in_order_excluir(TNode<E>* it, vector<TNode<E>>& aux, E k)
    {
        if (it != nullptr && it->valor != nullptr)
        {
            TNode<E>* temp = it;
            in_order_excluir(temp->hijo_iz, aux, k);
            if (it->valor != nullptr && *it->valor != k)
                aux.push_back(*it);
            in_order_excluir(temp->hijo_de, aux, k);
        }
    }

    void in_order(TNode<E>* it, vector<TNode<E>*>& aux)
    {
        if (it != nullptr && it->valor != nullptr)
        {
            TNode<E>* temp = it;
            in_order(temp->hijo_iz, aux);
            aux.push_back(it);
            in_order(temp->hijo_de, aux);
        }
    }

    TNode<E>* balancear_(TNode<E>* root, vector<TNode<E>*> aux, int i, int f)
    {
        if (i > f)
            return nullptr;

        int medio = (i + f) / 2;
        aux[medio]->hijo_iz = balancear_(aux[medio]->hijo_iz, aux, i, medio - 1);
        aux[medio]->hijo_de = balancear_(aux[medio]->hijo_de, aux, medio + 1, f);
        return aux[medio];
    }

public:
    TNode<E>* raiz;
    BST()
    {
        this->raiz = nullptr;
        this->contarNodo = 0;
    }

    ~BST()
    {
        limpiar();
        this->raiz = nullptr;
    }

    void limpiar_(TNode<E>* nodo)
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

    void insertar(E e)
    {
        if (this->raiz == nullptr)
        {
            this->raiz = new TNode<E>(e);
        }
        else
        {
            insertarAyuda(e, this->raiz, this->raiz, this->raiz, false);
        }
        this->contarNodo++;
    }

    void pre_order_print(TNode<E>* it, vector<int>& aux)
    {
        if (it != nullptr && it->valor != nullptr)
        {
            //cout << *it->valor << endl;// "|" << *it->valor << endl;
            aux.push_back(*it->valor);
            pre_order_print(it->hijo_iz, aux);
            pre_order_print(it->hijo_de, aux);
        }
    }

    void in_order_print(TNode<E>* it)
    {
        if (it != nullptr && it->valor != nullptr)
        {
            in_order_print(it->hijo_iz);
            cout << *it->valor << endl;//"|" << *it->valor << endl;
            in_order_print(it->hijo_de);
        }
    }

    void pos_order_print(TNode<E>* it, vector<E>& aux)
    {
        if (it == nullptr || it->valor == nullptr)
            return;

        pos_order_print(it->hijo_iz, aux);
        pos_order_print(it->hijo_de, aux);
        aux.push_back(*it->valor);
        //cout << *it->valor << endl;
    }

    void balancear()
    {
        vector<TNode<E>*> aux;
        in_order(this->raiz, aux);
        this->raiz = balancear_(this->raiz, aux, 0, aux.size() - 1);
        aux.clear();
    }

    E remover(E k)
    {
        E re;
        TNode<E>* nodo = this->raiz;
        TNode<E>* aux = nodo;
        vector<TNode<E>*> vec;
        bool direc;
        bool raiz = true;
        while (nodo != nullptr && nodo->valor != nullptr)
        {
            if (*nodo->valor > k)
            {
                aux = nodo;
                nodo = nodo->hijo_iz;
                direc = false;
                raiz = false;
            }
            else
            {
                if (*nodo->valor < k)
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
                        vec.clear();
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
                    vec.clear();
                    return re;
                }
            }
        }
    }



    E remover_reor(E k)
    {
        TNode<E> m;
        bool val = false;
        E hola;
        vector<TNode<E>> aux;
        TNode<E>* it = raiz;
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
        return remover(*this->raiz->valor);
    }

    bool buscar(E k, TNode<E>* it)
    {
        while (it != nullptr && it->valor != nullptr && *it->valor != k)
        {
            if (*it->valor < k)
            {
                it = it->hijo_de;
            }
            else
            {
                it = it->hijo_iz;
            }
        }
        if (*it->valor == k)
            return true;
        return false;
    }

    bool encontrar(E k)
    {
        return buscar(k, raiz);
    }

    int longitud()
    {
        return this->contarNodo;
    }

    void insertarAyuda(E k, TNode<E>* it, TNode<E>* r, TNode<E>* p, bool direccion);
};


template<typename E>
void BST<E>::insertarAyuda(E k, TNode<E>* it, TNode<E>* r, TNode<E>* p, bool direccion)
{
    if (it != nullptr && it->valor != nullptr)
    {
        if (*it->valor < k)
        {
            insertarAyuda(k, it->hijo_de, it, p, true);
            return;
        }
        else
        {
            insertarAyuda(k, it->hijo_iz, it, p, false);
            return;
        }
    }
    else
    {
        if (direccion)
        {
            r->hijo_de = new TNode<E>(k);
        }
        else
        {
            r->hijo_iz = new TNode<E>(k);
        }
    }
}

void print(vector<int> aux)
{
    if (aux[1] < aux[2])
    {
        int c = 0;
        cout << aux[0] << endl << aux[2] << endl << aux[1] << endl;
        for (auto e : aux)
        {
            if (c > 2)
                cout << e << endl;
            c++;
        }
    }
    else
    {
        for (auto e : aux)
        {
            cout << e << endl;
        }
    }
}


//funcion para ordenar vector 
void quicksort(vector<int>& A, int izq, int der)
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