#include <iostream>
#include <math.h>
using namespace std;
constexpr auto nulo = nullptr;

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
class ListaArreglo : public Lista<E> {
private:
    int tamMax;
    int tamLista;
    int actual;
    E** arreglo;
public:

    ListaArreglo(int tamMax = 100) {
        this->tamMax = tamMax;
        this->tamLista = this->actual = 0;
        this->arreglo = new E*[this->tamMax];

        for (int i = 0; i < tamMax; i++)
        {
            this->arreglo[i] = nulo;
        }
    }

    ~ListaArreglo() {
        delete[] this->arreglo;
    }

    void moverAInicio() {
        this->actual = 0;
    }

    void moverAlFinal() {
        this->actual = this->tamMax - 1;
    }

    void moverAPosicion(int pos) {
        this->actual = pos;
    }

    void siguiente() {
        if (this->actual < this->tamMax)
            this->actual++;
    }

    void anterior() {
        if (this->actual != 0) 
        {
            this->actual--;
        }
    }

    void insertar(E elemento)
    {
        this->arreglo[actual] = new E(elemento);
        this->tamLista++;
    }

    void limpiar() {
        delete[] this->arreglo;
        this->tamLista = this->actual = 0;
        this->arreglo = new E*[this->tamMax];
    }

    E eliminar() {
        E temp = *this->arreglo[actual];
        this->arreglo[actual] = nulo;
        this->tamLista--;
        return temp;
    }

    int longitud() {
        return this->tamLista;
    }

    int posicionActual() {
        return this->actual;
    }


    int get_tamMax()
    {
        return this->tamMax;
    }

    E* getAdress()
    {
        return this->arreglo[this->actual];
    }

    E getValor() {
        return *this->arreglo[this->actual];
    }

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


//SET_open
template<typename Key>
class SET_open : public Set<Key> 
{
private:
    ListaArreglo<Key>* lista;
public:
    //Constructor
    SET_open(int tamanho = 100) 
    {
        lista = new ListaArreglo<Key>(tamanho);
    }

    ~SET_open() 
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
        for(auto e : k)
        {
            ash += int(e) + 30 * c;
            c++;
        }
        return (ash % this->lista->get_tamMax());
    }

    //int/floats
    /*
    int Hash(Key k)
    {
    //falta implementar
    }
    */

    void insertar(Key k) 
    {
        int indice = Hash(k);
        lista->moverAPosicion(indice);
        if (lista->getValor() != nulo)
        {
            while (lista->getValor() != nulo)
            {
                lista->siguiente();
            }
            lista->insertar(k);
            return;
        }
        lista->insertar(k);
    }

    bool encontrar(Key k)
    {
        int indice = Hash(k);
        this->lista->moverAPosicion(indice);
        Key value = this->lista->getValor();
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

    Key removerCualquiera() 
    {
        lista->moverAlFinal();
        lista->anterior();
        Key temp = lista->eliminar();
        return temp;
    }


    int longitud() 
    {
        return this->lista->longitud();
    }
};


//set sin hashing para almacenar claves de numeros
template<typename Key>
class SET_n : public Set<Key>
{
private:
    ListaArreglo<Key>* lista;
public:
    //Constructor
    SET_n(int tamanho = 100)
    {
        lista = new ListaArreglo<Key>(tamanho);
    }

    ~SET_n()
    {
        delete lista;
    }

    void limpiar()
    {
        this->lista->limpiar();
    }

    void insertar(Key k)
    {
        lista->moverAInicio();
        while (lista->getAdress() != nullptr)
        {
            if (lista->getValor() == k)
                return;
            lista->siguiente();
        }
        lista->insertar(k);
        return;
    }

    bool encontrar(Key k)
    {
        Key aux;
        for (lista->moverAInicio(); lista->posicionActual() < lista->longitud(); lista->siguiente())
        {
            aux = lista->getValor();
            if (aux == k)
                return true;
        }
        return false;
    }

    void remover(Key k)
    {
        for (lista->moverAInicio(); lista->posicionActual() < lista->longitud(); lista->siguiente())
        {
            if (lista->getValor() == k)
            {
                lista->eliminar();
            }
        }
    }

    Key removerCualquiera()
    {
        lista->moverAInicio();
        Key temp = lista->eliminar();
        return temp;
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

    virtual E buscar(Key k) = 0;

    virtual bool encontrar(Key k) = 0;

    virtual int longitud() = 0;
};


//SET_open
template<typename Key, typename E>
class Diccionario_open : public Diccionario<Key, E>
{
private:
    ListaArreglo<E>* lista;
public:
    //Constructor
    Diccionario_open(int tamanho = 100)
    {
        lista = new ListaArreglo<E>(tamanho);
    }

    ~Diccionario_open()
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


    void insertar(Key k, E valor)
    {
        int indice = Hash(k);
        lista->moverAPosicion(indice);
        if (lista->getValor() != nulo)
        {
            while (lista->getValor() != nulo)
            {
                lista->siguiente();
            }
            lista->insertar(valor);
            return;
        }
        lista->insertar(valor);
    }

    E buscar(Key k)
    {
        int indice = Hash(k);
        this->lista->moverAPosicion(indice);
        E value = this->lista->getValor();
        if (value != nulo)
        {
            return value;
        }
        return nulo;
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

    E removerCualquiera()
    {
        lista->moverAlFinal();
        while (lista->getValor() == nulo)
        {
            lista->anterior();
        }
            
        E temp = lista->eliminar();
        return temp;
    }


    int longitud()
    {
        return this->lista->longitud();
    }
};

int main()
{
    SET_n<int>* set = new SET_n<int>;
    ListaArreglo<ListaArreglo<int>*>* conjunto = new ListaArreglo<ListaArreglo<int>*>;
    int casos;
       
    int inte;
    int c;

    int se;
    cin >> casos;
    for (size_t i = 0; i < casos; i++)
    {
        cin >> inte;
        for (size_t j = 0; j < inte; j++)
        {
            ListaArreglo<int>* aux = new ListaArreglo<int>;
            cin >> c;
            for (size_t k = 0; k < c; k++)
            {
                cin >> se;
                set->insertar(se);
                aux->insertar(se);
            }
            conjunto->insertar(aux);
            delete aux;
        }

        ListaArreglo<int>* aux = new ListaArreglo<int>;
        cout << "Caso " << i + 1 << ": ";
        while (conjunto->longitud() > 0)
        {
            conjunto->moverAInicio();
            aux = conjunto->eliminar();
            int porcentaje = 0;
            while (aux->longitud() > 0)
            {
                aux->moverAInicio();
                porcentaje += set->encontrar(aux->eliminar());
            }
            cout << porcentaje * 1000 / set->longitud() << "%" << "\t" ;
        }
    }
    return 0;
}

