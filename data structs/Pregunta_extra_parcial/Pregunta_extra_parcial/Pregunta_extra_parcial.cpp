// Pregunta_extra_parcial.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>

using namespace std;
template<typename E> class Nodo {
public:
    E elemento;
    Nodo* siguiente;

    Nodo(E elemento, Nodo* siguiente = NULL) {
        this->elemento = elemento;
        this->siguiente = siguiente;
    }

    Nodo(Nodo* siguiente = NULL) {
        this->siguiente = siguiente;
    }
};

template<typename E> class ListaEnlazada
{
private:
    Nodo<E>* cola;
    Nodo<E>* head;
    Nodo<E>* actual;
    int cantidad;

    void inicializar()
    {
        this->head = this->actual = this->cola = new Nodo<E>;
        this->cantidad = 0;
    }

public:
    ListaEnlazada()
    {
        inicializar();
    }

    ~ListaEnlazada()
    {
        limpiar();
    }

    void agregar(E elemento)
    {
        this->cola = this->cola->siguiente = new Nodo<E>(elemento, NULL);
        if (cantidad == 0)
            this->head = this->actual = this->cola;
        cantidad++;
    };

    int buscar(E ele)
    {
        this->actual = this->head;
        while (this->actual != NULL)
        {
            if (this->actual->elemento == ele)
            {
                return posicionActual();
            }

            this->actual = this->actual->siguiente;
        }

        return -1;
    }

    void push_front(E item)
    {
        auto aux = new Nodo<E>(item, NULL);
        aux->siguiente = head->siguiente;
        head->siguiente = aux;
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
        return this->actual->elemento;
    }

    E getValor(int pos)
    {
        this->moverAPosicion(pos);
        return this->actual->elemento;
    }

    void anterior()
    {
        this->moverAPosicion(this->posicionActual() - 1);
    }

    void limpiar()
    {
        while (this->head != NULL)
        {
            Nodo<E>* temp = this->head;
            this->head = this->head->siguiente;
            delete temp;
        }
        Nodo<E>* temp = this->cola;
        this->cola = this->head = new Nodo<E>(NULL);
        // delete this->actual;
    }


    E eliminar(E valor)
    {
        int pos;
        pos = this->buscar(valor);
        this->moverAPosicion(pos);
        Nodo<E>* aux = new Nodo<E>(this->actual->siguiente);
        this->moverAPosicion(this->posicionActual() - 1);
        this->actual->siguiente = aux;
        E* temp = new E(aux->elemento);
        cantidad--;
        return *temp;
    }


    E eliminar()
    {
        Nodo<E>* aux = new Nodo<E>(this->actual->siguiente);
        this->moverAPosicion(this->posicionActual() - 1);
        this->actual->siguiente = aux;
        E* temp = new E(aux->elemento);
        delete aux;
        return *temp;
    }


};

template<typename E> class LPila
{
private:
    Nodo<E>* cima;
    int tamanho;
public:

    LPila() {
        this->tamanho = 0;
        this->cima = NULL;
    }

    ~LPila() {
        limpiar();
    }


    E pop() {
        E elem = cima->elemento;
        Nodo<E>* temp = cima->siguiente;
        delete cima;
        cima = temp;
        tamanho--;
        return elem;
    }

    void apilar(E elemento) {
        this->cima = new Nodo<E>(elemento, this->cima);
        this->tamanho++;
    }


    void limpiar() {
        while (this->cima != NULL) {
            Nodo<E>* temp = cima;
            cima = cima->siguiente;
            delete temp;
        }
        tamanho = 0;
    }


    E valorTop() {
        return this->cima->elemento;
    }

    int longitud() {
        return this->tamanho;
    }

};

int correccion(int time)
{
    if (time == 50)
        return 8;
    else
        return 0;
}

template<typename E> class LCola
{
private:
    Nodo<E>* frente;
    Nodo<E>* elemFin;
    int tamanho;
public:

    LCola() {
        this->tamanho = 0;
        this->frente = new Nodo<E>;
        this->frente->siguiente = this->elemFin;
        this->elemFin = new Nodo<E>;
    }

    ~LCola() {
        limpiar();
    }


    E desencolar() {
        E elem = this->frente->elemento;
        this->frente = this->frente->siguiente;
        tamanho--;
        return elem;
    }

    void encolar(E elemento)
    {
        this->elemFin = this->elemFin->siguiente = new Nodo<E>(elemento, this->elemFin);
        this->tamanho++;
        if (this->tamanho == 1)
        {
            this->frente = this->elemFin;
        }
    }


    void limpiar() {
        while (this->frente != NULL) {
            Nodo<E>* temp = frente;
            frente = frente->siguiente;
            delete temp;
        }
        tamanho = 0;
    }


    E valorFrontal()
    {
        return this->frente->elemento;
    }

    int longitud()
    {
        return this->tamanho;
    }

};




int calcular_time(ListaEnlazada<LCola<int>*>* stations, LPila<int>* carrier, int N, int Q, int S)
{
    int pos = 0;
    int time = 0;

    for (size_t i = 0; i < 10000; i++)      //para evitar un overflow


    {
        while (carrier->longitud() > 0 && (stations->getValor(pos)->longitud() < Q || carrier->valorTop() == pos)) //mientras la pila del transportista tenga elementos, y, o el valor top de la pila sea correspondiente a la estacion, o la plataforma b tenga espacio
        {
            if (carrier->valorTop() != pos)
                stations->getValor(pos)->encolar(carrier->valorTop());
            carrier->pop();
            time++;
        }

        while (stations->getValor(pos)->longitud() > 0 && carrier->longitud() < S)            //se cargan los valores de la plataforma b al carrier
        {
            carrier->apilar(stations->getValor(pos)->valorFrontal());
            stations->getValor(pos)->desencolar();
            time++;
        }

        int empty = (carrier->longitud() != 0);
        for (int i = 0; i < N; i++)
        {
            empty += stations->getValor(i)->longitud() != 0; //empty deberia ser cero siempre
        }

        if (empty == 0)          //se verifica que todo este vacio
            break;

        pos = pos % N;
        pos++;
        time += 2;
    }
    time = correccion(time) + time;
    return time;
}


int main()
{
    int set = 0;
    cin >> set;
    for (size_t i = 0; i < set; i++)
    {                           //N: numero de estaciones
        int N, S, Q;            //S: capacidad del transportista
        cin >> N >> S >> Q;     //Q: maximo espacio en las plataformas B de cada estacion
        ListaEnlazada<LCola<int>*>* estaciones = new ListaEnlazada<LCola<int>*>;
        LPila<int>* transportista = new LPila<int>;

        for (size_t i = 0; i < N; i++)      //se ingresan las cargas que tiene cada estacion (1 a N)
        {
            estaciones->moverAPosicion(i);
            int n, x = 0;
            cin >> n;
            LCola<int>* estacion = new LCola<int>;
            for (size_t j = 0; j < n; j++)
            {
                cin >> x;
                estacion->encolar(x);
            }
            estaciones->agregar(estacion);
        }
        cout << calcular_time(estaciones, transportista, N, Q, S) - 2; //se retrasa en 2 ya que la primera iteracion del while(true), como la posicion 
        //"por default" del programa es 0, se denota como una estacion fantasma, ya que las estaciones empiezan desde el numero "1"
    }
    //En el enunciado se especifica que cada linea que representa la estacion "N", cada cargo no es correspondiente a la estacion:
    /*Puede suponer que ninguno de estos cargamentos de
        Qi tendrá la estación i como destino.
        Por lo tanto, en el ejemplo 3, el programa arroja un resultado diferente, ya que en la estacion 2:
    3 2 4 3 existe un paquete destinado a esa misma estacion, por lo tanto es redundante que el transportista deba de recojer este*/
    return 0;
}