#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>
using namespace std;

template<typename E> class Lista {
private:
    void operator = (const Lista&) {} //Asignación
    Lista(const Lista&) {} // Copia de constructor
public:
    Lista() {} //Constructor por defecto
    virtual ~Lista() {} //destructor base

    //Limpiar contenidos desde la lista, para hacerla vacía
    virtual void limpiar() = 0;

    //Insertar un elemento al final de la lista
    //item: el elemento a ser insertado
    virtual void insertar(E item) = 0;

    //Agregar un elemento al final de la lista
    //item: el elemento a ser agregado
    virtual void agregar(E item) = 0;

    //Eliminar y retornar el elemento actual
    //retornar: el elemento que fue eliminado
    virtual E eliminar() = 0;

    // Modificar la posici'on actual al inicio de la lista
    virtual void moverAInicio() = 0;

    //Modificar la posición al final de la lista
    virtual void moverAlFinal() = 0;

    //Mover la posición actual un paso a la izquierda.
    //No cambia si ya est'a al inicio
    virtual void anterior() = 0;

    //Mover la posición actual un paso a la derecha.
    //No cambia si ya está al final
    virtual void siguiente() = 0;

    //Retornar: el número de elementos en la lista
    virtual int longitud() = 0;

    //Retornar: la posición del elemento actual
    virtual int posicionActual() = 0;

    //Modificar la posición actual
    //pos: la posición para hacer actual
    virtual void moverAPosicion(int pos) = 0;

    //Retornar: el elemento actual
    virtual E getValor() = 0;
};



//ArrayList
template<typename E>
class ListaArreglo : public Lista<E> {
private:
    int tamMax;//tamaño predeterminado
    int tamLista; //nro elementos ingresados hasta ahora
    int actual; //índice actual (equivalente al puntero actual en la lista enlazada)
    //Arreglo de elementos
    E* arreglo;
public:
    //Constructor
    ListaArreglo(int tamMax = 100) {
        this->tamMax = tamMax;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }

    //Destructor
    ~ListaArreglo() {
        delete[] this->arreglo;
    }

    void moverAInicio() {
        this->actual = 0;
    }

    void moverAlFinal() {
        this->actual = this->tamLista;
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

    void agregar(E elemento) {
        this->arreglo[this->tamLista++] = elemento;
    }

    void insertar(E elemento) {
        for (int i = tamLista; i > actual; i--) {
            this->arreglo[i] = this->arreglo[i - 1];
        }
        this->arreglo[actual] = elemento;
        this->tamLista++;
    }


    void limpiar() {
        delete[] this->arreglo;
        this->tamLista = this->actual = 0;
        this->arreglo = new E[this->tamMax];
    }

    E eliminar() {
        E temp = this->arreglo[actual];
        for (int i = actual; i < this->tamLista - 1; i++) {
            this->arreglo[i] = this->arreglo[i + 1];
        }
        this->tamLista--;
        return temp;
    }

    int longitud() {
        return this->tamLista;
    }

    int posicionActual() {
        return this->actual;
    }

    void moverAPosicion(int pos) {
        if (pos >= 0 && pos < this->tamLista) {
            this->actual = pos;
        }
    }

    E getValor() {
        return this->arreglo[this->actual];
    }

    E getValor_pos(int pos)
    {
        return this->arreglo[pos];
    }

    void putValue(int pos, int value)
    {
        this->arreglo[pos] = value;
    }

    //Función amiga para accesar a los atributos privados
    friend void quick_sort(ListaArreglo<int>* arreglo, int izq, int der);
};

void imprimir(ListaArreglo<int>* arreglo)
{
    for (arreglo->moverAInicio(); arreglo->posicionActual() < arreglo->longitud(); arreglo->siguiente())
    {
        cout << arreglo->getValor() << endl;
    }
}




void quick_sort(ListaArreglo<int>* arreglo, int izq, int der)
{

    int i, j, x, aux;
    i = izq;
    j = der;
    x = arreglo->getValor_pos((izq + der) / 2);

    do {
        while ((arreglo->getValor_pos(i) < x) && (j <= der))
        {
            i++;
        }

        while ((x < arreglo->getValor_pos(j)) && (j > izq))
        {
            j--;
        }

        if (i <= j)
        {
            aux = arreglo->getValor_pos(i);
            arreglo->putValue(i, arreglo->getValor_pos(j));
            arreglo->putValue(j, aux);
            i++;  j--;
        }

    } while (i <= j);

    if (izq < j)
        quick_sort(arreglo, izq, j);
    if (i < der)
        quick_sort(arreglo, i, der);
}

int main() {
    ListaArreglo<int>* vera = new ListaArreglo<int>();
    int* N = new int(7);
    int* aux = new int;

    vector<int> oa = { 5 , 3 , 7 , 6 , 2 , 1 , 4 };

    for (auto e = 0; e < *N; e++)
    {
        
        vera->agregar(oa[e]);
    }
    auto a = *N - 1;
    quick_sort(vera, 0, a);
    imprimir(vera);
}
