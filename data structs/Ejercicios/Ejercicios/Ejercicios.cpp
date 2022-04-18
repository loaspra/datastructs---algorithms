#include <iostream>
#include <string>
#include <math.h>
#include <vector>
using namespace std;
template <typename E>

class Lista
{
private:
    void operator=(const Lista&) {} //Asignación
    Lista(const Lista&) {}          //Copia de constructor
public:
    Lista() {} //Constructor por defecto
    virtual void agregar(E item) = 0;
    virtual void push_front(E item) = 0;

    virtual void insertar(E item) = 0;
    //virtual E eliminar() = 0;

    virtual void moverAInicio() = 0;
    virtual void moverAlFinal() = 0;
    virtual void moverAPosicion(int pos) = 0;

    virtual int posicionActual() = 0;
    virtual int longitud() = 0;
    virtual void siguiente() = 0;
    //virtual void anterior() = 0;

    virtual E getValor() = 0;

    /*virtual ~Lista(){} //destructor base
    virtual void limpiar() = 0; //limpiar contenidos de la lista

    virtual E eliminar() = 0;*/
};

template <typename E>
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
        this->siguiente = NULL;
    }
};

template <typename E>
class ListaEnlazada : public Lista<E>
{
private:
    Nodo<E>* cola;   //puntero al final de la lista
    Nodo<E>* head;   //puntero al inicio de la lista
    Nodo<E>* actual; //pos actual
    int cantidad;    //tamaño de la lista

    void inicializar()
    {
        this->head = this->actual = this->cola = new Nodo<E>();
        this->cantidad = 0;
    }

public:
    ListaEnlazada()
    {
        inicializar();
    }

    void agregar(E elemento)
    {
        this->cola = this->cola->siguiente = new Nodo<E>(elemento, NULL);
        if (cantidad == 0)
            this->head = this->actual = this->cola;
        cantidad++;
    };

    void push_front(E item)
    {
        auto aux = new Nodo<E>(item, NULL);
        aux->siguiente = head->siguiente;
        head->siguiente = aux;
        this->actual = this->head;
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
        return this->actual->valor;
    }
};


int main()
{
    string entrada;
    ListaEnlazada<char>* lista = new ListaEnlazada<char>;
    cin >> entrada;
    for (auto e : entrada)
    {
       // if (lista->longitud() == 0)
       
//                lista->agregar(e);

            if (e == '[')
            {
                //lista->moverAlFinal();
                lista->moverAInicio();
            }
            else
            {
                if (e == ']')
                {
                    //lista->moverAInicio();
                    lista->moverAlFinal();
                }
                else
                {
                    lista->insertar(e);
                    lista->siguiente();
                }
            }
        
    }

    lista->moverAInicio();
    lista->siguiente();
    for (int e = 0; lista->posicionActual() < lista->longitud(); lista->siguiente())
    {
        cout << lista->getValor();
    }

    delete lista;
    return 0;
}
