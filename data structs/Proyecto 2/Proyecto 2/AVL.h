#pragma once

#include <vector>
#include <math.h>
#include <fstream>
#include <iostream>
#include <chrono>
#include "AVLNode.h"
using namespace std;

//--------------------------------------------------------------------
// AVL->AVL
//--------------------------------------------------------------------

//funciones auxiliares
int max(int a, int b)
{
    return (a > b) ? a : b;
}


template<typename E>
class AVL
{
private:
    int contarNodo;

    int getBalance(AVLNode<E>* N)
    {
        if (N == NULL)
            return 0;
        return height(N->hijo_iz) - height(N->hijo_de);
    }
    void in_order_excluir(AVLNode<E>* it, vector<AVLNode<E>>& aux, E k)
    {
        if (it != nullptr && it->valor != nullptr)
        {
            AVLNode<E>* temp = it;
            in_order_excluir(temp->hijo_iz, aux, k);
            if (it->valor != nullptr && *it->valor != k)
                aux.push_back(*it);
            in_order_excluir(temp->hijo_de, aux, k);
        }
    }

    AVLNode<E>* minValueNode(AVLNode<E>* node)
    {
        AVLNode<E>* current = node;

        while (current->hijo_iz != NULL)
            current = current->hijo_iz;

        return current;
    }

    AVLNode<E>* del(AVLNode<E> * raiz, int key)
    {

        if (raiz == nullptr)
            return raiz;

        if (key < *raiz->valor)
            raiz->hijo_iz = del(raiz->hijo_iz, key);

        else if (key > *raiz->valor)
            raiz->hijo_de = del(raiz->hijo_de, key);

        else
        {
            if ((raiz->hijo_iz == nullptr) || (raiz->hijo_de == nullptr))
            {
                AVLNode<E>* temp = raiz->hijo_iz ?
                    raiz->hijo_iz :
                    raiz->hijo_de;
 
                if (temp == nullptr)
                {
                    temp = raiz;
                    raiz = nullptr;
                }
                else  
                    *raiz = *temp; 
                free(temp);
            }
            else
            { 
                AVLNode<E>* temp = minValueNode(raiz->hijo_de);

                raiz->valor = temp->valor;

                raiz->hijo_de = del(raiz->hijo_de, *temp->valor);
            }
        }

        if (raiz == nullptr)
            return raiz;

        raiz->altura = 1 + max(height(raiz->hijo_iz),
            height(raiz->hijo_de));

        int balance = getBalance(raiz);

        if (balance > 1 &&
            getBalance(raiz->hijo_iz) >= 0)
            return rotar_de(raiz);

        if (balance > 1 &&
            getBalance(raiz->hijo_iz) < 0)
        {
            raiz->hijo_iz = rotar_iz(raiz->hijo_iz);
            return rotar_de(raiz);
        }

        if (balance < -1 &&
            getBalance(raiz->hijo_de) <= 0)
            return rotar_iz(raiz);

        if (balance < -1 &&
            getBalance(raiz->hijo_de) > 0)
        {
            raiz->hijo_de = rotar_de(raiz->hijo_de);
            return rotar_iz(raiz);
        }

        return raiz;
    }

    void in_order(AVLNode<E>* it, vector<AVLNode<E>*>& aux)
    {
        if (it != nullptr && it->valor != nullptr)
        {
            AVLNode<E>* temp = it;
            in_order(temp->hijo_iz, aux);
            aux.push_back(it);
            in_order(temp->hijo_de, aux);
        }
    }

    AVLNode<E>* insert(AVLNode<E>* node, E key)
    {

        if (node == nullptr)
            return(new AVLNode<E>(key));

        if (key < *node->valor)
            node->hijo_iz = insert(node->hijo_iz, key);
        else if (key > *node->valor)
            node->hijo_de = insert(node->hijo_de, key);
        else
            return node;

        int alt_iz = 0, alt_de = 0;
        if (node->hijo_iz != nullptr)
            alt_iz = node->hijo_iz->altura;

        if (node->hijo_de != nullptr)
            alt_de = node->hijo_de->altura;

        node->altura = 1 + max(alt_iz, alt_de);

        int balance = getBalance(node);


        // IZQUIERDA IZQUIERDA
        if (balance > 1 && key < *node->hijo_iz->valor)
            return rotar_de(node);

        // DERECHA DERECHA
        if (balance < -1 && key > *node->hijo_de->valor)
            return rotar_iz(node);

        // IZQUIERDA DERECHA
        if (balance > 1 && key > *node->hijo_iz->valor)
        {
            node->hijo_iz = rotar_iz(node->hijo_iz);
            return rotar_de(node);
        }

        // DERECHA IZQUIERDA
        if (balance < -1 && key < *node->hijo_de->valor)
        {
            node->hijo_de = rotar_de(node->hijo_de);
            return rotar_iz(node);
        }

        return node;
    }

public:
    AVLNode<E>* raiz;
    AVL()
    {
        this->raiz = nullptr;
        this->contarNodo = 0;
    }

    ~AVL()
    {
        limpiar();
        this->raiz = nullptr;
    }

    void limpiar_(AVLNode<E>* nodo)
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
        this->raiz = insert(raiz, e);
        this->contarNodo++;
    }


    AVLNode<E>* rotar_de(AVLNode<E>* y)
    {
        AVLNode<E>* x = y->hijo_iz;
        AVLNode<E>* T2 = x->hijo_de;

        x->hijo_de = y;
        y->hijo_iz = T2;

        y->altura = max(height(y->hijo_iz), height(y->hijo_de)) + 1;
        x->altura = max(height(x->hijo_iz), height(x->hijo_de)) + 1;

        return x;
    }

    int height(AVLNode<E>* N)
    {
        if (N == NULL)
            return 0;
        return N->altura;
    }

    AVLNode<E>* rotar_iz(AVLNode<E>* x)
    {
        AVLNode<E>* y = x->hijo_de;
        AVLNode<E>* T2 = y->hijo_iz;

        y->hijo_iz = x;
        x->hijo_de = T2;

        int alt_iz = 0, alt_de = 0;

        x->altura = max(height(x->hijo_iz), height(x->hijo_de)) + 1;
        y->altura = max(height(y->hijo_iz), height(y->hijo_de)) + 1;

        return y;
    }

    void pre_order_print(AVLNode<E>* it, vector<int>& aux)
    {
        if (it != nullptr && it->valor != nullptr)
        {
            //cout << *it->valor << endl;// "|" << *it->valor << endl;
            aux.push_back(*it->valor);
            pre_order_print(it->hijo_iz, aux);
            pre_order_print(it->hijo_de, aux);
        }
    }

    void in_order_print(AVLNode<E>* it)
    {
        if (it != nullptr && it->valor != nullptr)
        {
            in_order_print(it->hijo_iz);
            cout << *it->valor << endl;//"|" << *it->valor << endl;
            in_order_print(it->hijo_de);
        }
    }

    void pos_order_print(AVLNode<E>* it, vector<E>& aux)
    {
        if (it == nullptr || it->valor == nullptr)
            return;

        pos_order_print(it->hijo_iz, aux);
        pos_order_print(it->hijo_de, aux);
        aux.push_back(*it->valor);
    }

    void remover(E k)
    {
        this->raiz = del(this->raiz, k);
    }

    E removehijo_deualquiera()
    {
        if (this->contarNodo == 0)
            return nullptr;
        return remover(*this->raiz->valor);
    }

    bool buscar(E k, AVLNode<E>* it)
    {
        if (*it->valor < k)
        {
            return buscar(k, it->hijo_de);
        }
        else
        {
            if (*it->valor > k)
            {
                return buscar(k, it->hijo_iz);
            }
            else
                return *it->valor;
        }
        return NULL;
    }

    bool encontrar(E k)
    {
        return buscar(k, raiz);
    }

    int longitud()
    {
        return this->contarNodo;
    }
};