#include <iostream>
#include <vector>
#include <math.h>
using namespace std;

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
        clave = nullptr;
        hijo_iz = hijo_de = nullptr;
        clave = new Key();
    }

    TNode(Key clave, E valor, TNode* left = nullptr, TNode* right = nullptr) {
        this->clave = new Key(clave);
        hijo_iz = left;
        hijo_de = right;
        this->valor = new  E(valor);
    }

    ~TNode()
    {
        this->hijo_iz = nullptr;
        this->hijo_de = nullptr;
        this->clave = nullptr;
        this->valor = nullptr;
    }

    Key elemento()
    {
        return this->clave;
    }

    void setClave(Key e)
    {
        this->clave = new Key(e);
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
        TNode<Key, E>* nodo = new TNode<Key, E>(*aux[medio].clave, *aux[medio].clave, aux[medio].hijo_iz, aux[medio].hijo_de);
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

    void insertar(Key e, E val)
    {
        if (this->raiz == nullptr)
        {
            this->raiz = new TNode<Key, E>(e, val);
        }
        else
        {
            TNode<Key, E>* it;
            it = this->raiz;
            insertarAyuda(e, val, it, it, it, false);
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
            cout << *it->clave << endl;//"|" << *it->clave << endl;
            in_order_print(it->hijo_de);
        }
    }

    void pos_order_print(TNode<Key, E>* it, vector<Key, E>& aux)
    {
        if (it == nullptr || it->clave == nullptr)
            return;

        pos_order_print(it->hijo_iz, aux);
        pos_order_print(it->hijo_de, aux);
        aux.push_back(*it->clave);
        //cout << *it->clave << endl;
    }

    void balancear()
    {
        vector<TNode<Key, E>*> aux;
        in_order(this->raiz, aux);

        this->raiz = balancear_(this->raiz, aux, 0, aux.size() - 1);
    }

    Key remover(Key k)
    {
        Key re;
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
                    re = *nodo->clave;
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



    Key remover_reor(Key k)
    {
        TNode<Key, E> m;
        bool val = false;
        Key hola;
        vector<TNode<Key, E>> aux;
        TNode<Key, E>* it = raiz;
        hola = *it->clave;
        in_order_excluir(this->raiz, aux, k);
        limpiar();
        this->raiz = balancear_(this->raiz, aux, 0, aux.size());
        return hola;
    }

    Key removehijo_deualquiera()
    {
        if (this->contarNodo == 0)
            return nullptr;
        return remover(*this->raiz->clave);
    }

    Key encontrar(Key k, TNode<Key, E>* it)
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
                return *it->clave;
        }
        return NULL;
    }

    int longitud()
    {
        return this->contarNodo;
    }

    void insertarAyuda(Key k, E val, TNode<Key, E>* it, TNode<Key, E>* r, TNode<Key, E>* p, bool direccion);

    int solve_(TNode<Key, E>* it)
    {
        if (it->hijo_de == nullptr)
            return *it->valor;
        int suma = 0;
        suma += solve_(it->hijo_de);
        return suma;
    }

    int solve(Key aux)
    {
        TNode<Key, E>* it = this->raiz;

        while (it != nullptr && it->clave != nullptr)
        {
            if (*it->clave == aux)
                break;
            it = it->hijo_de;
        }
        return solve_(it) + *it->valor;
    }
};


template<typename Key, typename E>
void BST<Key, E>::insertarAyuda(Key k, E val, TNode<Key, E>* it, TNode<Key, E>* r, TNode<Key, E>* p, bool direccion)
{
    while (it != nullptr && it->clave != nullptr)
    {
        if (*it->clave < k)
        {
            insertarAyuda(k, val, it->hijo_de, it, p, true);
            return;
        }
        else
        {
            insertarAyuda(k, val, it->hijo_iz, it, p, false);
            return;
        }
    }
    if (direccion)
    {
        r->hijo_de = new TNode<Key, E>(k, val);
    }
    else
    {
        r->hijo_iz = new TNode<Key, E>(k, val);
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

int main()
{
    BST<string, int>* tree = new BST<string, int>;
    int N;
    cin >> N;
    string nombre;
    int ene;
    for (int i = 0; i < N; i++)
    {
        cin >> nombre >> ene;
        tree->insertar(nombre, ene);
    }

    cin >> nombre;
    cout << endl << endl;
    cout << tree->solve(nombre) << endl << endl;

    cout << "------Fin-------";
}