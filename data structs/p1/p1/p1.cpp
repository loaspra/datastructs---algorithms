#include <iostream>
using namespace std;

//Clase Nodo
template<typename E> class Nodo {
public:
    E elemento;
    Nodo* siguiente;

    //Constructores
    Nodo(E elemento, Nodo* siguiente = NULL) {
        this->elemento = elemento;
        this->siguiente = siguiente;
    }

    Nodo(Nodo* siguiente = NULL) {
        this->siguiente = siguiente;
    }
};



//Clase Abstracta Pila
template<typename E> class Pila {
private:
public:
    Pila() {}
    virtual ~Pila() {}

    //Retornar el elemento de la cima y luego eliminarlo de la pila
    virtual E pop() = 0;

    //Apilamos un nuevo elemento en nuestra estructura
    virtual void apilar(E elemento) = 0;

    //Método limpiar: reinicializar la pila
    virtual void limpiar() = 0;

    //Retornar el valor de la cima de la pila
    virtual E valorTop() = 0;

    //Retornar el tamaño de la pila: el número de elementos que contiene la pila
    virtual int longitud() = 0;
};


//Clase faltante
template<typename E> class APila : public Pila<E> {
private:
    int tamMaximo;
    int cima;
    E* arreglo;

public:
    //Inicialización
    APila(int tamanho = 100) {
        this->tamMaximo = tamanho;
        this->cima = 0;
        this->arreglo = new E[this->tamMaximo];
    }

    //Destructor
    ~APila() {
        delete[] this->arreglo;
    }


    E pop() {
        return this->arreglo[--cima];
    }

    void apilar(E elemento) {
        if (this->cima < tamMaximo)
            this->arreglo[cima++] = elemento;
    }

    void limpiar() {
        this->cima = 0;
    }

    E valorTop() {
        return this->arreglo[cima - 1];
    }

    int longitud() {
        return this->cima;
    }
};



//Clase faltante
template<typename E> class LPila : public Pila<E> {
private:
    Nodo<E>* cima;
    int tamanho;
public:
    //Constructor
    LPila() {
        this->tamanho = 0;
        this->cima = NULL;
    }

    //Destructor
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

int main() {
    LPila<string>* sujetos = new LPila<string>();
    int N;
    string palabra;
    string subject;

    cin >> N;
    for (auto e = 0; e < N; e++)
    {
        cin >> palabra;
        if (palabra == "Sleep")
        {
            cin >> subject;
            sujetos->apilar(subject);
        }
        else
        {
            if (palabra == "Kick")
            {
                if (sujetos->longitud() > 0)
                    sujetos->pop();
            }
            else
            {
                if (sujetos->longitud() > 0)
                {
                    cout << sujetos->valorTop() << endl;
                }
                else
                {
                    cout << "No esta en un suenio.";
                }
            }
        }
    }



    return 0;
}