#include <iostream>
#include <math.h>
using namespace std;
constexpr auto nulo = NULL;

template<typename E>
class Nodo 
{
public:
    E valor;
    Nodo* siguiente;
    //Constructor
    Nodo(E valor, Nodo* siguiente = NULL)
    {
        this->valor = valor;
        this->siguiente = siguiente;
    }

    Nodo()
    {
        this->valor = nulo;
        this->siguiente = NULL;
    }
};


template<typename E> class Lista {
private:
    void operator = (const Lista&) {}
    Lista(const Lista&) {}
public:
    Lista() {}
    virtual ~Lista() {}

    virtual void limpiar() = 0;

    virtual void insertar(E item) = 0;

    virtual E eliminar() = 0;

    virtual void moverAInicio() = 0;

    virtual void moverAlFinal() = 0;

    virtual void anterior() = 0;

    virtual void siguiente() = 0;

    virtual int longitud() = 0;

    virtual int posicionActual() = 0;

    virtual void moverAPosicion(int pos) = 0;

    virtual E getValor() = 0;
};

template<typename E>
class ListaNode : public Lista<E> {
private:
    int tamMax;
    int tamLista;
    int actual;
    int auxiliar;
    Nodo<E>* arreglo;
    Nodo<E>* colisiones;
public:
    ListaNode(int tamMax = 500) {
        this->tamMax = tamMax;
        this->tamLista = this->actual = 0;
        this->arreglo = new Nodo<E>[this->tamMax];
        this->auxiliar = tamMax;
        this->colisiones = new Nodo<E>[this->tamMax];
        for (int i = 0; i < tamMax; i++)
        {
            this->arreglo[i].valor = nulo;
            this->arreglo[i].siguiente = NULL;

            this->colisiones[i].valor = nulo;
            this->colisiones[i].siguiente = NULL;
        }
    }

    ~ListaNode() {
        delete[] this->arreglo;
    }

    void moverAInicio() {
        this->actual = 0;
    }

    void moverAlFinal() {
        this->actual = this->auxiliar;
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

    void insertar(E elemento) 
    {
        if (this->arreglo[actual].valor == nulo)
        {
            this->arreglo[actual].valor = elemento;
        }
        else
        {
            this->colisiones[actual].valor = this->colisiones[actual].valor + 1;
            this->arreglo[actual].siguiente = new Nodo<E>;
            this->arreglo[actual].siguiente->valor = elemento;
        }
        this->tamLista++;
    }

    void limpiar() {
        delete[] this->arreglo;
        this->tamLista = this->actual = 0;
        this->arreglo = new Nodo<E>[this->tamMax];
    }

    E eliminar() 
    {
        E temp = this->arreglo[actual].valor;
        this->arreglo[actual].valor = nulo;
        this->auxiliar--;
        return temp;
    }

    int longitud() {
        return this->tamLista;
    }

    int posicionActual() {
        return this->actual;
    }

    void moverAPosicion(int pos) {
        if (pos >= 0 && pos < this->tamMax) 
        {
            this->actual = pos;
        }
    }

    int get_tamMax()
    {
        return this->tamMax;
    }

    E getValor() {
        return this->arreglo[this->actual].valor;
    }

    void repeticiones()
    {
        int min = 0;
        int r = 0;
        for (auto e = 0; e < tamMax; e++)
        {
            if (colisiones[e].valor > 0)
            {
                if (colisiones[e].valor > min)
                {
                    r = 0;
                    min = colisiones[e].valor;
                }
                if (colisiones[e].valor == min)
                {
                    r++;
                }
            }
        }
            cout << min << endl;}

};


template<typename Key>
class Set {
private:
public:

    Set() {}

    virtual ~Set() {}

    virtual void limpiar() = 0;

    virtual void insertar(Key k) = 0;

    virtual void remover(Key k) = 0;

    virtual Key removerCualquiera() = 0;

    virtual bool encontrar(Key k) = 0;

    virtual int longitud() = 0;
};


//SET_chaining
template<typename Key>
class SET_chaining : public Set<Key>
{
private:
    ListaNode<Key>* lista;
public:
    //Constructor
    SET_chaining(int tamanho = 100)
    {
        lista = new ListaNode<Key>(tamanho);
    }

    ~SET_chaining()
    {
        delete lista;
    }

    void limpiar()
    {
        this->lista->limpiar();
    }

    //strings
    int Hash(Key k)
    {
        int c = 0;
        int ash = 0;
        for (auto e : k)
        {
            ash += int(e) + 30 * c;
            c++;
        }
        return (ash % this->lista->get_tamMax());
    }

    void insertar(Key k)
    {
        int indice = Hash(k);
        lista->moverAPosicion(indice);
        lista->insertar(k);
    }

    bool encontrar(Key k)
    {
        int indice = Hash(k);
        this->lista->moverAPosicion(indice);
        Key value = this->lista->getValor();
        if (value != "")
        {
            return true;
        }
        return false;
    }

    void remover(Key k)
    {
        int indice;
        if (encontrar(k))
        {
            indice = Hash(k);
            lista->moverAPosicion(indice);
            lista->eliminar();
        }
    }

    Key removerCualquiera()
    {
        lista->moverAlFinal();
        lista->anterior();
        Key temp = lista->eliminar();
        return temp;
    }

    int get_tamMax()
    {
        return this->lista->get_tamMax();
    }

    int longitud()
    {
        return this->lista->longitud();
    }
};


template<typename Key, typename E>
class Diccionario
{
private:
public:

    Diccionario() {}

    virtual ~Diccionario() {}

    virtual void limpiar() = 0;

    virtual void insertar(Key k, E valor) = 0;

    virtual void remover(Key k) = 0;

    virtual E removerCualquiera() = 0;

    virtual bool encontrar(Key k) = 0;

    virtual int longitud() = 0;
};


//Diccionario_chaining
template<typename Key, typename E>
class Diccionario_chaining : public Diccionario<Key, E>
{
private:
    ListaNode<E>* lista;
public:
    //Constructor
    Diccionario_chaining(int tamanho = 500)
    {
        lista = new ListaNode<E>(tamanho);
    }

    ~Diccionario_chaining()
    {
        delete lista;
    }

    void limpiar()
    {
        this->lista->limpiar();
    }

    /*
    //strings
    int Hash(Key k)
    {
        int c = 0;
        int ash = 0;
        for (auto e : k)
        {
            ash += int(e)*c + 30;
            c++;
        }
        return (ash % this->lista->get_tamMax());
    }*/

    //numeros
    int Hash(Key k)
    {
        return (k);
    }


    void insertar(Key k, E valor)
    {
        int indice = Hash(k);
        lista->moverAPosicion(indice);
        lista->insertar(valor);
    }


    bool encontrar(Key k)
    {
        int indice = Hash(k);
        this->lista->moverAPosicion(indice);
        E value = this->lista->getValor();
        if (value != nulo)
        {
            return true;
        }
        return false;
    }

    void remover(Key k)
    {
        int indice;
        if (encontrar(k))
        {
            indice = Hash(k);
            lista->moverAPosicion(indice);
            lista->eliminar();
        }
    }

    void repet()
    {
        lista->repeticiones();
    }

    E removerCualquiera()
    {
        lista->moverAlFinal();
        lista->anterior();
        E temp = lista->eliminar();
        return temp;
    }


    int tamMax()
    {
        return this->lista->get_tamMax();
    }

    int longitud()
    {
        return this->lista->longitud();
    }
};

int main()
{
    Diccionario_chaining<int, int>* dic = new Diccionario_chaining<int, int>;

    int N = 1;
    int llave;
    int value;
    while (true)
    {
        cin >> N;
        if (N == 0)
            break;
        for (auto e = 0; e < N*5; e++)
        {
            cin >> llave;
            value = llave;
            dic->insertar(llave, value);
        }
        dic->repet();
    }
    
    
    return 0;
}
