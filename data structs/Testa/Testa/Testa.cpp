#include <cmath>
#include <mutex>
#include <iterator>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;
template <typename E>
class ListaArreglo
{
private:
    int tamMax;
    int tamLista;
    int actual;
    E* arreglo;

public:
    ListaArreglo(int tamMax = 100)
    {
        this->tamMax = tamMax;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }
    ~ListaArreglo()
    {
        delete[] this->arreglo;
    }

    void moverAInicio()
    {
        this->actual = 0;
    }
    void moverAlFinal()
    {
        this->actual = this->tamLista;
    }
    void siguiente()
    {
        this->actual++;
    }
    void anterior()
    {
        if (this->actual != 0)
        {
            this->actual--;
        }
    }
    void push_back(E elemento)
    {
        this->arreglo[this->tamLista++] = elemento;
    }
    void insert(E elemento)
    {
        this->arreglo[actual] = elemento;
        this->tamLista++;
    }
    void limpiar()
    {
        delete[] this->arreglo;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }
    E eliminar()
    {
        E temp = this->arreglo[this->actual];
        for (int i = this->actual; i < this->tamLista - 1; i++)
        {
            this->arreglo[i] = this->arreglo[i + 1];
        }
        this->tamLista--;
        return temp;
    }
    int longitud()
    {
        return this->tamLista;
    }
    int posicionActual()
    {
        return this->actual;
    }
    void moverAPosicion(int pos)
    {
        if (pos >= 0)
        {
            this->actual = pos;
        }
    }
    E getValor(int pos)
    {
        return this->arreglo[pos];
    }
    E getValor()
    {
        return this->arreglo[this->actual];
    }
    void putValue(int pos, E elemento)
    {
        this->arreglo[pos] = elemento;
    }
    void agregar(E elemento)
    {
        for (int i = tamLista + 1; i > actual + 1; i--)
        {
            this->arreglo[i] = this->arreglo[i - 1];
        }
        this->tamLista++;
        if (this->actual == 0 || this->actual == this->tamLista - 1)
        {
            this->arreglo[actual] = elemento;
        }
        else
        {
            this->arreglo[actual + 1] = elemento;
        }

        this->actual = this->actual + 1;
    }
    void push_front(E item)
    {
        if (this->tamLista == this->tamMax)
        {
            return;
        }
        for (int i = this->tamLista; i > 0; i--)
        {
            this->arreglo[i] = this->arreglo[i - 1];
        }
        this->arreglo[0] = item;
        this->tamLista++;
        this->actual++;
    }

    E& operator[](int index)
    {
        return arreglo[index];
    }
    const E& operator[](int index) const
    {
        return arreglo[index];
    }
};



template <typename E>
class ArbolBinarioArreglo
{
private:
    ListaArreglo<E>* arreglo;
    int tamMax;
    int tamLista;

public:
    ArbolBinarioArreglo(int size = 100)
    {
        this->tamMax = size;
        this->tamLista = 0;
        this->arreglo = new ListaArreglo<E>(size);
        for (int i = 0; i < tamMax; ++i)
            arreglo->putValue(i, nullptr);
    }

    int longitud()
    {
        return this->tamLista;
    }

    int hijo_iz(int index)
    {
        return index * 2 + 1;
    }

    int hijo_de(int index)
    {
        return index * 2 + 2;
    }

    int roota(int index)
    {
        return (index - 1) / 2;
    }


    void insert(E e)
    {
        if (this->tamLista == 0)
        {
            arreglo->putValue(0, e);
            this->tamLista++;
            return;
        }
        int a = 0;
        while (true)
        {
            if (arreglo->getValor(a) == nullptr)
            {
                arreglo->putValue(a, e);
                this->tamLista++;
                return;
            }

            if (*(arreglo->getValor(a)) == *e)
            {
                return;
            }

            else if (*e > *(arreglo->getValor(a)))
            {
                a = hijo_de(a);
            }

            else if (*e < *(arreglo->getValor(a)))
            {
                a = hijo_iz(a);
            }
        }
    }

    int encontrar(E value)
    {
        int ind = 0;
        while (this->arreglo->getValor(ind) != nullptr) //while (v[ind]  != nulo)
        {

            if (*value > *(arreglo->getValor(ind)))
            {
                ind = hijo_de(ind);
            }
            else
            {
                if (*value < *(arreglo->getValor(ind)))
                    ind = hijo_iz(ind);
                else
                {
                    return ind;
                }
            }
        }
        return -1;
    }

    void in_order(int i, vector<int>& valores)
    {
        if (this->arreglo->getValor(i) != nullptr)
        {
            in_order(hijo_iz(i), valores);
            valores.push_back(*(this->arreglo->getValor(i)));
            this->arreglo->putValue(i, 0);
            in_order(hijo_de(i), valores);
        }
    }

    int eliminar(E valor, vector<int>& aux)
    {
        int ind = encontrar(valor);
        int m = 0;
        bool val = false;
        if (ind != -1)
        {
            in_order(ind, aux);
            float n = aux.size();

            if (int(n) % 2 != 0)
                val = true;

            n--;
            n = n / 2;

            n = round(n);
            m = aux[n];
            insert(new int(m));

            if (val)
            {
                insert(new int(aux[n + 1]));
            }
            int c = 0;
            for (size_t i = 1; i < n; i++)
            {

                if (aux[n - i] == *(valor))
                    c = 1;

                insert(new int(aux[n - i - c]));
                insert(new int(aux[n + i + val]));
            }
        }
        return -1;
    }

    void in_order(int index)
    {
        if (arreglo->getValor(index) == nullptr)
            return;
        in_order(hijo_iz(index));
        cout << *arreglo->getValor(index) << "\n";
        in_order(hijo_de(index));
    }
    void pre_order(int index)
    {
        if (arreglo->getValor(index) == nullptr)
            return;
        cout << *arreglo->getValor(index) << "\n";
        pre_order(hijo_iz(index));
        pre_order(hijo_de(index));
    }
    void pos_order(int index)
    {
        if (arreglo->getValor(index) == nullptr)
            return;
        pos_order(hijo_iz(index));
        pos_order(hijo_de(index));
        cout << *arreglo->getValor(index) << "\n";
    }
};


int main()
{
    ArbolBinarioArreglo<int*>* tree = new ArbolBinarioArreglo<int*>;
    vector<int> aux;
    int x;
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> x;
        auto ptr = new int(x);
        tree->insert(ptr);
    }
    cin >> N;
    tree->eliminar(new int(N), aux);
    tree->pos_order(0);

    return 0;
}
