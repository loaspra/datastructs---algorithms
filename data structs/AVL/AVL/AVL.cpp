#pragma once
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>
#include <chrono>
using namespace std;

//--------------------------------------------------------------------
// AVL->AVL
//--------------------------------------------------------------------

template<typename E>
class TNode
{
public:
    E* valor;
    TNode* hijo_iz;
    TNode* hijo_de;
    int altura;

    TNode()
    {
        hijo_iz = hijo_de = nullptr;
    }

    TNode(E value, TNode* left = nullptr, TNode* right = nullptr)
    {
        valor = new E(value);
        hijo_iz = left;
        hijo_de = right;
    }

    ~TNode()
    {
        this->hijo_iz = nullptr;
        this->hijo_de = nullptr;
        delete this->valor;
    }

    E elemento()
    {
        return this->valor;
    }

    void setValor(E e)
    {
        this->valor = new E(e);
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

    int getBalance(TNode<E>* N)
    {
        if (N == NULL)
            return 0;
        return height(N->hijo_iz) - height(N->hijo_de);
    }
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

    TNode<E>* insert(TNode<E>* node, E key)
    {

        if (node == nullptr)
            return(new TNode<E>(key));

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
    TNode<E>* raiz;
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
        this->raiz = insert(raiz, e);
        this->contarNodo++;
    }


    TNode<E>* rotar_de(TNode<E>* y)
    {
        TNode<E>* x = y->hijo_iz;
        TNode<E>* T2 = x->hijo_de;

        x->hijo_de = y;
        y->hijo_iz = T2;

        y->altura = max(y->hijo_iz->altura, y->hijo_de->altura) + 1;
        x->altura = max(x->hijo_iz->altura, x->hijo_de->altura) + 1;

        return x;
    }

    int height(TNode<E>* N)
    {
        if (N == NULL)
            return 0;
        return N->altura;
    }

    TNode<E>* rotar_iz(TNode<E>* x)
    {
        TNode<E>* y = x->hijo_de;
        TNode<E>* T2 = y->hijo_iz;

        y->hijo_iz = x;
        x->hijo_de = T2;

        int alt_iz = 0, alt_de = 0;

        x->altura = max(height(x->hijo_iz), height(x->hijo_de)) + 1;
        y->altura = max(height(y->hijo_iz), height(y->hijo_de)) + 1;

        return y;
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

    E encontrar(E k, TNode<E>* it)
    {
        if (*it->valor < k)
        {
            return encontrar(k, it->hijo_de);
        }
        else
        {
            if (*it->valor > k)
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
};


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

int main()
{
    AVL<int>* avl = new AVL<int>;
    avl->insertar(5);
    avl->insertar(4);
    avl->insertar(6);
    avl->insertar(7);
    avl->insertar(8);
    avl->insertar(9);
    cout << "GOOOL EOEOEOEOEOEO" << endl;
    return 0;
}