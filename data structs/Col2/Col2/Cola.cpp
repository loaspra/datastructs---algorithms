#include <iostream>

using namespace std;

//Nodo
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

template<typename E>
class ListaArreglo 
{
private:
	int tamMax;
	int tamLista;
	int actual;
	E* arreglo;
public:

	ListaArreglo(int tamMax = 100) {
		this->tamMax = tamMax;
		this->tamLista = this->actual = 0;
		this->arreglo = new E[this->tamMax];
	}

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

};

//Cola abstract
template<typename E> class Cola {
private:

public:
	Cola() {}

	virtual ~Cola() {}

	virtual E desencolar() = 0;

	virtual void encolar(E) = 0;

	virtual void limpiar() = 0;

	virtual E valorFrontal() = 0;

	virtual int longitud() = 0;
};

template<typename E> class ACola {
private:
	int tamMax;
	int frente;
	int elemFin;
	E* arreglo;
public:
	ACola(int tamanho = 100) {
		this->tamMax = tamanho + 1;
		this->frente = 1;
		this->elemFin = 0;
		this->arreglo = new E[this->tamMax];
	}

	~ACola() {
		delete[] this->arreglo;
	}

	E desencolar() {
		E elem = this->arreglo[this->frente];
		this->frente = (this->frente + 1) % this->tamMax;
		return elem;
	}

	void encolar(E elemento) {
		this->elemFin = (this->elemFin + 1) % this->tamMax;
		this->arreglo[this->elemFin] = elemento;
	}

	void limpiar() {
		this->elemFin = 0;
		this->frente = 1;
	}

	E valorFrontal() {
		return this->arreglo[this->frente];
	}

	int longitud() {
		return (this->tamMax - this->frente + this->elemFin + 1) % this->tamMax;
	}

};

//Clase faltante
template<typename E> class LCola : public Cola<E> {
private:
	Nodo<E>* frente;
	Nodo<E>* elemFin;
	int tamanho;
public:
	//Constructor
	LCola() {
		this->tamanho = 0;
		this->frente = new Nodo<E>;
		this->frente->siguiente = this->elemFin;
		this->elemFin = new Nodo<E>;
	}

	//Destructor
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


	E valorFrontal() {
		return this->frente->elemento;
	}

	int longitud() {
		return this->tamanho;
	}

};

int main()
{
	LCola<int>* cola = new LCola<int>;
	ListaArreglo<int>* IDs = new ListaArreglo<int>;
	ListaArreglo<int>* per = new ListaArreglo<int>;

	string esto;
	int N;
	int ID;
	int p;
	cin >> esto;

	while (esto != "#")
	{
		cin >> ID;
		IDs->agregar(ID);
	}

	cin >> N;
}