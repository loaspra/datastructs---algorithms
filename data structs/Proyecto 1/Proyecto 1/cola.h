#pragma once
#include <iostream>
#include <vector>

using namespace std;

template<typename E> class Cola {
private:

public:
	Cola() {}

	virtual ~Cola() {}

	virtual E desencolar() = 0;

	virtual void encolar(E) = 0;

	virtual void limpiar() = 0;

	virtual E valorFrontal() = 0;
	
	virtual void eliminar(E valor) = 0;

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

	void resize()
	{
		vector<E> aux(0);
		for (size_t i = 0; i < this->elemFin; i++)
		{
			aux.push_back(this->arreglo[i]);
		}
		delete[] this->arreglo;
		this->tamMax = this->tamMax + 100;
		this->arreglo = new E[this->tamMax];
		int i = 1;

		for (auto e : aux)
		{
			this->arreglo[i] = e;
			i++;
		}
	}

	E desencolar() {
		E elem = this->arreglo[this->frente];
		this->frente = (this->frente + 1) % this->tamMax;
		return elem;
	}

	void encolar(E elemento) 
	{
		if (elemFin == 50)
			resize();
		this->elemFin = (this->elemFin + 1);
		this->arreglo[this->elemFin] = elemento;
	}

	void limpiar() {
		this->elemFin = 0;
		this->frente = 1;
	}

	int buscar(int valor)
	{
		for (int i = this->frente; i <= this->elemFin; i++)
		{
			if (this->arreglo[i] == valor)
				return i;
		}
		return -1;
	}
	
	E eliminar(int valor)
	{
		int pos = buscar(valor);
		E temp = this->arreglo[pos];
		while (pos < this->elemFin)
		{
			this->arreglo[pos] = this->arreglo[pos + 1];
			pos++;
		}	
		this->elemFin--;
		return temp;
	}

	E valorFrontal() {
		return this->arreglo[this->frente];
	}

	int longitud() {
		return (this->tamMax - this->frente + this->elemFin + 1) % this->tamMax;
	}

};

template<typename E> class LCola : public Cola<E> {
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


	E desencolar() 
	{
		Nodo<E>* temp = this->frente;
		E elem = this->frente->elemento;
		this->frente = this->frente->siguiente;
		tamanho--;
		delete temp;
		return elem;
	}

	bool buscar(E valor) //retorna el indice
	{
		vector<E> aux(0);
		E iter = this->desencolar();
		while (iter != valor && this->tamanho > 0)
		{
			aux.push_back(iter);
			iter = this->desencolar();
		}	

		if (iter != valor)
			return false;				//se rearma toda la estructura...
										// se debe de desencolar tooooda la queue para luego volver a encolarla, ya que no se 
		while (this->tamanho > 0)		// mantendria el orden si es que se volviera a encolar, y la unica manera de iterar dentro de 
		{								// esta estructura es desencolando, ya que no hay ningun nodo "actual" (si es que se implementase, 
			aux.push_back(iter);		// se comportaria como una lista enlazada
			iter = this->desencolar();
		}
		aux.push_back(iter);

		for (auto e : aux)
		{
			this->encolar(e);
		}

		return false;
	}


	void eliminar(E valor)
	{
		vector<E> aux(0);
		E iter = this->desencolar();
		while (iter != valor && this->tamanho > 0)
		{
			aux.push_back(iter);
			iter = this->desencolar();
		}
		if (this->tamanho > 1)
			this->desencolar();

		if (this->tamanho > 1)
			iter = this->desencolar();

		while (this->tamanho > 0)
		{
			aux.push_back(iter);
			iter = this->desencolar();
		}
		aux.push_back(iter);

		for (auto e : aux)
		{
			this->encolar(e);
		}

		return;
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
		while (this->frente != this->elemFin){
			Nodo<E>* temp = frente;
			frente = frente->siguiente;
			delete temp;
		}
		delete elemFin;
		tamanho = 0;
	}


	E valorFrontal() {
		return this->frente->elemento;
	}

	int longitud() {
		return this->tamanho;
	}

};
