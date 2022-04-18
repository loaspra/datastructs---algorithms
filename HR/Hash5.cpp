#include <iostream>
#include <math.h>
using namespace std;

template <typename E> class Lista {
private:
	void operator=(const Lista&) {
	} // Asignación
	Lista(const Lista&) {
	} // Copia de constructor
public:
	Lista() {
	} // Constructor por defecto
	virtual ~Lista() {
	} // destructor base

	// Limpiar contenidos desde la lista, para hacerla vacía
	virtual void limpiar() = 0;

	// Insertar un elemento al final de la lista
	// item: el elemento a ser insertado
	virtual void insertar(E item) = 0;

	// Agregar un elemento al final de la lista
	// item: el elemento a ser agregado
	virtual void agregar(E item) = 0;

	// Eliminar y retornar el elemento actual
	// retornar: el elemento que fue eliminado
	virtual E eliminar() = 0;

	// Modificar la posici'on actual al inicio de la lista
	virtual void moverAInicio() = 0;

	// Modificar la posición al final de la lista
	virtual void moverAlFinal() = 0;

	// Mover la posición actual un paso a la izquierda.
	// No cambia si ya est'a al inicio
	virtual void anterior() = 0;

	// Mover la posición actual un paso a la derecha.
	// No cambia si ya está al final
	virtual void siguiente() = 0;

	// Retornar: el número de elementos en la lista
	virtual int longitud() = 0;

	// Retornar: la posición del elemento actual
	virtual int posicionActual() = 0;

	// Modificar la posición actual
	// pos: la posición para hacer actual
	virtual void moverAPosicion(int pos) = 0;

	// Retornar: el elemento actual
	virtual E getValor() = 0;
};

// ArrayList
template <typename E> class ListaArreglo : public Lista<E> {
private:
	int tamMax;   // tamaño predeterminado
	int tamLista; // nro elementos ingresados hasta ahora
	int actual;   //índice actual (equivalente al puntero actual en la lista
				  //enlazada)
	// Arreglo de elementos
	E* arreglo;

public:
	// Constructor
	ListaArreglo(int tamMax = 100) {
		this->tamMax = tamMax;
		this->tamLista = this->actual = 0;
		this->arreglo = new E[this->tamMax];
	}

	// Destructor
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

	int get_tamMax() {
		return this->tamMax;
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

// Clase Abstracta: Diccionario
template <typename Key, typename E> class Diccionario {
private:
public:
	// Constructor
	Diccionario() {
	}
	// Base Destructor
	virtual ~Diccionario() {
	}

	// Permite reinicializar el diccionario o tabla Hash
	virtual void limpiar() = 0;

	// k: la clave para el registro
	// e: el registro siendo insertado
	virtual void insertar(Key k, E e) = 0;

	// k: la clave para el registro a ser removido
	// retorno: un registro asociado a k. Si hay muchos registros
	// que se asocian a k, hay que remover uno de manera arbitraria
	// Debe retornar NULL si no hay registros con la clave k
	virtual E remover(Key k) = 0;

	// Retornar y remover un registro arbitrario del diccionario
	// Retorna NULL si no hay registros en el diccionario
	virtual E removerCualquiera() = 0;

	// Retornar un registro que se asocie con k (NULL si no existe)
	// Si múltiples registros se asocian con k, retornar uno
	// de manera arbitraria
	// k: es la clave a encontrar
	virtual E encontrar(Key k) = 0;

	// Retornar el número de registros existentes en el diccionario
	virtual int longitud() = 0;
};

template <typename Key, typename E> class KVpar {
private:
	Key k;
	E e;

public:
	KVpar() {
	}
	KVpar(Key clave, E valor) {
		this->k = clave;
		this->e = valor;
	}
	// Copia de constructor
	KVpar(const KVpar& o) {
		this->k = o.k;
		this->e = o.e;
	}

	// Métodos para acceso a los atributos
	Key getClave() {
		return this->k;
	}

	// Sobrecarga de operador =
	void operator=(const KVpar& o) {
		this->k = o.k;
		this->e = o.e;
	}

	E getValor() {
		return this->e;
	}

	void setClave(Key k) {
		this->k = k;
	}

	void setValor(E e) {
		this->e = e;
	}
};

//---------------------------
template <typename E> class DiccionarioHashing : public Diccionario<string, E> {
private:
	ListaArreglo<E>* lista;
	// int tam;
public:
	DiccionarioHashing(int tamanho = 100) {
		lista = new ListaArreglo<E>(tamanho);
	}

	~DiccionarioHashing() {
		delete lista;
	}

	void limpiar() {
		lista->limpiar();
	}

	void insertar(string k, E e) {
		int a = Hash(k);
		lista->moverAPosicion(a);
		lista->insertar(e);
	}

	E encontrar(string k) {
		int lugar = Hash(k);
		lista->moverAPosicion(lugar);
		return lista->getValor();
	}

	int Hash(string k) {
		int contador = 0;
		int ind = 0;
		for (auto e : k) {
			ind += int(e) * pow(10, contador);
		}
		ind = ind % (this->lista->get_tamMax());

		return ind;
	}

	E remover(string k) {
		int lugar = Hash(k);
		lista->moverAPosicion(lugar);
		auto e = lista->getValor();
		lista->eliminar();
		return e;
	}

	E removerCualquiera() {
		lista->moverAlFinal();
		lista->anterior();
		E temp = lista->eliminar();

		return temp;
		// return ;
	}

	int longitud() {
		return this->lista->longitud();
	}
};
//-------------------------------------------

class Boleta {
private:
	int ID;
	string nombre;
	string direccion;

public:
	Boleta(int id, string nom, string dir) {
		this->ID = id;
		this->nombre = nom;
		this->direccion = dir;
	}

	int getID() {
		return this->ID;
	}

	string getNombre() {
		return this->nombre;
	}

	string getDireccion() {
		return this->direccion;
	}
};

int main() 
{
	DiccionarioHashing<double>* dic = new DiccionarioHashing<double>;
	string p;
	double b;
	int N_;
	int N;
	cin >> N;
	cin >> N_;
	int aux = 0;
	int numero;
	for (auto e = 0; e < N; e++)
	{
		cin >> p;
		cin >> b;
		dic->insertar(p, b);
	}
	
	for (auto e = 0; e < N_; e++)
	{
		do
		{
			cin >> p;
			if (p != "+")
			{
				aux += dic->encontrar(p);
			}
			cout << "p: " << p << "_";
		} while (p != "<" && p != ">" && p != "=" && p != "<=" && p != ">=");
			
		cin >> numero;
		cout << "Supuesto #" << e + 1;
		if (p == "<")
		{
			cout << "||" << aux << "<" << numero << "||";
			if (aux < numero)
			{
				cout << " fue correcto." << endl;
			}
			else
			{
				cout << " fue incorrecto." << endl;
			}
		}
		else
		{
			if (p == ">")
			{
				cout << "||" << aux << ">" << numero << "||";
				if (aux > numero)
				{
					cout << " fue correcto." << endl;
				}
				else
				{
					cout << " fue incorrecto." << endl;
				}
			}
			else
			{
				if (p == ">=")
				{
					cout << "||" << aux << ">=" << numero << "||";
					if (aux >= numero)
					{
						cout << " fue correcto." << endl;
					}
					else
					{
						cout << " fue incorrecto." << endl;
					}
				}
				else
				{
					if (p == "<=")
					{
						cout << "||" << aux << "<=" << numero << "||";
						if (aux <= numero)
						{
							cout << " fue correcto." << endl;
						}
						else
						{
							cout << " fue incorrecto." << endl;
						}
					}
					else
					{
						cout << "||" << aux << "=" << numero << "||";
						if (aux == numero)
						{
							cout << " fue correcto." << endl;
						}
						else
						{
							cout << " fue incorrecto." << endl;
						}
					}
				}
			}
		}
	}

	delete dic;
	return 0;
}
