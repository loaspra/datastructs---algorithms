#include <iostream>

using namespace std;

template<typename E> class Link 
{
public:
    E elemento;//valor para este nodo
    Link* siguiente; //Puntero al siguiente nodo en la lista
    //Constructores
    Link(const E& elemVal, Link* proximoVal = NULL) {
        elemento = elemVal;
        siguiente = proximoVal;
    }

    Link(Link* proximoVal = NULL) {
        siguiente = proximoVal;
    }
};


class Arista 
{
    int vertice, peso;
public:
    Arista() 
    {
        this->vertice = -1;
        this->peso = -1;
    }

    Arista(int v, int w) 
    {
        this->vertice = v;
        this->peso = w;
    }

    int getVertice() { return this->vertice; }
    int getPeso() { return this->peso; }
};


template<typename E> class ListaEnlazada
{
private:
    Link<E>* cabeza; //puntero a la cabeza de la lista
    Link<E>* cola; //puntero al 'ultimo elemento
    Link<E>* actual; //puntero al elemento actual
    int cantidad; //tamano de la lista

    void inicializar() {
        actual = cola = cabeza = new Link<E>;
        cantidad = 0;
    }

    void eliminarTodo() {//retornar nodos de Link para liberar espacio
        while (cabeza != NULL) {
            actual = cabeza;
            cabeza = cabeza->siguiente;
            delete actual;
        }
    }

public:
    ListaEnlazada() {
        inicializar();
    }

    ~ListaEnlazada() {
        eliminarTodo();
    }




    void imprimir() const;
    void limpiar() {
        eliminarTodo();
        inicializar();
    }

    //Insertar "it" en posicion actual
    void insertar(E it) {
        actual->siguiente = new Link<E>(it, actual->siguiente);
        if (cola == actual)
            cola = actual->siguiente;//nuev cola
        cantidad++;
    }



    void agregar(E it) {
        //Agregar "it" a la lista
        cola = cola->siguiente = new Link<E>(it, NULL);
        cantidad++;
    }

    //Eliminar y retornar elemento actual
    E eliminar() {
        E it = actual->siguiente->elemento; //recordar valor
        Link<E>* ltemp = actual->siguiente; //recordar nodo enlace
        if (cola == actual->siguiente)
            cola = actual; //resetear la cola
        actual->siguiente = actual->siguiente->siguiente;//eliminar de la lista
        delete ltemp;
        cantidad--;
        return it;
    }



    void moverAInicio() 
    {
        this->actual = this->cabeza;
    }

    void moverAlFinal() {
        this->actual = this->cola;
    }


    //Retroceder
    void anterior() {
        if (actual == cabeza) return;
        Link<E>* temp = cabeza;
        while (temp->siguiente != actual) temp = temp->siguiente;
        actual = temp;
    }

    //Avanzar
    void siguiente() {
        if (actual != cola) actual = actual->siguiente;
    }



    //Longitud de la lista
    int longitud() {
        return this->cantidad;
    }

    //Retornar posición actual
    int posicionActual() {
        Link<E>* temp = cabeza;
        int i;
        for (i = 0; actual != temp; ++i) {
            temp = temp->siguiente;
        }
        return i;
    }


    //Mover actual posición de lista a pos
    void moverAPosicion(int pos) {
        if (pos<0 || pos>cantidad) {
            cout << "Posición fuera de rango";
        }
        actual = cabeza;
        for (int i = 0; i < pos; ++i) {
            actual = actual->siguiente;
        }
    }


    E getValor() {//retornar elemento actual
        if (actual->siguiente == NULL)
            cout << "Valor no existe";
        return actual->siguiente->elemento;
    }
    friend void reportar();
};

void reportar(ListaEnlazada<int>* x) {
    for (x->moverAInicio(); x->posicionActual() < x->longitud(); x->siguiente()) {
        int y = x->getValor();
        cout << y << endl;
    }
}

class GrafoL
{
private:
    int numVertice, numArista; //número de vértices y aristas
    ListaEnlazada<Arista>** vertice; //arreglo de puntero para listas de adyacencias
    int* marca; //lista de visitados
public:
    //Inicializar un grafo de N vértices
    void Init(int n) {
        int i;
        this->numVertice = n;
        this->numArista = 0;
        this->marca = new int[n];
        for (i = 0; i < this->numVertice; i++) marca[i] = 0;
        //Crear e inicializar la lisa de adyacencia
        vertice = (ListaEnlazada<Arista>**) new ListaEnlazada<Arista>*[this->numVertice];
        for (i = 0; i < this->numVertice; i++) {
            vertice[i] = new ListaEnlazada<Arista>;
        }
    }

    GrafoL(int numVertice) {
        //constructor
        Init(numVertice);
    }

    ~GrafoL() {
        //destructor
        delete[] this->marca;
        for (int i = 0; i < this->numVertice; i++) {
            delete[] vertice[i];
        }
        delete[] vertice;
    }


    //Retorno de vértices y aristas
    int n() 
    {
        return this->numVertice;
    }

    int e() 
    {
        return this->numArista;
    }

    //Retorno del primer vértice vecino de "v"
    int primero(int v) {
        if (vertice[v]->longitud() == 0) {
            return this->numVertice;
        }
        vertice[v]->moverAInicio();
        Arista it = vertice[v]->getValor();
        return it.getVertice();
    }

    //Retorna el próximo vecino de "v" comenzando desde el índice "w"
    int siguiente(int v, int w) {
        Arista it;
        if (esArista(v, w)) {
            if (vertice[v]->posicionActual() + 1 < vertice[v]->longitud()) {
                vertice[v]->siguiente();
                it = vertice[v]->getValor();
                return it.getVertice();
            }
        }
        return n();
    }

    //Modificación de la arista
    //v1, v2 son los vértices
    //w: peso de arista
    void setArista(int i, int j, int peso) 
    {
        Arista aristaActual(j, peso);
        if (esArista(i, j)) 
        {
            vertice[i]->eliminar();
            vertice[i]->insertar(aristaActual);
        }
        else 
        {
            this->numArista++;
            for (vertice[i]->moverAInicio(); vertice[i]->posicionActual() < vertice[i]->longitud(); vertice[i]->siguiente()) 
            {
                Arista temp = vertice[i]->getValor();
                if (temp.getVertice() > j)break;
            }
            vertice[i]->insertar(aristaActual);
        }
    }

    //Eliminar arista
    void eliminarArista(int v1, int v2) {
        if (esArista(v1, v2)) {
            vertice[v1]->eliminar();
            this->numArista--;
        }
    }

    //Determina si hay una arista entre i-j
    //Retorna: verdadero si la arista i-j existe o tiene peso diferente de CERO
    bool esArista(int i, int j) {
        Arista it;
        for (vertice[i]->moverAInicio(); vertice[i]->posicionActual() < vertice[i]->longitud(); vertice[i]->siguiente()) {
            Arista temp = vertice[i]->getValor();
            if (temp.getVertice() == j) return true;
        }
        return false;
    }
    //Retornar el peso de la arista v1-v2
    // v1, v2 son vértices
    //Retorna: el peso de la arista v1-v2 ó CERO
    int getPeso(int i, int j) {
        Arista actual;
        if (esArista(i, j)) {
            actual = vertice[i]->getValor();
            return actual.getPeso();
        }
        else return 0;
    }

    //Get y set del valor de la marca para un vértice
    int getMarca(int v) {
        return this->marca[v];
    }

    void setMarca(int v, int val) {
        this->marca[v] = val;
    }

    int conjunto(int pos)
    {
        for (vertice[pos]->moverAInicio(); vertice[pos]->posicionActual() < vertice[pos]->longitud(); vertice[pos]->siguiente()) 
        {
            Arista temp = vertice[pos]->getValor();
            if (marca[temp.getVertice()] == 0)
            {
                this->marca[temp.getVertice()] = 1;
                return conjunto(temp.getVertice());
            }
            else
                return 1;
        }
    }

    bool cycle()
    {
        return conjunto(0);
    }
};


int main()
{
    GrafoL* alo = new GrafoL(5);
    alo->setArista(0, 1, 1);
    alo->setArista(1, 2, 1);
    alo->setArista(2, 4, 1);
    alo->setArista(2, 3, 1);
    alo->setArista(4, 2, 1);
    alo->setArista(3, 0, 1);
    cout << "---------" << endl;
    cout << alo->cycle() << endl;
    cout << "---------" << endl;
    return 0;
}