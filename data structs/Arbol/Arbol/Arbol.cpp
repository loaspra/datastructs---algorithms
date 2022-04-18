#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
template<typename E>
class Nodo
{
public:
    E valor;
    Nodo* siguiente;
    Nodo(E valor, Nodo* siguiente = NULL)
    {
        this->valor = valor;
        this->siguiente = siguiente;
    }
    Nodo(Nodo* siguiente = NULL)
    {
        this->siguiente = siguiente;
    }
};
template<typename E>
class Cola
{
private:
    void operator = (const Cola&) {}  //Proteccion asignada
    Cola(const Cola&) {}  //Constructor Proteccion copia
public:
    Cola() {}  //por defecto
    virtual ~Cola() {}  //Base destructor

    //Reinicializar la cola. El usuario es responsable
    //por reclamar el espacio utilizado por el elemento
    //de la cola
    virtual void limpiar() = 0;

    //colocar un elemento en la parte de atras de la cola
    //it: el elemento siendo encolado
    virtual void push(E item) = 0;

    //Remover y retornar elementos al frente de la cola
    //Retornar: El elemento en el frente de la cola.
    virtual E pop() = 0;

    //Retornar: Una copia de el elemento frontal
    virtual E getValor() = 0;

    //Retornar: El numero de elementos in la cola .
    virtual int longitud() = 0;

};
template<typename E>
class LCola : public Cola<E>
{
private:
    Nodo<E>* frente;    //puntero al nodo frontal
    Nodo<E>* fin;        //puntero al nodo final
    int tamanho;        //Numero de elementos en la cola

public:
    LCola(int sz = 100) // constructor
    {
        frente = fin = new Nodo<E>(); tamanho = 0;
    }

    ~LCola() { limpiar(); delete frente; } //destructor

    void limpiar() { //vaciar cola
        while (frente->siguiente != NULL) { //elimiar cada enlace
            fin = frente;
            delete fin;
        }
        fin = frente;
        tamanho = 0;
    }

    void push(E it) { //Poner elementos al final de la cola
        fin->siguiente = new Nodo<E>(it, NULL);
        fin = fin->siguiente;
        tamanho++;
    }

    E pop() { //Remover elementos del frente
      //Assert(tamanho != 0, "La cola esta vacia");
        E it = frente->siguiente->valor; //Almacena el valor desencolado
        Nodo<E>* ltemp = frente->siguiente; //mantener el enlace al valor desencolado
        frente->siguiente = ltemp->siguiente; //avanzar al frente
        if (fin == ltemp) fin = frente; //desencolar el ultimo elemento
        delete ltemp; //borrar enlace 
        tamanho--;
        return it; //retornar el elemento desencolado
    }

    E getValor() { //obtener el elemento del frente
      //Assert(tamanho != 0, "La cola esta vacia");
        return frente->siguiente->valor;
    }

    virtual int longitud() { return tamanho; }
};
template<typename E>
class Lista
{
private:
    void operator = (const Lista&) {}
    Lista(const Lista&) {}
public:
    Lista() {}
    virtual ~Lista() {}
    virtual void push_back(E item) = 0;
    virtual void push_front(E item) = 0;
    virtual void insertar(E item) = 0;
    virtual void moverAPosicion(int pos) = 0;
    virtual void moverAInicio() = 0;
    virtual int posicionActual() = 0;
    virtual int longitud() = 0;
    virtual void siguiente() = 0;
    virtual E getValor() = 0;
    virtual void limpiar() = 0;
    virtual E eliminar() = 0;
    virtual void moverAlFinal() = 0;
    virtual void anterior() = 0;
};
template<typename E>
class ListaArreglo : public Lista<E>
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
    void insertar(E elemento)
    {
        //for(int i = tamLista; i>actual; i--)
        //{
        //    this->arreglo[i] = this->arreglo[i-1];
        //}
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
};
template <typename E>
class ArbolBinario {
private:
public:
    ArbolBinario() {} //Constructor
    virtual ~ArbolBinario() {} //Base destructor

    virtual void insertar(E e) = 0;

    /*virtual E remover (E e) = 0;
    //Reinicializar arbol binario
    virtual void limpiar() = 0;*/

    virtual E encontrar(E eK) = 0;

    //Retornar el numero de registros en el arbol binario
    virtual int longitud() = 0;
};
template <typename E>
class ArbolBinarioArreglo : ArbolBinario<E> {
private:
    ListaArreglo<E>* arreglo;
    int tamMax; //el tamaño del arreglo fijo
    int tamLista; //elementos que realmente almacena el árbol binario
public:
    ArbolBinarioArreglo(int size = 100)
    {
        this->tamMax = size;
        this->tamLista = 0;
        this->arreglo = new ListaArreglo<E>(size);
    }
    //Retornar el numero de registros en el arbol binario
    int longitud() {
        return this->tamLista;
    }

    void insertar(E e) {
        if (this->tamLista == 0)
        {
            arreglo->insertar(e);
            this->tamLista++;
            return;
        }
        int a = 0;
        while (true)
        {
            if (arreglo->getValor(a) == '\0')
            {
                arreglo->putValue(a, e);
                this->tamLista++;
                return;
            }
            if (arreglo->getValor(a) == e)
            {
                return;
            }
            if (e > arreglo->getValor(a))
            {
                a = 2 * a + 2;
            }
            if (e < arreglo->getValor(a))
            {
                a = 2 * a + 1;
            }
        }
    }

    E encontrar(E eK) {
        int a = 0;
        int n = 0;
        while (true)
        {
            if (arreglo->getValor(a) == eK)
            {
                if (arreglo->getValor(2 * a + 1) != '\0')
                {
                    cout << arreglo->getValor(2 * a + 1) << endl;
                }
                if (arreglo->getValor(2 * a + 2) != '\0')
                {
                    cout << arreglo->getValor(2 * a + 2) << endl;
                }
                return n;
            }
            if (eK > arreglo->getValor(a))
            {
                a = 2 * a + 2;
                n = n + 1;
            }
            if (eK < arreglo->getValor(a))
            {
                a = 2 * a + 1;
                n = n + 1;
            }
        }
        return n;
    }
};
int main()
{
    int* num = new int;
    ArbolBinarioArreglo<int>* arbol = new ArbolBinarioArreglo<int>();
    int aux = 0;
    int b = 0;

    while (true)
    {
        cin >> aux;
        if (aux != -1)
        {
            arbol->insertar(aux);
        }
        else
        {
            arbol->encontrar(b);
            return 0;
        }
        b = aux;
    }
}